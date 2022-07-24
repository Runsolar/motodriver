// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software.

#include "src/motodriver.h"

// After setup function create Motor class instances 
// for your DC motors with chosen Arduino pin numbers.
Motor motor1 = Motor(10,11,12,ShieldDriversNames::L298N);
Motor motor2 = Motor(3,4,0, ShieldDriversNames::TB6612);

// Create map container with Motor instances and their IDs
// and create MotoDriver class instance as below.
std::map<int8_t, Motor> motorList = { {1, motor1}, {2, motor2} };
MotoDriver motodriver = MotoDriver(motorList);

void setup() {
  motodriver.MotorToGroup(2, 1);
}


void loop() {
  
  //motodriver.Clockwise_Rotation(255, 2);
  //motodriver.Counterclockwise_Rotation(255, 1);

  motodriver.Clockwise_Group_Rotation(255, 0);
  motodriver.Counterclockwise_Group_Rotation(255, 1);

  delay(3000);

  
}
