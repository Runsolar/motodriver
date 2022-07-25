// This file is part of the Motodriver project.
//
// Feel free to use, copy, modify, merge, and publish this software

#include "motodriver.h"

#pragma region Motor Initialization

Motor::Motor() = default;

Motor::Motor(const uint8_t &_pwm_pin,
             const uint8_t &_direction_pin1, const uint8_t &_direction_pin2,
             const ShieldDriversNames &_shield_driver_type):
             pwm_pin(_pwm_pin),
             direction_pin1(_direction_pin1),
             direction_pin2(_direction_pin2),
             shield_driver_type(_shield_driver_type),
             dcycle(0){
    

    switch (shield_driver_type){

        case MX1508:
            shield_driver_name = "MX1508";
            pinMode(direction_pin1, OUTPUT);
            pinMode(direction_pin2, OUTPUT);
            break;

        case L298N:
            shield_driver_name = "L298N 2X Motor Shield";
            pinMode(pwm_pin, OUTPUT);
            pinMode(direction_pin1, OUTPUT);
            pinMode(direction_pin2, OUTPUT);
            break;
            
        case TB6612:
            shield_driver_name = "TB6612 Motor Driver";
            pinMode(pwm_pin, OUTPUT);
            pinMode(direction_pin1, OUTPUT);
            break;

        default:
            shield_driver_name = "Undefined";

            if(direction_pin2 != 0){
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

void Motor::set_direct(uint8_t _direct){
    direct = _direct;
}

void Motor::set_dcycle(uint8_t _dcycle){
    dcycle = _dcycle;
}

uint8_t Motor::get_direct(){
    return direct;
}

uint8_t Motor::get_dcycle(){
    return dcycle;
}

#pragma endregion
#pragma region Motor Functions

void Motor::print_driver_name() {
    std::cout << "Motor driver name is " << shield_driver_name << "\n";
}

void Motor::SetRotorDirection(){
    switch (direct){
        case RotorDirection::CLOCKWISE:
            //For two PWM pins motors like a MX1508
            if(shield_driver_type == MX1508){             
                pwm_pin = direction_pin2;
                analogWrite(direction_pin1, LOW);
            }
            else{
                digitalWrite(direction_pin1, LOW);
                digitalWrite(direction_pin2, HIGH);
            }

            break;
        case RotorDirection::COUNTERCLOCKWISE: 

            //For two PWM pins motors like a MX1508
            if(shield_driver_type == MX1508){
                pwm_pin = direction_pin1;
                analogWrite(direction_pin2, LOW);
            }
            else{
                digitalWrite(direction_pin1, HIGH);
                digitalWrite(direction_pin2, LOW);
            }

            break;
        default:
            digitalWrite(direction_pin1, LOW);
            digitalWrite(direction_pin2, LOW);
            break;
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

MotoDriver::MotoDriver(std::map<uint8_t, Motor> &_motors) {
    motors = _motors;
}

MotoDriver::~MotoDriver(){}

#pragma endregion
#pragma region MotoDriver Functions

void MotoDriver::Clockwise_Rotation(const uint8_t &_dcycle, const uint8_t &motorId) {     
    motors[motorId].direction_() = RotorDirection::CLOCKWISE;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate(); 
}

void MotoDriver::Counterclockwise_Rotation(const uint8_t &_dcycle, const uint8_t &motorId) {     
    motors[motorId].direction_() = RotorDirection::COUNTERCLOCKWISE;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
}

void MotoDriver::Halt(const uint8_t &motorId) { 
    //motors[motorId].direction_() = MoveDirection::SHUTDOWN;  
    motors[motorId].duty_cycle_() = 0;
    motors[motorId].Halt(); 
}

//Methods for groups
void MotoDriver::MotorToGroup(const uint8_t &motorId, const uint8_t &groupId) {
    motors[motorId].groupId = groupId;
}


void MotoDriver::SetGroupDirection(const uint8_t &groupId, const uint8_t &direction) {
    for(auto& motor : motors){
        if(motor.second.groupId == groupId){
            motor.second.direction_() = direction;
        }
    }
}


void MotoDriver::Clockwise_Group_Rotation(const uint8_t &_dcycle, const uint8_t &groupId) {
    for(auto& motor : motors){
        if(motor.second.groupId == groupId){
            Clockwise_Rotation(_dcycle, motor.first);
        }
    }
}


void MotoDriver::Counterclockwise_Group_Rotation(const uint8_t &_dcycle, const uint8_t &groupId) {
    for(auto& motor : motors){
        if(motor.second.groupId == groupId){
            Counterclockwise_Rotation(_dcycle, motor.first);
        }
    }
}
