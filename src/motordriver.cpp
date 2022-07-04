// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#include "motodriver.h"

#pragma region Motor

Motor::Motor() = default;

Motor::Motor(const int8_t &_pwm_pin, const int8_t &_direction_pin1, const int8_t &_direction_pin2,
             const int8_t &_dcycle, const int8_t &_direct, const std::string &_shield_driver_name){
       
    if(_shield_driver_name == "L298N"){

        shield_driver_type = (int8_t)ShieldDriversNames::L298N;
        pwm_pin = _pwm_pin;
        direction_pin1 = _direction_pin1;
        direction_pin2 = _direction_pin2;
        dcycle = _dcycle;
        direct = MoveDirection::SHUTDOWN;
        isMoving = false;

        pinMode(pwm_pin, OUTPUT);
        pinMode(direction_pin1, OUTPUT);
        pinMode(direction_pin2, OUTPUT);
    }
    
    if(_shield_driver_name == "OTHER"){

        shield_driver_type = (int8_t)ShieldDriversNames::OTHER;
        direction_pin1 = _direction_pin1;
        direction_pin2 = _direction_pin2;
        dcycle = 255;
        direct = MoveDirection::SHUTDOWN;
        isMoving = false;

        pinMode(direction_pin1, OUTPUT);
        pinMode(direction_pin2, OUTPUT);
    }
}

Motor::~Motor(){}

void Motor::set_direct(int8_t _direct){
    direct = _direct;
}

void Motor::set_dcycle(int8_t _dcycle){
    dcycle = _dcycle;
}

int8_t Motor::get_direct(){
    return direct;
}

int8_t Motor::get_dcycle(){
    return dcycle;
}

void Motor::print8_t_driver_name(){
    std::cout << "Motor driver name is " << shield_driver_name << "\n";
}

void Motor::Rotate(){
    digitalWrite(direction_pin1, direct);
    analogWrite(pwm_pin, dcycle);

    isMoving = true;
}

void Motor::Forward(){
    digitalWrite(direction_pin1, HIGH);
    digitalWrite(direction_pin2, LOW);
    analogWrite(pwm_pin, dcycle);

    direct = MoveDirection::FORWARD;
    isMoving = true;
}

void Motor::Backward(){
    digitalWrite(direction_pin1, LOW);
    digitalWrite(direction_pin2, HIGH);
    analogWrite(pwm_pin, dcycle);

    direct = MoveDirection::BACKWARD;
    isMoving = true;
}

void Motor::Shutdown(){
    digitalWrite(direction_pin1, LOW);
    digitalWrite(direction_pin2, LOW);
    analogWrite(pwm_pin, dcycle);

    direct = MoveDirection::SHUTDOWN;
    isMoving = false;
}

#pragma endregion
#pragma region MotoDriver

MotoDriver::MotoDriver() = default; 

MotoDriver::MotoDriver(std::map<int8_t, Motor> &_motors) {
    motors = _motors;
}

MotoDriver::~MotoDriver(){}

void MotoDriver::clockWise(const int8_t &_dcycle, const int8_t &motorId){     
    motors[motorId].direction_() = 1;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();   
}

void MotoDriver::counterclockWise(const int8_t &_dcycle, const int8_t &motorId){     
    motors[motorId].direction_() = 0;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();   
}

#pragma endregion