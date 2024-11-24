# Astra Rover 2025
Every year Astra Robotics participates in a number of rover competitions. This repo is way to store all of the code associated with the rover project in the form of STM32CUBEIDE projects or ROS nodes. It also serves as a way to issue general instructions, track common bugs, raise issues, and keep track of which team is doing what. The idea is to allow anyone with sufficient technical expertise to join the project and start contributing using this repo.

## Embedded Subsystem
### General Instructions
- Try to maintain a single version of STM32CUDEIDE, it gets cranky hwen you open projects made with an older version of the IDE.
- Do go through the FreeRTOS API and make sure to understand the basic concepts behind what a scheduler is, what kind of advantages an RTOS offers, and so on.
- Install MicroROS throught the GitHub repo only. Follow the instructions, make sure to check for the humble branch to match the version of ROS2.
### Current Task
- Start using the RTOS features on the current version of the rover code

