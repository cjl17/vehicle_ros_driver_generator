from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share_dir = get_package_share_directory("robobus_hmi_data_relay")
    config_file_path = os.path.join(
        pkg_share_dir,
        "config",
        "robobus_hmi_data_relay.yml",
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "config_file",
                default_value=config_file_path,
                description="Path to the unified parameter file",
            ),
            DeclareLaunchArgument(
                "git_version_json_path",
                default_value="",
                description="Path to the git version JSON payload",
            ),
            LogInfo(msg="Launching robobus_hmi_data_relay as a unified process."),
            Node(
                package="robobus_hmi_data_relay",
                executable="robobus_hmi_data_relay_node",
                name="robobus_hmi_data_relay",
                output="screen",
                parameters=[
                    LaunchConfiguration("config_file"),
                    {
                        "git_version_json_path": LaunchConfiguration(
                            "git_version_json_path"
                        ),
                    },
                ],
            ),
        ]
    )
