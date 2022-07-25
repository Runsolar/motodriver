<img src="https://i.imgur.com/l4UcX4U.png" alt="Motodriver-Title" width="500"/>


Universal Arduino library that makes simplier DC engine control via popular motor driver shields.

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

Include the Motodriver library in your sketch code.
```
#include <motodriver.h>
```

## Setting up
In order to control your physical motors, firstly you must create abstractions of its. These abstractions are implemented through a class called **Motor**.
Therefore in the first place you must to declarate the **Motor** class objects. It is preferable to do this outside of the **setup** and **loop** functions in *.ino sketch.
```
Motor motor_1;
Motor motor_2;
...
Motor motor_N;
```

A class which responsible for the all control logic of the **Motor** class objects is called **MotoDriver**.
Therefore, at the second step you must to declarate the **MotoDriver** class object and to create a class template collection of the motors.
Also we recommend to declare it out of the setup and loop functions in your sketch.
```
MotoDriver motodriver_1;
MotoDriver motodriver_2;
...
MotoDriver motodriver_M;

std::map<uint8_t, Motor> motorList_1;
std::map<uint8_t, Motor> motorList_2;
...
std::map<uint8_t, Motor> motorList_M;
```

In the next step, in the **setup** function you must to initialize your created objects before.

```
motor_1 = Motor(EN, IN1 , IN2, ShieldDriversName);
motor_2 = Motor(EN, IN1 , IN2, ShieldDriversName);
...
motor_N = Motor(EN, IN1 , IN2, ShieldDriversName);

motorList_1 = { {1, motor}, {2, motor},..., {P, motor_P}};
motorList_2 = { {P+1, motor}, {P+2, motor},..., {K, motor_K}};
....
motorList_M = { {K+1, motor}, {K+2, motor},..., {N, motor_N}};

motodriver_1 = MotoDriver(motorList_1);
motodriver_2 = MotoDriver(motorList_2);
...
motodriver_M = MotoDriver(motorList_N);
```

Where:
* N - amount of motors abstractions which you would to be created.
* M - amount of the **MotoDriver** instances for the **Motor** objects controlling.
* EN - PWM pin number connected to Enable pin of the motor driver module. If you using jumper instead of PWM pin, EN equal -1.
For other cases it might be EN=IN1 or EN=IN2 (see case 3).
* IN1 and IN2 - Arduino digital pin numbers connected to Input pins of the motor driver module.
* ShieldDriversName - Type of the motor driver module current motor connected is. If not stated, it will be Undefined.
* motorList - List of all **Motor** instances with their own IDs connected to current **MotoDriver**. Each of the motors must be assigned as an unique numerical identifier.

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

For example in general view, when N=4, M=1.

```
#include "motodriver.h"

Motor motor_1;
Motor motor_2;
Motor motor_3;
Motor motor_4;
std::map<uint8_t, Motor> motorList_1;
MotoDriver motodriver_1;

void setup() {
  motor_1 = Motor(9,9,11,ShieldDriversNames::MX1508); // Two PWM PINS MOTORS, LIKE A MX1508
  motor_2 = Motor(10, 8, 0, ShieldDriversNames::TB6612);
  motor_3 = Motor(3,4,0, ShieldDriversNames::TB6612);
  motor_4 = Motor(5,6,7, ShieldDriversNames::L298N);
  
  motorList_1 = { {1, motor_1}, {2, motor_2}, {3, motor_3}, {4, motor_4}};
  motodriver_1 = MotoDriver(motorList_1);
}

void loop() {

}

```
## Motors rotation
The **MotoDriver** class can drive each motor individually or drive them as a group. After initialization the all motors are in the zero group.
Any of the motors can be transferred to another group. To do this, you need to call the method **MotorToGroup**. The method is called as follows.

```
MotorToGroup(motorId, groupId);
```

Where:
* motorId - unique motor identifier;
* groupId - unique group identifier.

You can call this method both at the beginning of initialization of objects in the body of the **setup** function and during the operation of your motor control algorithm in the **loop** function or interrupts functions.

...

## Lazy MotoDriver methods (deprecated)

| Method        | Params                                                                | Description                                                                                 |
| ------------- | --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| Forward       | signed char **Duty cycle**, signed char **MotorID**                   | Move chosen motor forward with set duty cycle. If not stated, it will be 255.               |
| ForwardUntil  | signed char **Duty cycle**, signed char **MotorID**, short **Delay**  | Move chosen motor forward with set duty cycle and set delay. After delay end shutdown.      |
| Backward      | signed char **Duty cycle**, signed char **MotorID**                   | Move chosen motor backward with set duty cycle. If not stated, it will be 255.              |
| BackwardUntil | signed char **Duty cycle**, signed char **MotorID**, short **Delay**  | Move chosen motor backward with set duty cycle and set delay. After delay end shutdown.     |
| Shutdown      | signed char **MotorID**                                               | Shutdown chosen motor.                                                                      |

                        |

## Sketch examples

You can find several examples of using Motodriver library with wiring schemas in [Examples](https://github.com/Runsolar/motodriver/tree/main/examples) folder of this repository.

## Authors

[D.Wolf](https://github.com/Runsolar)   
[Arxaid](https://github.com/Arxaid)   
[NeviDimka](https://github.com/dmitrii591)   
