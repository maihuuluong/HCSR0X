#include "HCSR0X.h"


/*
  Connection diagrams
  12 <-> Trig
  A0 <-> Ech
  GND <-> GND
  5V  <-> Vcc 
  The sketch has been tested with SR-015
*/

HCSR0X Sensor1(12, A0 , 200); // TRIG, ECHO, TIME OUT

float DistanceCm = 0;

void setup()
{
 Serial.begin(9600);
}

void loop()
{
    
 DistanceCm = Sensor1.ping();   
 Serial.println(DistanceCm);
 delay(30);
}




