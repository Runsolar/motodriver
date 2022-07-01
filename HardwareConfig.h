// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#pragma once

#include <ArduinoSTL.h>
#include <map>
#include <string>

using namespace std;

/**
* @brief Supporting Drivers:    
* L298N 2X Motor Shield, 
* Other.
*/
enum class ShieldDriversNames{L298N, OTHER}

class MotorConfiguration{
    private:
        int8_t pwm_pin;
        int8_t direction_pin1;
        int8_t direction_pin2;
        int8_t dcycle;
        int8_t direct;
    
    public:
        int8_t motorID;
        int8_t shield_driver_type;
        string shield_driver_name;
        
        #pragma region Initialization
        /**
        * @brief MotorConfiguration object constructor by default.
        */
        MotorConfiguration() = default; 

        /**
        * @brief MotorConfiguration object constructor.
        * @param pwm_pin PWM (Pulse-width modulation) controller pin number.
        * @param direction_pin1 First rotating direction pin number.
        * @param direction_pin2 Second rotating direction pin number(if exists).
        * @param dcycle Duty cycle value.
        * @param direct Direction value.
        * @param shield_driver_name Name of your motor driver shield (check for support).
        */
        MotorConfiguration(const int8_t &_pwm_pin, const int8_t &_direction_pin1, const int8_t &_direction_pin2,
                           const int8_t &_dcycle, const int8_t &_direct, 
                           const string &_shield_driver_name): pwm_pin(_pwm_pin), direction_pin1(_direction_pin1), 
                           direction_pin2(_direction_pin2), dcycle(_dcycle), direct(_direct){

            switch (_shield_driver_name)
            {
            case "L298N":
                shield_driver_type = (int8_t)ShieldDriversNames::L298N;
                break;          
            default:
                shield_driver_type = (int8_t)ShieldDriversNames::OTHER;
                break;
            }

            pinMode(pwm_pin, OUTPUT);
            pinMode(direction_pin1, OUTPUT);
            pinMode(direction_pin2, OUTPUT);
        }

        ~MotorConfiguration(){}

        #pragma endregion
        #pragma region Accessors

        void set_direct(int8_t _direct){
            direct = _direct;
        }

        void set_dcycle(int8_t _dcycle){
            dcycle = _dcycle;
        }

        int8_t get_direct(){
            return direct;
        }

        int8_t get_dcycle(){
            return dcycle;
        }

        int8_t &direction_() {
            return direct;
        }

        int8_t &duty_cycle_() {
            return dcycle;
        }

        #pragma endregion
        #pragma region Functions

        /**
        * @result Shield driver name.
        */        
        void print8_t_driver_name(){
            std::cout << "Motor driver shield name is " << shield_driver_name << "\n";
        }

        /**
        * @brief
        */
        void Rotate(){
            digitalWrite(direction_pin1, direct);
            analogWrite(pwm_pin, dcycle);
        }

        #pragma endregion

};

class ShieldDriver {
    private:
        map<int8_t, MotorConfiguration> motorConfiguartion;

    public:
        #pragma region Initialization

        /**
        * @brief ShieldDriver object constructor by default.
        */
        ShieldDriverConfiguration() = default; 

        /**
        * @brief MotorConfiguration object constructor.
        * @param motorConfiguration MotorConfiguration instance.
        */
        ShieldDriverConfiguration(map<int8_t, MotorConfiguration> &_motorConfiguration) {
            motorConfiguartion = _motorConfiguration;
        }

        ~ShieldDriverConfiguration(){}

        #pragma endregion
        #pragma region Functions

        /**
        * @brief Function that allows motor to rotate clockwise.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void clockWise(const int8_t &_dcycle, const int8_t &motorId){     
            motors[motorId].direction_() = 1;
            motors[motorId].durty_cycle_() = _dcycle;
            motors[motorId].Rotate();   
        }

        /**
        * @brief Function that allows motor to rotate counterclockwise.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void counterclockWise(const int8_t &_dcycle, const int8_t &motorId){     
            motors[motorId].direction_() = 0;
            motors[motorId].durty_cycle_() = _dcycle;
            motors[motorId].Rotate();   
        }

        #pragma endregion
};