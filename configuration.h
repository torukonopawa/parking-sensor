#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

    #define F_CPU 8000000UL

    //=>Libraries
    #include <avr/io.h>
    #include <util/delay.h>
    #include <avr/interrupt.h>
    #include "LCD.h"

    //=>RGB LEDs
    #define RED_VAL OCR2B
    #define GREEN_VAL OCR0B
    #define BLUE_VAL OCR0A
    //PB3 - OC2A - D11
    #define NEXT_PWM OCR2A //not used

    //=>LCD
    #define LCD_Data_Dir DDRC
    #define LCD_Data_Port PORTC

    #define LCD_Cmd_Dir DDRB
    #define LCD_Cmd_Port PORTB

    #define RS PB0
    #define EN PB1

    //=>BUZZER
    #define BUZZER PB2
    #define BUZZER_PORT PORTB

#endif /* CONFIGURATION_H_ */
