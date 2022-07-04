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
}

void Motor::Shutdown(){
    digitalWrite(direction_pin1, LOW);
    digitalWrite(direction_pin2, LOW);
    analogWrite(pwm_pin, dcycle);
}

#pragma endregion
#pragma region MotorX2

MotorX2::MotorX2() = default;

MotorX2::MotorX2(const int8_t &_pwm_pin_A, const int8_t &_pwm_pin_B,
                 const int8_t &_direction_pin1_A, const int8_t &_direction_pin2_A,
                 const int8_t &_direction_pin1_B, const int8_t &_direction_pin2_B,
                 const int8_t &_dcycle_A, const int8_t &_dcycle_B,
                 const int8_t &_direct,
                 const std::string &_shield_driver_name_A, const std::string &_shield_driver_name_B):
                 motorA(_pwm_pin_A, _direction_pin1_A, _direction_pin2_A, _dcycle_A,
                 _direct, _shield_driver_name_A), 
                 motorB(_pwm_pin_B, _direction_pin1_B, _direction_pin2_B, _dcycle_B,
                 _direct, _shield_driver_name_B){}

MotorX2::~MotorX2(){}

void MotorX2::set_direct(int8_t _direct){
    direct = _direct;
}

void MotorX2::set_dcycle_A(int8_t _dcycle_A){
    dcycleA = _dcycle_A;
}

void MotorX2::set_dcycle_B(int8_t _dcycle_B){
    dcycleB = _dcycle_B;
}

int8_t MotorX2::get_direct(){
    return direct;
}

int8_t MotorX2::get_dcycle_A(){
    return dcycleA;
}

int8_t MotorX2::get_dcycle_B(){
    return dcycleB;
}

void MotorX2::print8_t_driver_names(){
    std::string outputData = "First motor driver name is " + shield_driver_name_A + "\n" + 
                             "Second motor driver name is " + shield_driver_name_B + "\n";
    std::cout << outputData; 
}

void MotorX2::RotateA(){
    motorA.Rotate();
}

void MotorX2::RotateB(){
    motorB.Rotate();
}

void MotorX2::ShutdownA(){
    motorA.Shutdown();
}

void MotorX2::ShutdownB(){
    motorB.Shutdown();
}

#pragma endregion
#pragma region MotoDriver

MotoDriver::MotoDriver() = default; 

MotoDriver::MotoDriver(std::map<int8_t, Motor> &_motors) {
    motors = _motors;
}

MotoDriver::~MotoDriver(){}

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
    motors[motorId].direction_() = MoveDirection::SHUTDOWN;
    motors[motorId].Shutdown();  
    
    isMoving = false; 
}

#pragma endregion
#pragma region MotoDriverX2

MotoDriverX2::MotoDriverX2() = default; 

MotoDriverX2::MotoDriverX2(std::map<int8_t, MotorX2> &_motors) {
    motors = _motors;
}

MotoDriverX2::~MotoDriverX2(){}

void MotoDriverX2::BackwardA(const int8_t &_dcycleA, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::BACKWARD;
    motors[motorId].duty_cycle_A_() = _dcycleA;
    motors[motorId].RotateA();  

    isMoving = true; 
}

void MotoDriverX2::BackwardB(const int8_t &_dcycleB, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::BACKWARD;
    motors[motorId].duty_cycle_B_() = _dcycleB;
    motors[motorId].RotateB();  

    isMoving = true; 
}

void MotoDriverX2::BackwardBoth(const int8_t &_dcycleA, const int8_t &_dcycleB, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::BACKWARD;
    motors[motorId].duty_cycle_A_() = _dcycleA;
    motors[motorId].RotateA(); 
    motors[motorId].duty_cycle_B_() = _dcycleB;
    motors[motorId].RotateB();  

    isMoving = true; 
}

void MotoDriverX2::ForwardA(const int8_t &_dcycleA, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::FORWARD;
    motors[motorId].duty_cycle_A_() = _dcycleA;
    motors[motorId].RotateA();  

    isMoving = true; 
}

void MotoDriverX2::ForwardB(const int8_t &_dcycleB, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::FORWARD;
    motors[motorId].duty_cycle_B_() = _dcycleB;
    motors[motorId].RotateB();  

    isMoving = true; 
}

void MotoDriverX2::ForwardBoth(const int8_t &_dcycleA, const int8_t &_dcycleB, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::FORWARD;
    motors[motorId].duty_cycle_A_() = _dcycleA;
    motors[motorId].RotateA(); 
    motors[motorId].duty_cycle_B_() = _dcycleB;
    motors[motorId].RotateB();  

    isMoving = true; 
}

void MotoDriverX2::ShutdownA(const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::SHUTDOWN;
    motors[motorId].ShutdownA();  

    isMoving = false; 
}

void MotoDriverX2::ShutdownB(const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::SHUTDOWN;
    motors[motorId].ShutdownB();  

    isMoving = false; 
}

void MotoDriverX2::ShutdownBoth(const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::SHUTDOWN;
    motors[motorId].ShutdownA(); 
    motors[motorId].ShutdownB();  

    isMoving = false; 
}

#pragma endregion