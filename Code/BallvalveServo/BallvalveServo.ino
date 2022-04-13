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
                      104000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      98000);         // Value of the series resistor

// Global temperature reading
uint16_t temp;

void setup() {
  Serial.begin(9600);
  Serial.print(valvepos);

  //initialize the variables we're linked to
  Input = temp;
  Setpoint = 50;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  //HOME(); 
}

void loop() {
  //Serial.print(counter);
  TEMPREAD();
  PIDC();
  SETVALVE();
  delay(500);
  Serial.print("setpos ");
  Serial.println(setpos);
  
}

  void HOME(){
    OPEN();
    CLOSE();
    OPEN();
  }
  
  void OPEN(){
    for (valvepos = 1; valvepos <= 33;){
      open1();
      delay(200);
    }
  }
  void CLOSE(){
    for (valvepos = 33; valvepos >= 1;){
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
    Serial.print("valvepos: ");
    Serial.println(valvepos);
  }

  void close1(){
    servo.attach(3);
    delay(10);
    servo.write(180);
    delay(100);
    servo.detach();
    valvepos = valvepos -1;
    Serial.print("valvepos: ");
    Serial.println(valvepos);
  }

void TEMPREAD(){
temp = thermistor.read();   // Read temperature
  Serial.println (temp);
}


void PIDC(){
    Input = temp;
    myPID.Compute();
   Serial.print("PIDOUT: ");
   Serial.println(Output);
   setpos = map(Output, 0, 255, 33, 0);
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
