/*
  SRManager.h - Library  for sensor HCSR0X
  Use for multiple sensors working at the same time.
  Can use common trigger pin for all sensors
*/

#ifndef SRManager_h
#define SRManager_h

#include <Arduino.h>

#include "_macro.h"


class SRManager
{
  public:
  SRManager(int max_range_in_cm = DEFAULT_RANGE);

   /*!
    @method
    @abstract   Constructor.
    @discussion You can overwrite the max range for the sensors

    @param       max_range_in_cm: The max range in centimeter that the sensors can measure
    */

  void attachSensor(const uint8_t Trig, const uint8_t Echo);

     /*!
    @method
    @abstract   Attach the sensor to the program
    @discussion You can use the same trigger pin for all sensor

    @param       Trig: trigger pin number
    @param       Echo: echo pin number
    */

  void ping();

   /*!
    @method
    @abstract   Starts calculating a distance.
    @discussion Starts ping for all attached sensor.

    */

  int getDistance(int index, int type=CM);

     /*!
    @method
    @abstract   Get the sensors return distance.
    @discussion This method return the distance measured by the last ping call.

    @param      index: the sensor index corresponding to the order when it was call attachSensor, start from 0
    @param      type: calculate the distance in centimeters or inch (CM or INC)
    @result     distance in centimeters or inch, base on [type]
    */
  // To be optimized
  private:
    long _Time_out;
    uint8_t _maxSensor;
    uint8_t _size;
    volatile uint8_t * _TriggerRegister[MAX_SENSOR];
    volatile uint8_t * _EchoRegister[MAX_SENSOR];
    uint8_t  _TriggerBit[MAX_SENSOR];
    uint8_t  _EchoBit[MAX_SENSOR];
    long _break_time;
    long  _deltaTime[MAX_SENSOR];

    long  _startChrono[MAX_SENSOR];
    long  _endChrono[MAX_SENSOR];
};

#endif

