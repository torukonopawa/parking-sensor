#include "LCD.h"
#include "configuration.h"

void LCD_Enable_Pulse()
{
    LCD_Cmd_Port |= (1<<EN);
    _delay_us(1);
    LCD_Cmd_Port &= ~ (1<<EN);
}

void LCD_Command(unsigned char cmnd)
{
    LCD_Cmd_Port &= ~ (1<<RS); /* RS=0, command reg. */
    
    LCD_Data_Port = (LCD_Data_Port & 0xF0) | (cmnd >> 4); /* sending upper nibble */
    LCD_Enable_Pulse();
    
    _delay_us(200);
    
    LCD_Data_Port = (LCD_Data_Port & 0xF0) | (cmnd & 0x0F); /* sending lower nibble */
    LCD_Enable_Pulse();
    
    _delay_ms(2);
}

void LCD_Char(unsigned char data)
{
    LCD_Cmd_Port |= (1<<RS); /* RS=1, data reg. */
    
    LCD_Data_Port = (LCD_Data_Port & 0xF0) | (data >> 4); /* sending upper nibble */
    LCD_Enable_Pulse();
    
    _delay_us(200);
    
    LCD_Data_Port = (LCD_Data_Port & 0xF0) | (data & 0x0F); /* sending lower nibble */
    LCD_Enable_Pulse();
    
    _delay_ms(2);
}

void LCD_Init(void)
{
    LCD_Cmd_Dir = 0xFF;
    LCD_Data_Dir = 0xFF;
    _delay_ms(20); /* LCD Power ON delay always >15ms */
    
    LCD_Command(0x02); /* send for 4 bit initialization of LCD */
    LCD_Command(0x28); /* 2 line, 5*7 matrix in 4-bit mode */
    LCD_Command(0x0c); /* Display on cursor off*/
    LCD_Command(0x06); /* Increment cursor (shift cursor to right)*/
    LCD_Command(0x01); /* Clear display screen*/
    
    _delay_ms(2);
}

void LCD_String(char *str)
{
    int i;
    for(i=0;str[i]!=0;i++) /* Send each char of string till the NULL */
    {
        LCD_Char(str[i]);
    }
}

void LCD_Integer(char num)
{
    char d1 = '0', d2 = '0', d3 = '0';
    int temp = num / 100;
    
    d1 = d1 + temp;
    d2 = d2 + (num-temp*100) / 10;
    d3 = d3 + num % 10;
    
    LCD_Char(d1);
    LCD_Char(d2);
    LCD_Char(d3);
}

void LCD_Distance_RGB(char distance, char Red, char Green, char Blue)
{
    LCD_String("Distance: ");
    LCD_Command((10 & 0x0F)|0x80); /* Command of first row and required position<16 */
    LCD_Integer(distance);
    LCD_String(" cm");
    
    LCD_Command(0xC0); //next line
    
    LCD_String("RGB: ");
    LCD_Integer(Red); LCD_Char(',');
    LCD_Integer(Green); LCD_Char(',');
    LCD_Integer(Blue);
}
void LCD_String_xy(char row, char pos, char *str) /* Send string to LCD with xy position */
{
    if(row == 0 && pos<16)
        LCD_Command((pos & 0x0F)|0x80); /* Command of first row and required position<16 */
    else if(row == 1 && pos<16)
        LCD_Command((pos & 0x0F)|0xC0); /* Command of first row and required position<16 */
    
    LCD_String(str); /* Call LCD string function */
}

void LCD_Clear()
{
    LCD_Command(0x01); /* Clear display */
    _delay_ms(2);
    LCD_Command(0x80); /* Cursor at home position */
}
