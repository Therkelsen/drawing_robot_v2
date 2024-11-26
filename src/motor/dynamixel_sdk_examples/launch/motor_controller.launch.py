from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='dynamixel_sdk_examples',
            executable='read_write_node',
            name='motor_controller',
            parameters=[
                {'topic_name': 'set_position'}
            ]
        ),
        # Node(
        #     package='dynamixel_sdk_examples',
        #     executable='read_write_node',
        #     name='motor_controller_10',
        #     parameters=[
        #         {'topic_name': 'motor_10/set_position'}
        #     ]
        # ),
    ])
