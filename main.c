/*
* ParkingSensor
*
* Created: 1/6/2023 3:11:53 AM
* Author : toruko
*
* ABOUT:
*   ->Parking sensor of a vehicle. According to distance of vehicle to the obstacle
*   RGB LED color changes and buzzer is activated at some point.
*
* FUNCTIONS:
    =>OUTPUTS:
        -> Displays:
            -RGB LED
            -LCD
        -> Alarms:
            -Buzzer
    =>INPUTS:
        -> Sensors:
            -Distance sensor
*
* Program Loop:
*   -get: distance
*   -set & activate: LCD, RGB & BUZZER
*/
#include "configuration.h"
#include "initialize.h"

int get_distance();

int main(void)
{
    //initialize
    init_all();
    int red = 0, green = 0, blue = 0;
    int distance = 0;
    
    while(1)
    {
        distance = get_distance();
        
        if(distance < 90)
        {
            BUZZER_PORT |= (1<<BUZZER);
            //=>RED = R:FF G:00 B:00
            red = 0xFF;
            green = 0;
            blue = 0;
        }
        else if(distance < 180)
        {
            BUZZER_PORT &= ~(1<<BUZZER);
            //=>YELLOW = R:FF G:FF B:00
            red = 0xFF;
            green = 0xFF;
            blue = 0;
        }
        else
        {
            BUZZER_PORT &= ~(1<<BUZZER);
            //=>GREEN = R:00 G:FF B:00
            red = 0;
            green = 0xFF;
            blue = 0;
        }
        
        RED_VAL = red;
        GREEN_VAL = green;
        BLUE_VAL = blue;
        LCD_Distance_RGB(distance, red, green, blue);
        
        _delay_ms(50);
    }
}

//DISTANCE SENSOR SIMULATED BY POTENTIOMETER
//incoming data should be converted to desired unit (mm,cm,m etc.)
int get_distance()
{
    //ADC5
    ADMUX &= (ADMUX & 0xE0) | (0x05); //select ADC5
    
    ADCSRA |= (1<<ADSC); //START CONVERSION
    while(!(ADCSRA & (1<<ADIF))); //WAIT CONVERSION
    ADCSRA |= (1<<ADIF); //CLEAR by writing 1
    ADCSRA |= (1<<ADEN);
    
    return ADCH;
}
