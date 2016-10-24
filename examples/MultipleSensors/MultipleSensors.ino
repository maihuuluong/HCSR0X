#include "SRManager.h"


/*
  The sketch has been tested with SR-015
*/

SRManager sManager(200); // TRIG, ECHO, TIME OUT

void setup()
{
 Serial.begin(9600);
sManager.attachSensor(2, 3); // TRIG, ECHO,
sManager.attachSensor(2, 4); // TRIG, ECHO,
sManager.attachSensor(2, 5); // TRIG, ECHO,
sManager.attachSensor(2, 6); // TRIG, ECHO,
sManager.attachSensor(2, 7); // TRIG, ECHO,
sManager.attachSensor(2, 8); // TRIG, ECHO,
sManager.attachSensor(2, 9); // TRIG, ECHO,

}

void output(int index)
{
    Serial.print (sManager.getDistance(index));
    Serial.print ("\t");
}
void loop()
{
    
  sManager.ping();   
  output(0);
  Serial.println();
  delay(30);

}




