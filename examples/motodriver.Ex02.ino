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
Motor motor1 = Motor(10,9,8,ShieldDriversNames::L298N);
Motor motor2 = Motor(3,5,4,ShieldDriversNames::L298N);

// Create list of Motor instances
// and create MovingGroup class instance as below.
std::vector<Motor> motorList = {motor1, motor2};

MovingGroup movingGroup = MovingGroup(motorList);

void loop() {

    // Move forward with maximum duty cycle during second.
    movingGroup.GroupForwardUntil(255, 1000);
    
    // Move backward with low duty cycle during half a second.
    movingGroup.GroupBackwardUntil(50, 500);
}