from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    use_keyboard = DeclareLaunchArgument(
        'use_keyboard', default_value='true',
        description='是否随 launch 一起启动键盘遥控节点')

    rviz_config = PathJoinSubstitution(
        [FindPackageShare('rm_oop_demo'), 'rviz', 'odom_demo.rviz'])

    chassis_node = Node(
        package='rm_oop_demo',
        executable='chassis_node',
        name='chassis_node',
        output='screen')

    referee_mock_node = Node(
        package='rm_oop_demo',
        executable='referee_mock_node',
        name='referee_mock_node',
        output='screen')

    keyboard_teleop_node = Node(
        package='rm_oop_demo',
        executable='keyboard_teleop_node',
        name='keyboard_teleop_node',
        output='screen',
        condition=IfCondition(LaunchConfiguration('use_keyboard')))

    rviz2 = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config],
        output='screen')

    return LaunchDescription([
        use_keyboard,
        chassis_node,
        referee_mock_node,
        keyboard_teleop_node,
        rviz2,
    ])
