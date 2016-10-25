/*
  HCSR0X.cpp
  Mai Huu Luong - Nov, 2016
*/

#include  <Arduino.h>
#include "HCSR0X.h"


HCSR0X::HCSR0X( uint8_t Trigger, uint8_t Echo ,  int max_range_in_cm){



  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);

  _TriggerBit = digitalPinToBitMask(Trigger);
  _EchoBit = digitalPinToBitMask(Echo);

  _TriggerRegister = portOutputRegister(digitalPinToPort(Trigger));
  _EchoRegister   = portInputRegister(digitalPinToPort(Echo));
  _Time_out = max_range_in_cm * SONARS_SPEED_RATIO_CM << 1;
}

float  HCSR0X::ping(int type)
{

  long /*BeginChrono,*/EndChrono,DeltaChrono =0;

  //BeginChrono  = micros();

  BIT_OFF(*_TriggerRegister, _TriggerBit);
  _delay_us(2);
  //digitalWrite(_Trigger, HIGH);
  BIT_ON(*_TriggerRegister, _TriggerBit);
  //_delay_10_micros();
  _delay_us(10);
  //digitalWrite(_Trigger, LOW);
  BIT_OFF(*_TriggerRegister , _TriggerBit);

  _break_time = micros() + _Time_out;
  while(!BIT_GET(*_EchoRegister,_EchoBit)){
    if (micros() > _break_time)
      return ERROR_RANGE;
  }
  //BeginChrono  = micros();
  _break_time  =  micros() + _Time_out;

  while(BIT_GET(*_EchoRegister,_EchoBit)) { 			//Echo begin wait until echo response end
    EndChrono = micros();

    if (EndChrono > _break_time)
      return OUT_RANGE;
  }
  DeltaChrono = EndChrono - (_break_time - _Time_out) - 20; // overheat approximately 20 microseconds for the operations.
  return float(DeltaChrono/2)/(type == CM?SONARS_SPEED_RATIO_CM:SONARS_SPEED_RATIO_INC);
}

