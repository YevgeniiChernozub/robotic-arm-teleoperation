Robotic Arm Teleoperation System

This project demonstrates a teleoperated robotic arm that can be controlled remotely using wearable sensors and live video feedback.  
The system consists of a robotic arm mounted on a mobile platform, VR headset footage streaming, and a wearable shirt with bending sensors.

---

Overview

This robotic system allows a human operator to control the arm's movement in real-time.
The operator wears a custom-built shirt equipped with bending sensors to mimic human arm motion.

The video stream from the robot is sent to a VR headset, giving fully immersive teleoperation.

---

 Hardware Components

- Custom 3D-printed robotic arm  
- Mobile base platform  
- Servo motors  
- STM32 microcontroller  
- Arduino microcontroller  
- RaspberryPi 3 for video streaming  
- Wearable shirt with flex sensors  

---

Software / Firmware

- STM32 firmware for servo control  
- Arduino firmware for reading flex sensors  
- RaspberryPi software for wireless video streaming  
- Python/C code for signal mapping  

> The system maps bending sensor signals to servo angles.

---

Live Video Streaming

- VR headset (smartphone-inside)
- RaspberryPi video streaming
- Wireless transmission to operator

---

 Competitions

The system was presented at:
- **World Robotics Competition — Abu Dhabi 2019**
- **World Robotics Competition — Mexico City 2020**
