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
        int8_t pwm_pin;
        int8_t direction_pin1;
        int8_t direction_pin2;
        int8_t dcycle;
        int8_t direct;
        boolean direction_pin_flag;
    public:
        int8_t motorID;
        int8_t shield_driver_type;
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
        Motor(const int8_t &_pwm_pin, const int8_t &_direction_pin1, const int8_t &_direction_pin2, 
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
        void set_direct(int8_t _direct);

        /**
        * @brief Set new duty cycle.
        */
        void set_dcycle(int8_t _dcycle);

        /**
        * @brief Get current direction.
        */
        int8_t get_direct();

        /**
        * @brief Get current duty cycle.
        */
        int8_t get_dcycle();

        /**
        * @brief Get current direction by link.
        */
        int8_t &direction_() {
            return direct;
        }

        /**
        * @brief Get current duty cycle by link.
        */
        int8_t &duty_cycle_() {
            return dcycle;
        }

        #pragma endregion
        #pragma region Functions

        /**
        * @result Shield driver name.
        */        
        void print8_t_driver_name();

        /**
        * @brief Stop moving.
        */
        void Shutdown();

        /**
        * @brief Move with set direction and duty cycle.
        */
        void Rotate();

        #pragma endregion

};

class MotoDriver{
    private:
        std::map<int8_t, Motor> motors;
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
        MotoDriver(std::map<int8_t, Motor> &_motors);

        /**
        * @brief MotoDriver object destructor by default.
        */
        ~MotoDriver();

        #pragma endregion
        #pragma region Functions

        /**
        * @brief Move backward.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void Backward(const int8_t &_dcycle, const int8_t &motorId);

        /**
        * @brief Move backward with set delay.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        * @param delay Moving time (milliseconds).
        */
        void BackwardUntil(const int8_t &_dcycle, const int8_t &motorId, const int16_t &_delay);

        /**
        * @brief Move forward.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void Forward(const int8_t &_dcycle, const int8_t &motorId);

        /**
        * @brief Move forward with set delay.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        * @param delay Moving time (milliseconds).
        */
        void ForwardUntil(const int8_t &_dcycle, const int8_t &motorId, const int16_t &_delay);

        /**
        * @brief Stop moving.
        * @param motorID Current motor you want to stop.
        */
        void Shutdown(const int8_t &motorId);

        #pragma endregion
};

class MovingGroup{
    private:
        std::vector<Motor> movingGroup;
        int8_t groupCounter;
        int8_t softVelocity;
        boolean isMoving;
    public:
        #pragma region Initialization

        /**
        * @brief MovingGroup object constructor by default.
        */
        MovingGroup();

        /**
        * @brief MovingGroup object constructor.
        * @param movingGroup List of grouped motors.
        */
        MovingGroup(std::vector<Motor> &_movingGroup);

        /**
        * @brief MovingGroup object destructor by default.
        */
        ~MovingGroup();

        #pragma endregion
        #pragma region Functions

        /**
        * @brief Move backward.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        */
        void GroupBackward(const int8_t &_dcycle);

        /**
        * @brief Move backward with set delay.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param delay Moving time (milliseconds).
        */
        void GroupBackwardUntil(const int8_t &_dcycle, const int16_t &_delay);

        /**
        * @brief Move forward.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        */
        void GroupForward(const int8_t &_dcycle);

        /**
        * @brief Move forward with set delay.
        * @note Set duty cycle if pwm pin exists, if not - will move with 255.
        * @param dcycle Duty cycle value.
        * @param delay Moving time (milliseconds).
        */
        void GroupForwardUntil(const int8_t &_dcycle, const int16_t &_delay);

        /**
        * @brief Stop moving.
        */
        void GroupShutdown();

        /**
         * @brief Hard turn left with maximum possible angular velocity.
         * @param dcycle Duty cycle value, if not stated - will be 50.
         * @param delay Turning time (in milliseconds).
         */
        void HardTurnLeft(const int8_t &_dcycle, const int16_t &_delay);

        /**
         * @brief Hard turn right with maximum possible angular velocity.
         * @param dcycle Moving group duty cycle value, if not stated - will be 50.
         * @param delay Turning time (in milliseconds).
         */
        void HardTurnRight(const int8_t &_dcycle, const int16_t &_delay);

        /**
         * @brief Soft turn left with set increased angular velocity.
         * @param dcycle Moving group duty cycle value, if not stated - will be 50.
         * @param turn_dcycle Turning duty cycle increase.
         * @param delay Turning time (in milliseconds).
         */
        void SoftTurnLeft(const int8_t &_dcycle, const int8_t &_turn_dcycle, const int16_t &_delay);

        /**
         * @brief Soft turn right with set increased angular velocity.
         * @param dcycle Moving group duty cycle value, if not stated - will be 50.
         * @param turn_dcycle Turning duty cycle increase.
         * @param delay Turning time (in milliseconds).
         */
        void SoftTurnRight(const int8_t &_dcycle, const int8_t &_turn_dcycle, const int16_t &_delay);
        
        #pragma endregion
};