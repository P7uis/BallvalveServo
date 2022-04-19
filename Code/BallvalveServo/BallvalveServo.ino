#include <PID_v1.h>
#include <Servo.h>
Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int valvepos =0;
int setpos = 0;
#include "thermistor.h"

// Analog pin used to read the NTC
#define NTC_PIN A7

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Thermistor object
THERMISTOR thermistor(NTC_PIN,        // Analog pin
                      100000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      100000);         // Value of the series resistor

// Global temperature reading
int temp;

void setup() {
  //Serial.begin(9600);
  
  //initialize the variables we're linked to
  Input = temp;
  Setpoint = 25;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  HOME(); 
}

void loop() {
  //Serial.print(counter);
  TEMPREAD();
  delay(100);
  PIDC();
  delay(100);
  SETVALVE();
  delay(1000);
}

  void HOME(){
    OPEN();
    CLOSE();
    OPEN();
  }
  
  void OPEN(){
    for (valvepos = 1; valvepos < 20;){
      open1();
      delay(200);
    }
  }
  void CLOSE(){
    for (valvepos = 20; valvepos > 0;){
      close1();
      delay(200);
    }
  }
  

  void open1(){
    servo.attach(3);
    delay(10);
    servo.write(0);
    delay(100);
    servo.detach();
    valvepos = valvepos +1;
  }

  void close1(){
    servo.attach(3);
    delay(10);
    servo.write(180);
    delay(100);
    servo.detach();
    valvepos = valvepos -1;
  }

void TEMPREAD(){
temp = thermistor.read();   // Read temperature
delay(500);
}


void PIDC(){
    Input = temp;
    myPID.Compute();
   setpos = map(Output, 0, 255, 20 , 0);
}

void SETVALVE(){
  if (setpos > valvepos) {
    while (setpos > valvepos) {
      open1();
    }
}
  else if (setpos < valvepos) {
    while (setpos < valvepos) {
      close1();
    }
}
  else {
  // Safe! Continue usual tasks.
  }
}
