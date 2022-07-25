<img src="https://i.imgur.com/l4UcX4U.png" alt="Motodriver-Title" width="500"/>


Universal Arduino library that makes simplier DC engine control via popular motor driver shields.   
Nightly version 2.16

## Feedback 

Here you can submit bug report, feature requests or any other feedback about Motodriver library with only three simple rules:
* Do not create shitful or troll submissions. This will get you banned from this repository.
* Make sure to check other issues before submitting your own.
* Use correct form for what you are submitting.

Choose from the following issue types:
* [Bug Report](https://github.com/Arxaid/motodriver/issues/new?assignees=Arxaid&labels=bug&template=bug-report.yml&title=[Bug+Report])
* [Feature Request](https://github.com/Arxaid/motodriver/issues/new?assignees=Arxaid&labels=enhancement&template=feature-request.yml&title=[Feature+Request])

## Install 

**Arduino IDE:**   
You can import Motodriver library going to _Sketch -> Include Library -> Manage Libraries_ and search for it, or you can download full repository as a .zip file and install it  directly going to _Sketch -> Include Library -> Add .ZIP Library_

**Platform IO:**   
You can import Motodriver library going to _PlatformIO: Home -> Libraries_ and search for it.

## Supported shield drivers

* L298N 2X Motor Shield;
* TB6612 Shield driver;
* MX1508;
* in progress.

## Import

You can import the library in your sketch code writing the include statement:
```
#include <motodriver.h>
```

## Setting up

First thing you need to do is to create a **Motor** class instances to all your motors:
```
Case 1 (for shield drivers like a L298N)
Motor motor = Motor(EN, IN1 , IN2, ShieldDriversName);
```
```
Case 2 (for shield drivers like a TB6612)
Motor motor = Motor(EN, IN1 , 0, ShieldDriversName);
```
```
Case 3 (for shield drivers like a MX1508)
Motor motor = Motor(IN1, IN1 , IN2, ShieldDriversName);
```
Where:
* EN - Arduino PWM pin number connected to Enable pin of the motor driver module. If you using jumper instead of PWM pin, EN equal -1.
For other cases it might be EN=IN1 or EN=IN2 (see case 3).
* IN1 and IN2 - Arduino digital pin numbers connected to Input pins of the motor driver module.
* ShieldDriversName - Type of the motor driver module current motor connected is. If not stated, it will be Undefined.

Second thing is to create a **MotoDriver** class instances to all your motor driver modules:
```
MotoDriver motodriver = MotoDriver(motorList);
```
Where:
* motorList - List of all Motor instances with their own IDs connected to current MotoDriver.

If you want to control all Motors as group, you need to create a **MovingGroup** class instance:
```
MovingGroup movingGroup = MovingGroup(motorGroup);
```
Where:
* motorGroup - List of all Motor instances you want to join as group.

## Lazy MotoDriver methods

| Method        | Params                                                                | Description                                                                                 |
| ------------- | --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| Forward       | signed char **Duty cycle**, signed char **MotorID**                   | Move chosen motor forward with set duty cycle. If not stated, it will be 255.               |
| ForwardUntil  | signed char **Duty cycle**, signed char **MotorID**, short **Delay**  | Move chosen motor forward with set duty cycle and set delay. After delay end shutdown.      |
| Backward      | signed char **Duty cycle**, signed char **MotorID**                   | Move chosen motor backward with set duty cycle. If not stated, it will be 255.              |
| BackwardUntil | signed char **Duty cycle**, signed char **MotorID**, short **Delay**  | Move chosen motor backward with set duty cycle and set delay. After delay end shutdown.     |
| Shutdown      | signed char **MotorID**                                               | Shutdown chosen motor.                                                                      |

## Lazy MovingGroup methods

| Method        | Params                                                                | Description                                                                                 |
| ------------- | --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| GroupForward  | signed char **Duty cycle**                                            | Move all grouped motors forward with set duty cycle. If not stated, it will be 255.         |
| GroupForwardUntil | signed char **Duty cycle**, short **Delay**                           | Move all grouped motors forward with set duty cycle and set delay. After delay end shutdown. |
| GroupBackward | signed char **Duty cycle**                                            | Move all grouped motors backward with set duty cycle. If not stated, it will be 255.        |
| GroupBackwardUntil | signed char **Duty cycle**, short **Delay**                           | Move all grouped motors backward with set duty cycle and set delay. After delay end shutdown. |
| GroupShutdown |                                                                       | Shutdown all motors in moving group.                                                        |
| HardTurnLeft  | signed char **Duty cycle**, short **Delay**                           | Hard turn left with maximum possible angular velocity.                                      |
| HardTurnRight | signed char **Duty cycle**, short **Delay**                           | Hard turn right with maximum possible angular velocity.                                     |
| SoftTurnLeft  | signed char **Duty cycle**, signed char **Turn Duty cycle**, short **Delay**  | Soft turn left with set increased angular velocity.                                 |
| SoftTurnRight | signed char **Duty cycle**, signed char **Turn Duty cycle**, short **Delay**  | Soft turn right with set increased angular velocity.                                |

## Sketch examples

You can find several examples of using Motodriver library with wiring schemas in [Examples](https://github.com/Runsolar/motodriver/tree/main/examples) folder of this repository.

## Authors

[D.Wolf](https://github.com/Runsolar)   
[Arxaid](https://github.com/Arxaid)   
[NeviDimka](https://github.com/dmitrii591)   
