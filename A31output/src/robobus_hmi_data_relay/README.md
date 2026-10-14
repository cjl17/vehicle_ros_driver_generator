# robobus_hmi_data_relay

ROS 2 collector package for RoboBus HMI integration.

This package now follows the same high-level shape as `pixmoving_chassis_interface`:

- one shared component library as the business core
- one unified launch entry for normal deployment
- one installable `config/` parameter entry
- one runtime executable generated from component registration

## Architecture

The package is organized by responsibility:

- `src/bridges`: topic and service bridging between Autoware, IPC, and HMI
- `src/monitors`: monitoring and safety-related helpers
- `src/publishers`: lightweight publishers and service helpers
- `src/robobus_hmi_data_relay_node.cpp`: unified aggregation node that owns all modules

Bridge and monitor class naming has been normalized where it materially improved clarity, for example `RelayAutowareTransferBridgeModule`.

Only the unified aggregation node is intended to run. Individual module entrypoints have been removed.
The `robobus_hmi_data_relay_node` executable is now produced directly by ROS 2 component registration rather than a handwritten `main.cpp`.

## Launch

Primary launch file:

```bash
ros2 launch robobus_hmi_data_relay robobus_hmi_data_relay.launch.py
```

Optional arguments:

```bash
ros2 launch robobus_hmi_data_relay robobus_hmi_data_relay.launch.py \
  config_file:=/path/to/robobus_hmi_data_relay.yml \
  git_version_json_path:=/path/to/git_version.json
```

## Parameters

Default parameters are installed at:

`share/robobus_hmi_data_relay/config/robobus_hmi_data_relay.yml`

Current unified config covers:

- `git_version_json_path`
- `blind_spot.left/right/front/rear.{x_min,x_max,y_min,y_max}`
- `blind_spot.threshold.{low_speed_kmh,high_speed_kmh}`
- `blind_spot.delay.{entry_sec,exit_sec}`

Legacy flat blind-spot parameter names are still accepted for compatibility, but the new dotted names are now preferred.
