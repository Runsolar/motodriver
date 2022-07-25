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
In the first place you should to declarate a **Motor** class object(s).
It is preferable to do this outside of the setup and loop functions.
```
Motor motor1;
Motor motor2;
...
Motor motorN;
```

In the second place you should to declarate a **Motor Driver** class object(s) and to create a class template collections of the motors.
Also declare it out of the setup and loop functions.
```
For ex.
MotoDriver motodriver;
std::map<uint8_t, Motor> motorList;
```

In the next step, in the setup function you should to initialize your's created objects before.

```
motor1 = Motor(EN, IN1 , IN2, ShieldDriversName);
motor2 = Motor(EN, IN1 , IN2, ShieldDriversName);
...
motorN = Motor(EN, IN1 , IN2, ShieldDriversName);

motorList = { {1, motor}, {2, motor},..., {N, motorN}};
motodriver = MotoDriver(motorList);
```

Where:
* EN - Arduino PWM pin number connected to Enable pin of the motor driver module. If you using jumper instead of PWM pin, EN equal -1.
For other cases it might be EN=IN1 or EN=IN2 (see case 3).
* IN1 and IN2 - Arduino digital pin numbers connected to Input pins of the motor driver module.
* ShieldDriversName - Type of the motor driver module current motor connected is. If not stated, it will be Undefined.
* motorList - List of all Motor instances with their own IDs connected to current MotoDriver.

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


```
For ex.
motor1 = Motor(9,9,11,ShieldDriversNames::MX1508); // Two PWM PINS MOTORS, LIKE A MX1508
motor2 = Motor(10, 8, 0, ShieldDriversNames::TB6612);
motor3 = Motor(3,4,0, ShieldDriversNames::TB6612);
motor4 = Motor(5,6,7, ShieldDriversNames::L298N);
motorList = { {1, motor1}, {2, motor2}, {3, motor3}, {4, motor4}};
motodriver = MotoDriver(motorList);
```

In general view you'll get the below code.
```
#include "motodriver.h"

Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;
std::map<uint8_t, Motor> motorList;
MotoDriver motodriver;

void setup() {
  motor1 = Motor(9,9,11,ShieldDriversNames::MX1508); // Two PWM PINS MOTORS, LIKE A MX1508
  motor2 = Motor(10, 8, 0, ShieldDriversNames::TB6612);
  motor3 = Motor(3,4,0, ShieldDriversNames::TB6612);
  motor4 = Motor(5,6,7, ShieldDriversNames::L298N);
  
  motorList = { {1, motor1}, {2, motor2}, {3, motor3}, {4, motor4}};
  motodriver = MotoDriver(motorList);
}

void loop() {

}

```
## Rotate the motors


## Lazy MotoDriver methods

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
