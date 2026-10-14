from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory
import os
import pwd


def _candidate_station_yaml_paths():
    candidates = []

    home_dir = os.getenv('PIX_USER_ROOT')
    if not home_dir:
        for user_env in ('PIX_USER', 'USER'):
            user_name = os.getenv(user_env)
            if not user_name:
                continue
            try:
                home_dir = pwd.getpwnam(user_name).pw_dir
                break
            except KeyError:
                continue
    if not home_dir:
        try:
            home_dir = pwd.getpwuid(os.getuid()).pw_dir
        except KeyError:
            home_dir = os.getenv('HOME', '/home/ipc')

    candidates.append(os.path.join(home_dir, 'pix', 'map', 'main', 'stations.yaml'))

    pix_map_path = os.getenv('PIX_MAP_PATH')
    if pix_map_path:
        candidates.append(os.path.join(pix_map_path, 'main', 'stations.yaml'))
        resolved_main = os.path.realpath(os.path.join(pix_map_path, 'main'))
        candidates.append(os.path.join(resolved_main, 'stations.yaml'))

    candidates.extend([
        '/root/pix/map/main/stations.yaml',
        os.path.join(os.path.realpath('/root/pix/map/main'), 'stations.yaml'),
        '/home/ipc/pix/map/main/stations.yaml',
        os.path.join(os.path.realpath('/home/ipc/pix/map/main'), 'stations.yaml'),
    ])
    deduped_candidates = []
    seen = set()
    for candidate in candidates:
        normalized = os.path.normpath(candidate)
        if normalized in seen:
            continue
        seen.add(normalized)
        deduped_candidates.append(normalized)
    return deduped_candidates


def _default_station_yaml_path():
    for candidate in _candidate_station_yaml_paths():
        if os.path.exists(candidate):
            return candidate
    home_dir = os.getenv('PIX_USER_ROOT') or os.getenv('HOME', '/home/ipc')
    return os.path.join(home_dir, 'pix', 'map', 'main', 'stations.yaml')


def _build_launch(context, *args, **kwargs):
    station_yaml_file_path = LaunchConfiguration('station_yaml_file_path').perform(context)
    if not os.path.exists(station_yaml_file_path):
        raise FileNotFoundError(f"Required station_yaml file not found: {station_yaml_file_path}")

    pkg_share_dir = get_package_share_directory('pixmoving_chassis_interface')
    config_file_path = os.path.join(
        pkg_share_dir,
        'config',
        'chassis_interface.yml'
    )

    return [
        Node(
            package='pixmoving_chassis_interface',
            executable='chassis_interface_node',
            name='pixmoving_chassis_interface_node',
            # namespace='/pixmoving/chassis_interface',
            output='screen',
            respawn=True,
            respawn_delay=60.0,
            parameters=[{
                'loop_rate': LaunchConfiguration('loop_rate'),
                'use_state_machine_drive_mode': True,  # 使用状态机版本
                'station_yaml_file_path': LaunchConfiguration('station_yaml_file_path'),
                'vehicle_info_snapshot_path': LaunchConfiguration('vehicle_info_snapshot_path'),
            }, config_file_path]
        )
    ]


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'loop_rate',
            default_value='10.0',
            description='Loop rate for the chassis interface node'
        ),
        DeclareLaunchArgument(
            'station_yaml_file_path',
            default_value=_default_station_yaml_path(),
            description='Path to the station YAML file'
        ),
        DeclareLaunchArgument(
            'vehicle_info_snapshot_path',
            default_value='/tmp/pixmoving_chassis_interface_vehicle_info.bin',
            description='Cached VehicleInfo snapshot path used across respawn'
        ),
        OpaqueFunction(function=_build_launch)
    ])
