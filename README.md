# Autonomous Mobile Vacuum Cleaning Robot
This project focuses on the development of an autonomous mobile vacuum cleaning robot utilizing the ROS2 (Robot Operating System 2) framework and 2D LiDAR (Light Detection and Ranging) technology. The objective is to design and implement a robot capable of efficient and thorough cleaning in various indoor environments with minimal human intervention.

![Rover in action](Media/Model%20Pictures/1.png)



## Table of Contents
- [Components ](#components)
- [Block Diagram](#block-diagram)
- [Connections](#Connections)
- [Software Used](#software-used)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [Contact](#contact)



## Components
- Raspberry Pi 4B x1
- SD Card (C10) x1
- Motor Driver (L293D For Wheels) x2
- Arduino UNO x1
- RPLiDAR A1 x1
- Drivers for Cleaning Motors x1


## Block Diagram
![Block Diagram](Media/Block%20Diagram.png)

## Connections

![Connection Diagram](Media/Circuit%20Diagram.png)

*Connection Diagram*

## Software Used
- Ubuntu 22.04 LTS
- Robot Operating System (ROS2) (Distro : Humble)
- Nav2 Stack
- Python
- C++
- Arduino Programming

## Installation
Open terminal and Install the following,
```bash
sudo apt install ros-humble-ros2-control
sudo apt install ros-humble-ros2-controllers
sudo apt install ros-humble-robot-state-publisher
sudo apt install ros-humble-joint-state-publisher
sudo apt install ros-humble-joint-state-publisher-gui
sudo apt install ros-humble-joint-state-broadcaster
sudo apt install ros-humble-diff-drive-controller
sudo apt install libserial-dev
```
## Usage

For Launching the LiDAR:
```bash
ros2 launch rplidar_ros rplidar.launch.py
```
For Connecting the RaspberryPi and Arduino:
```bash
ros2 launch diffdrive_arduino diffbot.launch.py
```
For Teleoperation:
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/diffbot_base_controller/cmd_vel_unstamped
```
For Navigation:
```bash
ros2 launch nav2_bringup navigation_launch.py
```
For Launching the SLAM:
```bash
ros2 launch slam_toolbox online_async_launch.py
```
Incase of any errors, Install the dependencies, for that go to the workspace folder and execute the following command:
```bash
rosdep install --from-paths src --ignore-src -r -y
```

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.



## Contact

Dinish S K - [dinishsk02@gmail.com](mailto:your.email@example.com)

