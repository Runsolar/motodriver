// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#include "motodriver.h"

#pragma region Motor Initialization

Motor::Motor() = default;

Motor::Motor(const int8_t &_pwm_pin, 
             const int8_t &_direction_pin1, const int8_t &_direction_pin2 = 0,
             const ShieldDriversNames &_shield_driver_type = ShieldDriversNames::OTHER):
             direction_pin1(_direction_pin1), direction_pin2(_direction_pin2),
             dcycle(0){
    
    switch (_shield_driver_type){
    case L298N:
        shield_driver_name = "L298N 2X Motor Shield";
        pwm_pin = _pwm_pin;
        pinMode(pwm_pin, OUTPUT);
        pinMode(direction_pin1, OUTPUT);
        pinMode(direction_pin2, OUTPUT);
        break;
        
    case TB6612:
        shield_driver_name = "TB6612 Motor Driver";
        pwm_pin = _pwm_pin;
        pinMode(pwm_pin, OUTPUT);
        pinMode(direction_pin1, OUTPUT);
        break;

    default:
        shield_driver_name = "Undefined";

        if(direction_pin2 != 0){
            pwm_pin = _pwm_pin;
            pinMode(pwm_pin, OUTPUT);
            pinMode(direction_pin1, OUTPUT);
            pinMode(direction_pin2, OUTPUT);
            break;
        }
        else{
            pwm_pin = _pwm_pin;
            pinMode(pwm_pin, OUTPUT);
            pinMode(direction_pin1, OUTPUT);
        }
        break;
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

void Motor::print8_t_driver_name() {
    std::cout << "Motor driver name is " << shield_driver_name << "\n";
}

void Motor::SetRotorDirection(){
    if(direction_pin2 != 0) {

        switch (direct){
            case RotorDirection::CLOCKWISE:
                digitalWrite(direction_pin1, LOW);
                digitalWrite(direction_pin2, HIGH);
                break;
            case RotorDirection::COUNTERCLOCKWISE: 
                digitalWrite(direction_pin1, HIGH);
                digitalWrite(direction_pin2, LOW);
                break;
            default:
                digitalWrite(direction_pin1, LOW);
                digitalWrite(direction_pin2, LOW);
                break;
        }
    }
    else {
        digitalWrite(direction_pin1, direct);
    }
}

void Motor::Rotate() {
    SetRotorDirection();
    analogWrite(pwm_pin, dcycle);
}

void Motor::Halt() {
    digitalWrite(direction_pin1, LOW);
    digitalWrite(direction_pin2, LOW);
    analogWrite(pwm_pin, 0);
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

void MotoDriver::Clockwise_Rotation(const int8_t &_dcycle, const int8_t &motorId) {     
    motors[motorId].direction_() = RotorDirection::CLOCKWISE;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate(); 
}

void MotoDriver::Counterclockwise_Rotation(const int8_t &_dcycle, const int8_t &motorId) {     
    motors[motorId].direction_() = RotorDirection::COUNTERCLOCKWISE;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
}

void MotoDriver::Halt(const int8_t &motorId) { 
    //motors[motorId].direction_() = MoveDirection::SHUTDOWN;  
    motors[motorId].duty_cycle_() = 0;
    motors[motorId].Halt(); 
}

//Methods for groups
void MotoDriver::MotorToGroup(const int8_t &motorId, const int8_t &groupId) {
    motors[motorId].groupId = groupId;
}


void MotoDriver::SetGroupDirection(const int8_t &groupId, const int8_t &direction) {
    for(auto& motor : motors){
        if(motor.second.groupId == groupId){
            motor.second.direction_() = direction;
        }
    }
}


void MotoDriver::Clockwise_Group_Rotation(const int8_t &_dcycle, const int8_t &groupId) {
    for(auto& motor : motors){
        if(motor.second.groupId == groupId){
            Clockwise_Rotation(_dcycle, motor.first);
        }
    }
}


void MotoDriver::Counterclockwise_Group_Rotation(const int8_t &_dcycle, const int8_t &groupId) {
    for(auto& motor : motors){
        if(motor.second.groupId == groupId){
            Counterclockwise_Rotation(_dcycle, motor.first);
        }
    }
}
