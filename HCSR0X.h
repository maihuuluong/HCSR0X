/*
  HCSR0X.h - Library  for sensor HCSR0X
*/

#ifndef HCSR0X_h
#define HCSR0X_h

#include <Arduino.h>


#define CM 1
#define IN 0

#define ERROR_RANGE -2
#define OUT_RANGE -1

#define BIT_ON(REG, BIT) *REG|=BIT
#define BIT_OFF(REG, BIT) *REG&=~BIT
#define BIT_GET(REG, BIT)  (*REG&BIT?HIGH:LOW)

#define DEFAULT_RANGE       500 // default max range in centimeters
#define SONARS_SPEED_RATIO_CM  29
#define SONARS_SPEED_RATIO_INC  74



#define PIN_INPUT(REG, BIT) {uint8_t oldSREG = SREG;\
                            cli();\
                            *REG &= ~BIT;\
                            SREG = oldSREG;\
                            }
#define PIN_OUTPUT(REG, BIT) {int8_t oldSREG = SREG;\
                             cli();\
                             *REG |= BIT;\
                             SREG = oldSREG;\
                             }



#define _delay_10_micros() __asm__("    ldi  r18, 53\n\t\
                                        L1: dec  r18\n\t\
                                        brne L1\n\t\
                                        nop\n\t\
                                  ")



class HCSR0X
{
  public:
  HCSR0X(uint8_t Trigger,uint8_t Echo, int max_range_in_cm = DEFAULT_RANGE);

   /*!
    @method
    @abstract   Sets all the pins of the device.
    @discussion This method sets all the pins of the device Trigger
    and Echo.

    @param       Trigger[in] device pin to send pulses. Range (0..12).
    @param       Echo[out] to set the pin of answer device (0..12).
    @param       Time_out max waiting time in milliseconds.
    */

  float ping(int type = CM);

   /*!
    @method
    @abstract   Starts calculating a distance.
    @discussion This method use this Formula: delay in uS / 58 = centimeters.

    @param      type[integer] centimeters or inch CM/INC
    @result     distance in centimeters or inch
    */

  private:
    long _Time_out;
    volatile uint8_t * _TriggerRegister;
    volatile uint8_t * _EchoRegister;
    uint8_t _TriggerBit;
    uint8_t _EchoBit;
    long _break_time;
};

#endif

