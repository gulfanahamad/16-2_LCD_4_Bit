#ifndef LCD_H
#define LCD_H
#define LCD_PORT    PORTB             //upper 4-bits of PORTB register


void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Cmd(char cmd);
void Lcd_Data(char data);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char row, char col);
void Lcd_Write_Char(char a);
void Lcd_Write_String(unsigned char *a);
void Lcd_Send_Int(int IntToBeDisplayed);
void Lcd_Send_Float(float FloatToBeDisplayed);
void Lcd_Bits_Write(char Bits);							//it is for 4-bits only & Bits will be recieved in MSB only

void Lcd_Strobe(void);                                  //to set & reset EN pin of LCD

void Lcd_Init();
void Lcd_Cmd (char cmd);
void Lcd_Data(char data);

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Set_Cursor(char a, char b);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();


#endif
