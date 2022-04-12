#include <Servo.h>
Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int counter =0;
#include "thermistor.h"

// Analog pin used to read the NTC
#define NTC_PIN A7

// Thermistor object
THERMISTOR thermistor(NTC_PIN,        // Analog pin
                      104000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      98000);         // Value of the series resistor

// Global temperature reading
uint16_t temp;

void setup() {
  Serial.begin(9600);
  Serial.print(counter);
  //HOME();
}

void loop() {
  //Serial.print(counter);
  TEMPREAD();
  delay(2000);
  
}

  void HOME(){
    OPEN();
    CLOSE();
    OPEN();
  }
  
  void OPEN(){
    for (counter = 1; counter <= 33;){
      open1();
      delay(200);
    }
  }
  void CLOSE(){
    for (counter = 33; counter >= 1;){
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
    counter = counter +1;
  }

  void close1(){
    servo.attach(3);
    delay(10);
    servo.write(180);
    delay(100);
    servo.detach();
    counter = counter -1;
  }

void TEMPREAD(){
temp = thermistor.read();   // Read temperature
  Serial.println (temp);
  

}
