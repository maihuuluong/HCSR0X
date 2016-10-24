#define CM 1
#define INC 0

#define ERROR_RANGE -2
#define OUT_RANGE -1

#define BIT_ON(REG, BIT) REG|=BIT
#define BIT_OFF(REG, BIT) REG&=~BIT
#define BIT_GET(REG, BIT)  (REG&BIT?HIGH:LOW)

#define DEFAULT_RANGE       500 // default max range in centimeters
#define SONARS_SPEED_RATIO_CM  29
#define SONARS_SPEED_RATIO_INC  74

#define MAX_SENSOR 10 // to be optimized /dynamic allocate

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
