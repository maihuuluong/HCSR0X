/*
  SRManager.cpp
  Multiple sensor working at the same time.
  Tested up to 10 sensors on arduino nano
  Mai Huu Luong - Nov, 2016
*/

#include  <Arduino.h>
#include "SRManager.h"


SRManager::SRManager(int max_range_in_cm):_size(0){
  _Time_out = max_range_in_cm * (SONARS_SPEED_RATIO_CM *3);
}

void SRManager::attachSensor(const uint8_t Trig, const uint8_t Echo)
{
  if(_size == 15) return; // exceed max sensors number
  _TriggerBit[_size] = digitalPinToBitMask(Trig);
  _EchoBit[_size] = digitalPinToBitMask(Echo);

  _TriggerRegister[_size] = portOutputRegister(digitalPinToPort(Trig));
  _EchoRegister[_size]   = portInputRegister(digitalPinToPort(Echo));
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  _size++;
}

void SRManager::ping()
{
  uint8_t portB = 0;
  uint8_t portC = 0;
  uint8_t portD = 0;
  long test = 0;
  int i = 0;

  // set the pin value to temporally variable corresponding to output port.
  for(i= 0; i < _size ; i++)
  {
    _startChrono[i] = 0;
    _endChrono[i] = 0;
    _deltaTime[i] = 0;
    if (_TriggerRegister[i] == &PORTB) BIT_ON(portB,_TriggerBit[i]);
    if (_TriggerRegister[i] == &PORTC) BIT_ON(portC,_TriggerBit[i]);
    if (_TriggerRegister[i] == &PORTD) BIT_ON(portD,_TriggerBit[i]);
  }


  // Turn off all trigger pins
  /*if (portB)*/ BIT_OFF(PORTB, portB);
  /*if (portC)*/ BIT_OFF(PORTC, portC);
  /*if (portD)*/ BIT_OFF(PORTD, portD);

  _delay_us(2);
  // Turn on all trigger pins
  /*if (portB)*/ BIT_ON(PORTB, portB);
  /*if (portC)*/ BIT_ON(PORTC, portC);
  /*if (portD)*/ BIT_ON(PORTD, portD);

  _delay_us(10);


  // Turn off all trigger pins again
  /*if (portB)*/ BIT_OFF(PORTB, portB);
  /*if (portC)*/ BIT_OFF(PORTC, portC);
  /*if (portD)*/ BIT_OFF(PORTD, portD);
  //_delay_ms(500);
  _break_time = micros() + _Time_out;

  int flag = 0; // to check if all sensor have returned the value
  do{
    test = micros();
    for(i = 0; i < _size ; i++)
    {
      int bit = BIT_GET(*_EchoRegister[i],_EchoBit[i]);
      if( !bit && _startChrono[i] && !_endChrono[i]){
          _endChrono[i]  = test;     // Pulse end
          flag++;
      }
      else if( bit && !_startChrono[i]) {
          _startChrono[i] = test;    // Just start receive the pulse
      }
    }
  }while(test < _break_time && flag < _size);


  for( i = 0; i < _size ; i++)
  {
    if(_startChrono[i] > 0)
      if(_endChrono[i] > 0)
        _deltaTime[i] = _endChrono[i] - _startChrono[i] -25 ; // overheat
      else
        _deltaTime[i] = OUT_RANGE;
    else
      _deltaTime[i] = ERROR_RANGE;
  }
}

float SRManager::getDistance(int index , int type)
{
  if(_deltaTime[index] > 0)
    return (float)(_deltaTime[index]/2)/(type == CM?SONARS_SPEED_RATIO_CM:SONARS_SPEED_RATIO_INC);
  else
    return _deltaTime[index];
}

