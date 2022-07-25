// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#pragma once

#include <ArduinoSTL.h>
#include <map>
#include <string>
#include "type-declaration.h"

class Motor{
    private:
        uint8_t pwm_pin;
        uint8_t direction_pin1;
        uint8_t direction_pin2;
        uint8_t dcycle;
        uint8_t direct;
        
        //boolean direction_pin_flag;
    public:
        uint8_t motorID;
        uint8_t groupId = 0;
        uint8_t shield_driver_type;
        std::string shield_driver_name;
        
        #pragma region Initialization

        /**
        * @brief Motor object constructor by default.
        */
        Motor(); 

        /**
        * @brief Motor object constructor.
        * @param pwm_pin PWM (Pulse-width modulation) controller pin number.
        * @param direction_pin1 First rotating direction pin number.
        * @param direction_pin2 Second rotating direction pin number (if exists).
        * @param shield_driver_name Name of your motor driver shield.
        */
        Motor(const uint8_t &_pwm_pin,
                const uint8_t &_direction_pin1, const uint8_t &_direction_pin2, 
                const ShieldDriversNames &_shield_driver_type);

        /**
        * @brief Motor object destructor by default.
        */
        ~Motor();

        #pragma endregion
        #pragma region Accessors

        /**
        * @brief Set new direction.
        */
        void set_direct(uint8_t _direct);

        /**
        * @brief Set new duty cycle.
        */
        void set_dcycle(uint8_t _dcycle);

        /**
        * @brief Get current direction.
        */
        uint8_t get_direct();

        /**
        * @brief Get current duty cycle.
        */
        uint8_t get_dcycle();

        /**
        * @brief Get current direction by link.
        */
        uint8_t &direction_() {
            return direct;
        }

        /**
        * @brief Get current duty cycle by link.
        */
        uint8_t &duty_cycle_() {
            return dcycle;
        }

        #pragma endregion
        #pragma region Functions

        /**
        * @result Shield driver name.
        */        
        void print_driver_name();

        /**
        * @result Set direction for the rotor
        */  
        void SetRotorDirection();

        /**
        * @brief Stop moving.
        */
        void Halt();

        /**
        * @brief Move with set direction and duty cycle.
        */
        void Rotate();  

        #pragma endregion
};

class MotoDriver{
    private:
        std::map<uint8_t, Motor> motors;
        boolean isMoving;
    public:
        #pragma region Initialization

        /**
        * @brief MotoDriver object constructor by default.
        */
        MotoDriver();

        /**
        * @brief MotoDriver object constructor.
        * @param motors Motor instance list.
        */
        MotoDriver(std::map<uint8_t, Motor> &_motors);

        /**
        * @brief MotoDriver object destructor by default.
        */
        ~MotoDriver();

        #pragma endregion
        #pragma region Functions

        /**
        * @brief Moving to forward/backward.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */

        void Clockwise_Rotation(const uint8_t &_dcycle, const uint8_t &motorId);
        void Counterclockwise_Rotation(const uint8_t &_dcycle, const uint8_t &motorId);

        /**
        * @brief Stop moving.
        * @param motorID Current motor you want to stop.
        */
        void Halt(const uint8_t &motorId);

        //The group methods
        //void addGroup(uint8_t groupId);
        //Move a morotor to the group (a default group - 0)
        void MotorToGroup(const uint8_t &motorId, const uint8_t &groupId);
        void SetGroupDirection(const uint8_t &groupId, const uint8_t &direction);

        void Clockwise_Group_Rotation(const uint8_t &_dcycle, const uint8_t &groupId);
        void Counterclockwise_Group_Rotation(const uint8_t &_dcycle, const uint8_t &groupId);


        #pragma endregion
};
