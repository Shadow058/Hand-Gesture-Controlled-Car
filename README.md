# Hand Gesture-Controlled Robot Car using Arduino

## Introduction
This project aims to develop a user-friendly and natural method for controlling a four-wheeled robot car using hand gestures. By utilizing sensors, and Arduino programming, the system recognizes hand gestures to control the movement of the robot car. The project integrates obstacle detection for enhanced safety and navigation.

## Components Required
- **MPU6050 (Gyroscope and Accelerometer)**: Enables precise motion tracking for responsive hand gesture control.
- **Arduino Uno**: Receives hand control data, processes it, and controls the motors.
- **Motor Driver (L293D)**: Controls motor speed and direction.
- **Robot Car Chassis**: Includes wheels and motors for locomotion.
- **Ultrasonic Sensor**: Provides obstacle detection and avoidance capability.
- **Buzzer**: Shows detecton by making a sound.

## Circuit Diagram
![image](https://github.com/user-attachments/assets/81422c9e-9a08-41a8-b64c-9632d5ce8e41)

## Project Overview
- **Hand Gesture Controller**: The hand gesture controller consists of a flex sensor and an accelerometer to capture hand movements. The flex sensor is used to detect finger movements, while the accelerometer detects hand orientation.
- **Robot Car**: The robot car is equipped with a motor driver for processing the data and sending commands to the motors to drive the wheels.
- **Arduino Programming**: The Arduino board is programmed to receive the hand control data, process it, and send commands to the motors to control the robot car's movement.
- **Hand Motion Algorithm**: The proposed system uses a hand motion algorithm to recognize different hand gestures and translate them into specific commands for the robot car
- **Ultrasound-Based Object Avoidance**: Additionally, the proposed system incorporates an ultrasound sensor to enable obstacle detection and avoidance. This feature enhances the safety and autonomy of the robot car by allowing it to detect obstacles in its path and navigate around them.
