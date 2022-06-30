//#include <iostream>
//#include <ros.h>
#include<ArduinoSTL.h>
#include<map>
#include<string>

using namespace std;

/* Supporting drivers
 * L298N 2X Motor Shield 
 * 
 */
//SDN - Shild drivers names

enum class SDN{L298N, OTHER};


class Motor{
 private:
  int8_t pwm_pin;
  int8_t direction_pin1;
  //const int8_t direction_pin2;
  int8_t dcycle;
  int8_t direct;
  
  int8_t shild_driver_type;
  
 public:
  int8_t motorId;
  string shild_driver_name;

  
  Motor() = default;
  
  Motor(const int8_t &_pwm_pin, const int8_t &_direction_pin1, const int8_t &_direction_pin2 = 0, 
        const int8_t &_dcycle = 0, const int8_t &_direct = 0, const string _shild_driver_name = "L298N"): pwm_pin(_pwm_pin), direction_pin1(_direction_pin1){
      //pwm_pin = _pwm_pin;
      //direction_pin1 = _direction_pin1;
      dcycle = _dcycle;
      direct = _direct;

      if(_shild_driver_name == "L298N")
        shild_driver_type =  (int8_t)SDN::L298N;

      
      switch(shild_driver_type){
        case 1:
          break;
        case 2:
          break;
        default:
          break;
         
      }
      
      pinMode(pwm_pin, OUTPUT);
      pinMode(direction_pin1, OUTPUT);
  }
  void print8_t_driver_name(){
      std::cout << "Driver name: " << shild_driver_name << '\n';
  }

  void Rotate(){
/*
    Serial.print8_t(pwm_pin, DEC);
    Serial.print8_t("\t");
    
    Serial.print8_t(direction_pin1, DEC);
    Serial.print8_t("\t");
*/    
    digitalWrite(direction_pin1, direct);
    analogWrite(pwm_pin, dcycle); 
  } 

  void set_direct(int8_t _direct)
  {
        direct = _direct;
  }
 
  void set_dcycle(int8_t _dcycle) {
        dcycle = _dcycle;
  }

  int8_t get_direct() const {
        return direct;
  }

  int8_t get_dcycle() const {
        return dcycle;
  }

  //Геттер-ссылка
  int8_t &direction_() {
    return direct;
  }

  int8_t &durty_cycle_() {
    return dcycle;
  }
 
};


class MotoDriver{

  private:
    std::map<int8_t, Motor> motors;
  
  public:
  
    MotoDriver() = default;
    
    MotoDriver(std::map<int8_t, Motor> &_motors){
      motors = _motors;
    }

  void clockWise(const int8_t &_dcycle, const int8_t &motorId){     
    //Write(motors[motorId], _dcycle);
    //motors[motorId].print8_t_driver_name();
    //Motor motor = motors.find(motorId);
    
    //Motor m = motors[motorId];
    
    //motors[motorId].print8_t_driver_name();
    //motors[motorId].set_direct(1);
    motors[motorId].direction_() = 1;
    //motors[motorId].set_dcycle(_dcycle);
    motors[motorId].durty_cycle_() = _dcycle;
    motors[motorId].Rotate();
/*    
    for (auto& n : motors) {
        //std::cout << n.first << " = " << n.second << ";
        //cout << "Motor ID: " << n.first << "\n";
        n.second.print8_t_driver_name();
    }
*/     
  }

  void counterclockWise(const int8_t &_dcycle, const int8_t &motorId){
    motors[motorId].direction_() = 0;
    motors[motorId].durty_cycle_() = _dcycle;
    motors[motorId].Rotate();
  }
  
};



void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
}

Motor motor1 = Motor(3, 4);
Motor motor2 = Motor(5, 6);

std::map<int8_t, Motor> motors = { {1, motor1}, {2, motor2} };
MotoDriver motodriver = MotoDriver(motors);

//motodriver.setMoveGroupAs(1, 2)

void loop(){
  
  motodriver.clockWise(255, 1);
  motodriver.clockWise(255, 2);

/*
  motodriver.moveForward(5)
  motodriver.stop()
  motodriver.moveBackward(5)
  motodriver.turnLeft(-90, d)
  motodriver.turnRight(90, d)
*/    
    //motodriver.turnBack(-90, d, k, 1, 2, )
  
}
