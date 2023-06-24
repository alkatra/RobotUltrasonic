# Simple-Autonomous-Robot

This repository provides a basic implementation for autonomous movement of a robot integrated with an Arduino and ultrasonic sensors. The code in this project reads sensor data, processes it, and automates the robot's movements to avoid obstacles and move indefinitely without requiring manual control.

Key Components:
1. **Arduino Code (arduino.ino)**: An Arduino sketch that interfaces with the ultrasonic sensors on the robot. It reads sensor data and transmits it via serial communication.
2. **Robot Bridge (robot_bridge.py)**: A ROS Node written in Python that reads the serial data from Arduino and forwards it to the robot controller for further processing.
3. **Robot Controller (robot_controller.py)**: A ROS Node written in Python that reads the sensor data forwarded by the robot bridge. It uses this data to automate the robot's movements, enabling it to avoid obstacles and move indefinitely without stopping.

With these three files, you can turn any robot with an Arduino and ultrasonic sensors into an autonomous bot capable of intelligent movement and obstacle avoidance.
