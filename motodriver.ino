// This file is part of the Motodriver project.
//
// Feel free to use, copy, modify, merge, and publish this software.

#include "src/motodriver.h"

// After setup function create Motor class instances 
// for your DC motors with chosen Arduino pin numbers.
MotoDriver motodriver;
Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;
std::map<uint8_t, Motor> motorList;

void setup() {
  motor1 = Motor(9,9,11,ShieldDriversNames::MX1508); // Two PWM PINS MOTORS, LIKE A MX1508
  motor2 = Motor(10, 8, 0, ShieldDriversNames::TB6612);
  motor3 = Motor(3,4,0, ShieldDriversNames::TB6612);
  motor4 = Motor(5,6,7, ShieldDriversNames::L298N);
  
  motorList = { {1, motor1}, {2, motor2}, {3, motor3}, {4, motor4}};
  motodriver = MotoDriver(motorList);
  
  motodriver.MotorToGroup(1, 1);
  motodriver.MotorToGroup(2, 1);
  motodriver.MotorToGroup(3, 2);
  motodriver.MotorToGroup(4, 2);
  
  //Serial.begin(9600);
}


void loop() {

  //motodriver.Clockwise_Rotation(255, 1);
  //motodriver.Clockwise_Rotation(255, 2);
  //motodriver.Clockwise_Rotation(255, 3);
  //motodriver.Clockwise_Rotation(255, 4);
  
  //motodriver.Counterclockwise_Rotation(255, 1);
  
  motodriver.Clockwise_Group_Rotation(255, 1);
  motodriver.Counterclockwise_Group_Rotation(255, 2);

}
