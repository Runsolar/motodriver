// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#include "motodriver.h"

#pragma region Motor Initialization

Motor::Motor() = default;

Motor::Motor(const ShieldDriversNames &_shield_driver_type, const int8_t &_pwm_pin, 
             const int8_t &_direction_pin1):direction_pin1(_direction_pin1),
             dcycle(100), direct(MoveDirection::SHUTDOWN){
                
    if(_shield_driver_type == (int8_t)ShieldDriversNames::L298N){
        shield_driver_name = "L298N 2X Motor Shield";
        pwm_pin = _pwm_pin;
        pinMode(pwm_pin, OUTPUT);
        pinMode(direction_pin1, OUTPUT);
    }
    
    if(_shield_driver_type == (int8_t)ShieldDriversNames::OTHER){
        shield_driver_name = "Undefined";
        pinMode(direction_pin1, OUTPUT);
    }
}

Motor::Motor(const ShieldDriversNames &_shield_driver_type, const int8_t &_pwm_pin, 
             const int8_t &_direction_pin1, const int8_t &_direction_pin2):
             direction_pin1(_direction_pin1), direction_pin2(_direction_pin2),
             dcycle(100), direct(MoveDirection::SHUTDOWN){
       
    if(_shield_driver_type == (int8_t)ShieldDriversNames::L298N){
        shield_driver_name = "L298N 2X Motor Shield";
        pwm_pin = _pwm_pin;
        pinMode(pwm_pin, OUTPUT);
        pinMode(direction_pin1, OUTPUT);
        pinMode(direction_pin2, OUTPUT);
    }
    
    if(_shield_driver_type == (int8_t)ShieldDriversNames::OTHER){
        shield_driver_name = "Undefined";
        pinMode(direction_pin1, OUTPUT);
        pinMode(direction_pin2, OUTPUT);
    }
}

Motor::~Motor(){}

#pragma endregion;
#pragma region Motor Accessors

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

#pragma endregion
#pragma region Motor Functions

void Motor::print8_t_driver_name(){
    std::cout << "Motor driver name is " << shield_driver_name << "\n";
}
void Motor::Rotate(){
    digitalWrite(direction_pin1, direct);
    analogWrite(pwm_pin, dcycle);  
}
void Motor::Shutdown(){
    digitalWrite(direction_pin1, MoveDirection::SHUTDOWN);
    analogWrite(pwm_pin, dcycle);
}

#pragma endregion
#pragma region MotoDriver Initialization

MotoDriver::MotoDriver() = default; 

MotoDriver::MotoDriver(std::map<int8_t, Motor> &_motors) {
    motors = _motors;
}

MotoDriver::~MotoDriver(){}

#pragma endregion
#pragma region MotoDriver Functions

void MotoDriver::Backward(const int8_t &_dcycle, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::BACKWARD;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
    isMoving = true;
}
void MotoDriver::Forward(const int8_t &_dcycle, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::FORWARD;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
    isMoving = true; 
}
void MotoDriver::Shutdown(const int8_t &motorId){     
    motors[motorId].Shutdown();  
    isMoving = false; 
}

#pragma endregion