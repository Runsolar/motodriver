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
             dcycle(100), direct(MoveDirection::SHUTDOWN){
    
    switch (_shield_driver_type){
    case L298N:
        shield_driver_name = "L298N 2X Motor Shield";

        pwm_pin = _pwm_pin;
        pinMode(pwm_pin, OUTPUT);
        
        if(direction_pin2 == 0){
            pinMode(direction_pin1, OUTPUT);
            direction_pin_flag = false;
        }
        if(direction_pin2 != 0){
            pinMode(direction_pin1, OUTPUT);
            pinMode(direction_pin2, OUTPUT);
            direction_pin_flag = true;
        }
        break;
    default:
        shield_driver_name = "Undefined";

        if(direction_pin2 == 0){
            pinMode(direction_pin1, OUTPUT);
            direction_pin_flag = false;
        }
        if(direction_pin2 != 0){
            pinMode(direction_pin1, OUTPUT);
            pinMode(direction_pin2, OUTPUT);
            direction_pin_flag = true;
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

void Motor::print8_t_driver_name(){
    std::cout << "Motor driver name is " << shield_driver_name << "\n";
}

void Motor::Rotate(){
    if(direction_pin_flag){
        switch (direct){
        case MoveDirection::FORWARD:
            digitalWrite(direction_pin1, HIGH);
            digitalWrite(direction_pin2, LOW);
        break;
        case MoveDirection::BACKWARD: 
            digitalWrite(direction_pin1, LOW);
            digitalWrite(direction_pin2, HIGH);
        break;
        default:
            digitalWrite(direction_pin1, LOW);
            digitalWrite(direction_pin2, LOW);
        break;
        }
    }
    if(!direction_pin_flag){
        digitalWrite(direction_pin1, direct);
    }

    analogWrite(pwm_pin, dcycle);
}

void Motor::Shutdown(){
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

void MotoDriver::Backward(const int8_t &_dcycle, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::BACKWARD;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
    isMoving = true;
}

void MotoDriver::BackwardUntil(const int8_t &_dcycle, const int8_t &motorId, const int16_t &_delay){     
    motors[motorId].direction_() = MoveDirection::BACKWARD;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
    isMoving = true;

    delay(_delay);

    motors[motorId].direction_() = MoveDirection::SHUTDOWN;  
    motors[motorId].Shutdown();
    isMoving = false;
}

void MotoDriver::Forward(const int8_t &_dcycle, const int8_t &motorId){     
    motors[motorId].direction_() = MoveDirection::FORWARD;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
    isMoving = true; 
}

void MotoDriver::ForwardUntil(const int8_t &_dcycle, const int8_t &motorId, const int16_t &_delay){     
    motors[motorId].direction_() = MoveDirection::FORWARD;
    motors[motorId].duty_cycle_() = _dcycle;
    motors[motorId].Rotate();  
    isMoving = true;
    
    delay(_delay);

    motors[motorId].direction_() = MoveDirection::SHUTDOWN;  
    motors[motorId].Shutdown();
    isMoving = false;
}

void MotoDriver::Shutdown(const int8_t &motorId){ 
    motors[motorId].direction_() = MoveDirection::SHUTDOWN;  
    motors[motorId].Shutdown();  
    isMoving = false; 
}

#pragma endregion
#pragma region MovingGroup Initialization

MovingGroup::MovingGroup() = default; 

MovingGroup::MovingGroup(std::vector<Motor> &_movingGroup) {
    movingGroup = _movingGroup;
}

MovingGroup::MovingGroup(){}

#pragma endregion
#pragma region MovingGroup Functions

void MovingGroup::GroupBackward(const int8_t &_dcycle){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::BACKWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;
}

void MovingGroup::GroupBackwardUntil(const int8_t &_dcycle, const int16_t &_delay){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::BACKWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;

    delay(_delay);

    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::SHUTDOWN;
        iterator.Shutdown();
    }   isMoving = false;

}

void MovingGroup::GroupForward(const int8_t &_dcycle){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::FORWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;
}

void MovingGroup::GroupForwardUntil(const int8_t &_dcycle, const int16_t &_delay){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::FORWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;

    delay(_delay);

    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::SHUTDOWN;
        iterator.Shutdown();
    }   isMoving = false;
}

void MovingGroup::GroupShutdown(){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::SHUTDOWN;
        iterator.Shutdown();
    }   isMoving = false;
}

void MovingGroup::HardTurnLeft(const int8_t &_dcycle = 50, const int16_t &_delay){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::FORWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
        groupCounter++;
    }   isMoving = true;

    switch (groupCounter){
    case 2:
        movingGroup[2].duty_cycle_() = 255;
        movingGroup[2].Rotate();
        break;
    case 3:
        movingGroup[3].duty_cycle_() = 255;
        movingGroup[3].Rotate();
        break;
    case 4:
        movingGroup[2].duty_cycle_() = 255;
        movingGroup[4].duty_cycle_() = 255;
        movingGroup[2].Rotate();
        movingGroup[4].Rotate();
        break;
    default:
        break;
    }   isMoving = true;

    delay(_delay);

    for(Motor iterator : movingGroup){
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;
}

void MovingGroup::HardTurnRight(const int8_t &_dcycle = 50, const int16_t &_delay){
    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::FORWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
        groupCounter++;
    }   isMoving = true;
    
    switch (groupCounter){
    case 2:
        movingGroup[1].duty_cycle_() = 255;
        movingGroup[1].Rotate();
        break;
    case 3:
        movingGroup[2].duty_cycle_() = 255;
        movingGroup[2].Rotate();
        break;
    case 4:
        movingGroup[1].duty_cycle_() = 255;
        movingGroup[1].duty_cycle_() = 255;
        movingGroup[3].Rotate();
        movingGroup[3].Rotate();
        break;
    default:
        break;
    }   isMoving = true;

    delay(_delay);

    for(Motor iterator : movingGroup){
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;
}

void MovingGroup::SoftTurnLeft(const int8_t &_dcycle = 50, const int8_t &_turn_dcycle, const int16_t &_delay){
    if(_dcycle + _turn_dcycle < 256){softVelocity = _dcycle + _turn_dcycle;}else{softVelocity = 255;}

    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::FORWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
        groupCounter++;
    }   isMoving = true;
    
    switch (groupCounter){
    case 2:
        movingGroup[2].duty_cycle_() = softVelocity;
        movingGroup[2].Rotate();
        break;
    case 3:
        movingGroup[3].duty_cycle_() = softVelocity;
        movingGroup[3].Rotate();
        break;
    case 4:
        movingGroup[2].duty_cycle_() = softVelocity;
        movingGroup[4].duty_cycle_() = softVelocity;
        movingGroup[2].Rotate();
        movingGroup[4].Rotate();
        break;
    default:
        break;
    }   isMoving = true;

    delay(_delay);

    for(Motor iterator : movingGroup){
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;
}

void MovingGroup::SoftTurnRight(const int8_t &_dcycle = 50, const int8_t &_turn_dcycle, const int16_t &_delay){
    if(_dcycle + _turn_dcycle < 256){softVelocity = _dcycle + _turn_dcycle;}else{softVelocity = 255;}

    for(Motor iterator : movingGroup){
        iterator.direction_() = MoveDirection::FORWARD;
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
        groupCounter++;
    }   isMoving = true;
    
    switch (groupCounter){
    case 2:
        movingGroup[1].duty_cycle_() = softVelocity;
        movingGroup[1].Rotate();
        break;
    case 3:
        movingGroup[2].duty_cycle_() = softVelocity;
        movingGroup[2].Rotate();
        break;
    case 4:
        movingGroup[1].duty_cycle_() = softVelocity;
        movingGroup[1].duty_cycle_() = softVelocity;
        movingGroup[3].Rotate();
        movingGroup[3].Rotate();
        break;
    default:
        break;
    }   isMoving = true;

    delay(_delay);

    for(Motor iterator : movingGroup){
        iterator.duty_cycle_() = _dcycle;
        iterator.Rotate();
    }   isMoving = true;
}

#pragma endregion