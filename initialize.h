#include "configuration.h"

//=>initilaze i/o
void init_io();
    //=>outputs:
        void init_outputs();
        void init_lcd();
        void init_rgbLED();
        void init_buzzer();
    //=> inputs:
        void init_inputs();
        void init_distanceSensor();

//=>timers:
    void init_timers();
    void init_timer0();
    void init_timer1();
    void init_timer2();

// & & & &
void init_all()
{
    init_io();
    init_timers();
}
// & & & &

void init_io()
{
    init_outputs();
    init_inputs();
}

void init_outputs()
{
    //DISPLAYS
    init_lcd();
    init_rgbLED();
    //ALARMS
    init_buzzer();
}

void init_inputs()
{
    //SENSORS
    init_distanceSensor();
}

// - - - -

void init_timers()
{
    //TIMERS
    init_timer0();
    init_timer1();
    init_timer2();
}

void init_timer0()
{
    //7.8125kHz, 0.128ms/STEP => STEP*256 = 32.768ms, 30.5Hz
    //=>PWM0 8b: TCNT0 OCR0A OCR0B TIMSK0/TIFR0
    
    //TCCR0A |= (1<<COM0A0);
    TCCR0A |= (1<<COM0A1); //non-inverting
    
    //TCCR0A |= (1<<COM0B0);
    TCCR0A |= (1<<COM0B1); //non-inverting
    
    TCCR0A |= (1<<WGM00);
    TCCR0A |= (1<<WGM01);
    //TCCR0B |= (1<<WGM02); //fastPWM (max: 0xFF)
    
    TCCR0B |= (1<<CS00);
    //TCCR0B |= (1<<CS01);
    TCCR0B |= (1<<CS02); //f/1024 (8MHz/1024=7.8125kHz)
    
    //TIMSK0 |= (1<<TOIE0); //interrupt
}

void init_timer1()
{
//NOT USED
}

void init_timer2()
{
    //7.8125kHz, 0.128ms/STEP => STEP*256 = 32.768ms, 30.5Hz
    //=>PWM2 8b: TCNT2 OCR2A OCR2B TIMSK2/TIFR2
    
    //TCCR0A |= (1<<COM2A0);
    TCCR2A |= (1<<COM2A1); //non-inverting
    
    //TCCR0A |= (1<<COM2B0);
    TCCR2A |= (1<<COM2B1); //non-inverting
    
    TCCR2A |= (1<<WGM20);
    TCCR2A |= (1<<WGM21);
    //TCCR2B |= (1<<WGM22); //fastPWM (max: 0xFF)
    
    TCCR2B |= (1<<CS20);
    TCCR2B |= (1<<CS01);
    TCCR2B |= (1<<CS22); //f/1024 (8MHz/1024=7.8125kHz)
    
    //TIMSK2 |= (1<<TOIE0); //interrupt
}

// = = = =

void init_lcd()
{
    LCD_Init();
    LCD_Clear();
    LCD_Distance_RGB(0, 0, 0, 0);
}

void init_rgbLED()
{
    RED_VAL = 10;
    DDRD |= (1<<PD3); //OC2B - D3
    
    GREEN_VAL = 10;
    DDRD |= (1<<PD5); //OC0B - D5
    
    BLUE_VAL = 10;
    DDRD |= (1<<PD6); //OC0A - D6
}

void init_buzzer()
{
    DDRB |= (1<<BUZZER);
}

// - - - -

void init_distanceSensor()
{
    //DISTANCE SENSOR SIMULATED BY POTENTIOMETER
    DDRC = (DDRC & 0x0F) | (0x00);
    
    ADMUX |= (1<<REFS0); //AVcc with external C at AREF
    ADMUX |= (1<<ADLAR); //LEFT ADJUST
    
    ADMUX = (ADMUX & 0xE0) | (0x05); //0101 ADC5
    
    ADCSRA |= (1<<ADEN);
    
    ADCSRA |= (1<<ADPS1)|(1<<ADPS2); //div 64, 125 kHz@8MHz
}
