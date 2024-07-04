from launch import LaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    ld = LaunchDescription()

    yaml_file_path = os.path.join(get_package_share_directory("diffdrive_arduino"),"config","map_server_params.yaml")
    
    map_server_cmd = Node(
        package = "nav2_map_server",
        executable = "map_server",
        output = "screen",
        parameters = [{"yaml_filename": yaml_file_path}]
    )




    ld.add_action(map_server_cmd)
    return ld
