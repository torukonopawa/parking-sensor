#ifndef LCD_H_
#define LCD_H_

    void LCD_Command(unsigned char cmnd);
    void LCD_Init(void);
    void LCD_String(char *str);
    void LCD_String_xy(char row, char pos, char *str);
    void LCD_Clear();
    void LCD_Distance_RGB(char distance, char Red, char Green, char Blue);

#endif /* LCD_H_ */
