// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software.

#include <Arduino.h>
#include "motodriver.h"

void setup() {
    Serial.begin(9600);
}

// After setup function create Motor class instances 
// for your DC motors with chosen Arduino pin numbers.
Motor motor1 = Motor(6,5,0,ShieldDriversNames::L298N); // Top left
Motor motor2 = Motor(3,4,0,ShieldDriversNames::L298N); // Top right
Motor motor3 = Motor(11,10,0,ShieldDriversNames::L298N); // Down left
Motor motor4 = Motor(9,8,0,ShieldDriversNames::L298N); // Down right

// Create list of Motor instances
// and create MovingGroup class instance as below.
std::vector<Motor> motorList = {motor1, motor2, motor3, motor4};

MovingGroup movingGroup = MovingGroup(motorList);

void loop() {

    // Move forward with maximum duty cycle during second.
    movingGroup.GroupForwardUntil(255, 1000);

    // Slow down before turn.
    movingGroup.GroupForwardUntil(100, 300);

    // Turn left with maximum possible angular velocity via HardTurn function.
    movingGroup.HardTurnLeft(100, 500);

    // Turn right with slower angualar velosity but longer turn time via SoftTurn function.
    movingGroup.SoftTurnRight(100, 50, 1000);
}