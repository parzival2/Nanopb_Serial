# Nanopb Serial
An example project that uses nanopb to pass messages on USB using Chibios.
The proto files used are in [proto](proto) folder and the headers and sources will be automatically generated using the cmake file provided in Nanopb. 

Inorder to differentiate messages, every message has enum infront of it that differentiates it from other messages. 

This implementation uses [Bluepill](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill.html) to run the code. 
The messages are received and parsed using a script provided in ![Scripts](Scripts) folder. The `proto` files are converted into their python counter parts using [python-betterproto](https://github.com/danielgtaylor/python-betterproto). Please have a look in that repository for installation details. 
