#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PKG_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
ROOT_DIR="$(cd "${PKG_DIR}/../../../../../../.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build/pixmoving_chassis_interface"
TEST_BIN="${BUILD_DIR}/test_drive_mode_manager"
JOBS="${JOBS:-2}"

usage() {
  cat <<'EOF'
Usage:
  run_drive_mode_tests.sh
  run_drive_mode_tests.sh --list
  run_drive_mode_tests.sh '<gtest_filter>'

Examples:
  run_drive_mode_tests.sh
  run_drive_mode_tests.sh --list
  run_drive_mode_tests.sh '*AutoCancelNewTask*'
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

echo "[1/3] Configure BUILD_TESTING=ON"
cmake -S "${PKG_DIR}" -B "${BUILD_DIR}" -DBUILD_TESTING=ON

echo "[2/3] Build pixmoving_chassis_interface and test_drive_mode_manager"
CCACHE_DISABLE=1 cmake --build "${BUILD_DIR}" \
  --target pixmoving_chassis_interface test_drive_mode_manager \
  -j"${JOBS}"

export ROS_LOG_DIR="${ROS_LOG_DIR:-/tmp}"
export LD_LIBRARY_PATH="${BUILD_DIR}:${LD_LIBRARY_PATH:-}"

if [[ "${1:-}" == "--list" ]]; then
  echo "[3/3] List gtest cases"
  exec "${TEST_BIN}" --gtest_list_tests
fi

if [[ $# -ge 1 ]]; then
  echo "[3/3] Run gtest with filter: $1"
  exec "${TEST_BIN}" --gtest_filter="$1"
fi

echo "[3/3] Run ctest"
exec ctest --test-dir "${BUILD_DIR}" --output-on-failure -R test_drive_mode_manager
