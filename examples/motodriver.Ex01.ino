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

// Create map container with Motor instances and their IDs
// and create MotoDriver class instance as below.
std::map<int8_t, Motor> motorList = { {1, motor1}, {2, motor2} };
MotoDriver motodriver = MotoDriver(motorList);

void loop() {

    // Move forward first motor with maximum duty cycle during second.
    motodriver.ForwardUntil(255, 1, 1000);

    // Move forward second motor with maximum duty cycle during second.
    motodriver.ForwardUntil(255, 2, 1000);
    
    // Move backward first motor with low duty cycle during half a second.
    motodriver.BackwardUntil(50, 1, 500);
}