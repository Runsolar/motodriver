// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#pragma once

#include <ArduinoSTL.h>
#include <map>
#include <string>

/**
* @brief Supporting Drivers:    
* L298N 2X Motor Shield, 
* Other.
*/
typedef enum {
    L298N = 1, 
    OTHER = 0
} ShieldDriversNames;

/**
 * @brief Supporting directions: 
 * Forward, Backward, Shutdown
 */
typedef enum {
    FORWARD = 0, 
    BACKWARD = 1,
    SHUTDOWN = -1
} MoveDirection;

class Motor{
    private:
        int8_t pwm_pin;
        int8_t direction_pin1;
        int8_t direction_pin2;
        int8_t dcycle;
        int8_t direct;
    
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
        * @param direction_pin2 Second rotating direction pin number(if exists).
        * @param dcycle Duty cycle value.
        * @param direct Direction value.
        * @param shield_driver_name Name of your motor driver shield (check for support).
        */
        Motor(const int8_t &_pwm_pin, const int8_t &_direction_pin1, const int8_t &_direction_pin2, 
              const int8_t &_dcycle, const int8_t &_direct, const std::string &_shield_driver_name);

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

class MotorX2{
    private:
        int8_t dcycleA;
        int8_t dcycleB;
        int8_t direct;
    public:
        Motor motorA;
        Motor motorB;
        int8_t motorID;
        int8_t shield_driver_type_A;
        int8_t shield_driver_type_B;
        std::string shield_driver_name_A;
        std::string shield_driver_name_B;

        #pragma region Initialization

        /**
        * @brief MotorX2 object constructor by default.
        */
        MotorX2(); 

        /**
        * @brief MotorX2 object constructor.
        * @param pwm_pin_A [First] PWM (Pulse-width modulation) controller pin number.
        * @param pwm_pin_B [Second] PWM (Pulse-width modulation) controller pin number.
        * @param direction_pin1_A [First] First rotating direction pin number.
        * @param direction_pin2_A [First] Second rotating direction pin number(if exists).
        * @param direction_pin1_B [Second] First rotating direction pin number.
        * @param direction_pin2_B [Second] Second rotating direction pin number(if exists).
        * @param dcycle_A [First] Duty cycle value.
        * @param dcycle_B [Second] Duty cycle value.
        * @param direct [Both] Direction value.
        * @param shield_driver_name_A [First] Name of your motor driver shield (check for support).
        * @param shield_driver_name_B [Second] Name of your motor driver shield (check for support).
        */
        MotorX2(const int8_t &_pwm_pin_A, const int8_t &_pwm_pin_B, 
                const int8_t &_direction_pin1_A, const int8_t &_direction_pin2_A, 
                const int8_t &_direction_pin1_B, const int8_t &_direction_pin2_B, 
                const int8_t &_dcycle_A, const int8_t &_dcycle_B, 
                const int8_t &_direct,
                const std::string &_shield_driver_name_A, const std::string &_shield_driver_name_B);
    
        /**
        * @brief Motor object destructor by default.
        */
        ~MotorX2();        

        #pragma endregion
        #pragma region Accessors

        /**
        * @brief [Both] Set new direction.
        */
        void set_direct(int8_t _direct);

        /**
        * @brief [First] Set new duty cycle.
        */
        void set_dcycle_A(int8_t _dcycle_A);

        /**
        * @brief [Second] Set new duty cycle.
        */
        void set_dcycle_B(int8_t _dcycle_B);

        /**
        * @brief [Both] Get current direction.
        */
        int8_t get_direct();

        /**
        * @brief [First] Get current duty cycle.
        */
        int8_t get_dcycle_A();

        /**
        * @brief [Second] Get current duty cycle.
        */
        int8_t get_dcycle_B();

        /**
        * @brief [Both] Get current direction by link.
        */
        int8_t &direction_() {
            return direct;
        }

        /**
        * @brief [First] Get current duty cycle by link.
        */
        int8_t &duty_cycle_A_() {
            return dcycleA;
        }

        /**
        * @brief [Second] Get current duty cycle by link.
        */
        int8_t &duty_cycle_B_() {
            return dcycleB;
        }

        #pragma endregion
        #pragma region Functions

        /**
        * @result [Both] Shield driver names.
        */        
        void print8_t_driver_names();

        /**
        * @brief [First] Move with set direction and duty cycle.
        */
        void RotateA();

        /**
        * @brief [Second] Move with set direction and duty cycle.
        */
        void RotateB();

        /**
        * @brief [First] Stop moving.
        */
        void ShutdownA();

        /**
        * @brief [Second] Stop moving.
        */
        void ShutdownB();

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
        * @param motor Motor instance.
        */
        MotoDriver(std::map<int8_t, Motor> &_motors);

        /**
        * @brief MotoDriver object destructor by default.
        */
        ~MotoDriver();

        #pragma endregion
        #pragma region Functions

        /**
        * @brief Move backward with set duty cycle if pwm pin exists, if not - move backward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void Backward(const int8_t &_dcycle, const int8_t &motorId);

        /**
        * @brief Move forward with set duty cycle if pwm pin exists, if not - move forward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void Forward(const int8_t &_dcycle, const int8_t &motorId);

        /**
        * @brief Stop moving.
        * @param motorID Current motor you want to stop.
        */
        void Shutdown(const int8_t &motorId);

        #pragma endregion
};

class MotoDriverX2{
    private:
        std::map<int8_t, MotorX2> motors;
        boolean isMoving;
    public:
        #pragma region Initialization

        /**
        * @brief MotoDriver object constructor by default.
        */
        MotoDriverX2();

        /**
        * @brief MotoDriverX2 object constructor.
        * @param motor Motor instance.
        */
        MotoDriverX2(std::map<int8_t, MotorX2> &_motors);

        /**
        * @brief MotoDriverX2 object destructor by default.
        */
        ~MotoDriverX2();

        #pragma endregion
        #pragma region Functions

        /**
        * @brief [First] Move backward with set duty cycle if pwm pin exists, if not - move backward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void BackwardA(const int8_t &_dcycleA, const int8_t &motorId);

        /**
        * @brief [Second] Move backward with set duty cycle if pwm pin exists, if not - move backward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void BackwardB(const int8_t &_dcycleA, const int8_t &motorId);

        /**
        * @brief [Both] Move backward with set duty cycle if pwm pin exists, if not - move backward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void BackwardBoth(const int8_t &_dcycleA, const int8_t &_dcycleB, const int8_t &motorId);

        /**
        * @brief [First] Move forward with set duty cycle if pwm pin exists, if not - move forward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void ForwardA(const int8_t &_dcycleA, const int8_t &motorId);

        /**
        * @brief [Second] Move forward with set duty cycle if pwm pin exists, if not - move forward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void ForwardB(const int8_t &_dcycleA, const int8_t &motorId);

        /**
        * @brief [Both] Move forward with set duty cycle if pwm pin exists, if not - move forward with 255.
        * @param dcycle Duty cycle value.
        * @param motorID Current motor you want to rotate.
        */
        void ForwardBoth(const int8_t &_dcycleA, const int8_t &_dcycleB, const int8_t &motorId);

        /**
        * @brief [First] Stop moving.
        * @param motorID Current motor you want to stop.
        */
        void ShutdownA(const int8_t &motorId);

        /**
        * @brief [Second] Stop moving.
        * @param motorID Current motor you want to stop.
        */
        void ShutdownB(const int8_t &motorId);

        /**
        * @brief [Both] Stop moving.
        * @param motorID Current motor you want to stop.
        */
        void ShutdownBoth(const int8_t &motorId);

        #pragma endregion
};