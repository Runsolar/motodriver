// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software.

#include <avr/io.h>
#include <avr/interrupt.h>

#include "src/motodriver.h"

// After setup function create Motor class instances 
// for your DC motors with chosen Arduino pin numbers.
MotoDriver motodriver;
Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;
std::map<uint8_t, Motor> motorList;

void setup() {
  motor1 = Motor(9,9,11,ShieldDriversNames::MX1508); // Two PWM PINS MOTORS, LIKE A MX1508
  motor2 = Motor(10, 8, 0, ShieldDriversNames::TB6612);
  motor3 = Motor(3,4,0, ShieldDriversNames::TB6612);
  motor4 = Motor(5,6,7, ShieldDriversNames::L298N);
  
  motorList = { {1, motor1}, {2, motor2}, {3, motor3}, {4, motor4}};
  motodriver = MotoDriver(motorList);
  
  motodriver.MotorToGroup(1, 1);
  motodriver.MotorToGroup(2, 1);
  motodriver.MotorToGroup(3, 1);
  motodriver.MotorToGroup(4, 1);

  // инициализация Timer1
  cli();  // отключить глобальные прерывания
  TCCR1A = 0;   // установить регистры в 0
  TCCR1B = 0;

  OCR1A = 15624; // установка регистра совпадения

  TCCR1B |= (1 << WGM12);  // включить CTC режим 
  TCCR1B |= (1 << CS10); // Установить биты на коэффициент деления 1024
  TCCR1B |= (1 << CS12);

  TIMSK1 |= (1 << OCIE1A);  // включить прерывание по совпадению таймера 
  sei(); // включить глобальные прерывания

  //Serial.begin(9600);
}


void loop() {
  
  motodriver.Clockwise_Group_Rotation(255, 1);
  motodriver.Counterclockwise_Group_Rotation(255, 2);

}

int seconds = 0;
int count = 0;
bool forward = 1;
ISR(TIMER1_COMPA_vect)
{
    seconds++;
    if(seconds == 5)
    {
        seconds = 0;

        if(count == 0){
          if(forward)
            motodriver.MotorToGroup(1, 2);
          else
            motodriver.MotorToGroup(1, 1);
        }

        if(count == 1){
          if(forward)
            motodriver.MotorToGroup(2, 2);
          else
            motodriver.MotorToGroup(2, 1);
        }

        if(count == 2){
          if(forward)
            motodriver.MotorToGroup(3, 2);
          else
            motodriver.MotorToGroup(3, 1);
        }

        if(count == 3){
          if(forward)
            motodriver.MotorToGroup(4, 2);
          else
            motodriver.MotorToGroup(4, 1);

          if(forward == 1)
            forward = 0;
          else
            forward = 1;
        }
        
        if(count == 3)
          count = 0;
        else
          ++count; 
    }
}
