#include "lcd.h"

#include "lcd.h"
#include<stdio.h>
//#define Lcd_Strobe  ((EN_SetHigh()),(__delay_ms(1)),(EN_SetLow()))

/**
	* @brief  Function to set/reset enable pin for latching the data to data lines of LCD   
	* @param  None
	* @retval None
	*/
void Lcd_Strobe(void)
{
    EN_SetHigh();
    __delay_ms(1);
    EN_SetLow();    
}
/**
	* @brief  Main Function to give command to all the functions  
	* @param  None
	* @retval None
	*/
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();        //to initialize GPIO pins & clock of controller
    Lcd_Init();

    while (1)
    {
    Lcd_Clear();    
    Lcd_Set_Cursor(1,0);
    Lcd_Write_String("Hello world");
    __delay_ms(10);
    Lcd_Set_Cursor(2,0);
    Lcd_Write_String("Let's Do it!");
    __delay_ms(10);
    }
}
/**
	* @brief  Function to Reset LCD module   
	* @param  None
  * @retval None
	*/
void Lcd_Reset(void)
{
	Lcd_Bits_Write(0xFF);            //LCD_PORT = 0xFF;
	__delay_ms(20); 
    Lcd_Strobe();
    Lcd_Bits_Write(0x30);            //LCD_PORT = 0x03;
    Lcd_Strobe() ;
	__delay_ms(10);
	Lcd_Bits_Write(0x30);            //LCD_PORT = 0x03;
    Lcd_Strobe();
	__delay_ms(1);
    Lcd_Bits_Write(0x30);            //LCD_PORT = 0x03;
    Lcd_Strobe();
	__delay_ms(1);
	Lcd_Bits_Write(0x20);            //LCD_PORT = 0x02;
    Lcd_Strobe();
	__delay_ms(1);    
}
/**
	* @brief  Function to Initialize the LCD by sending some command   
	* @param  None
  * @retval None
	*/
void Lcd_Init()
{
	Lcd_Reset();         // Call LCD reset
    __delay_ms(10); 
	Lcd_Cmd(0x28);       // 4-bit mode - 2 line - 5x7 font.
    __delay_ms(10); 
	Lcd_Cmd(0x0C);       // Display no cursor - no blink.
    __delay_ms(10); 
	Lcd_Cmd(0x06);       // Automatic Increment - No Display shift.
    __delay_ms(10); 
	Lcd_Cmd(0x80);       // Address DDRAM with 0 offset 80h.
    __delay_ms(10); 
 }
/**
	* @brief  Function to send the Commands to the LCD
	* @param  cmd : 8-bit command for lcd
	* @retval None
	*/
void Lcd_Cmd(char cmd)
{ 
	RS_SetLow();
    Lcd_Bits_Write(cmd & 0xF0);
    Lcd_Strobe();
 	__delay_ms(1); 

	Lcd_Bits_Write((cmd<<4) & 0xF0);
    Lcd_Strobe();
 	__delay_ms(1);    
  }
/**
	* @brief  Function to send the Data to the LCD 
	* @param  data : 8-bit data which nees to display on lcd
	* @retval None
	*/
void Lcd_Data(char data)
{ 
    RS_SetHigh();
	Lcd_Bits_Write((data  & 0xF0));
    Lcd_Strobe();
	__delay_ms(1);
	Lcd_Bits_Write(((data<<4) & 0xF0));
    Lcd_Strobe(); 
	__delay_ms(1);
}
/**
	* @brief  Function to Clear the Contents of the LCD   
	* @param  None
  * @retval None
	*/
void Lcd_Clear()
{
	  Lcd_Cmd(0x10);
      __delay_ms(10);
}
/**
	* @brief  Function to set the cursor location on the LCD   
	* @param  row : Row number location of LCD
	* @param  col : Column number location of LCD (starts from 0to15)
	* @retval None
	*/
void Lcd_Set_Cursor(char row, char col)
{
	if(row == 1)
	  Lcd_Cmd(0x80 + col);
	else if(row == 2)
       Lcd_Cmd(0xC0 + col);
    __delay_ms(1); 
}
/**
	* @brief  Function to set/reset particular data bits   
	* @param  Bits : to send on particular data bits of lcd
	* @retval None
	*/
void Lcd_Bits_Write(char Bits)							//it is for 4-bits only & Bits will be recieved in MSB only
{
	if((0x10 & Bits) == 0x10)                        //for lower bits do masking with 0b00000001
    {
        D4_SetHigh();                       //set D4 bit of lcd
    }
		
    else
    {
        D4_SetLow();                      //reset D4 bit of lcd
    }
      
	
	if((0x20 & Bits) == 0x20)                        //for lower bits do masking with 0b00000010
    {
        D5_SetHigh();                     //set D5 bit of lcd
    }
		
    else
    {
        D5_SetLow();                    //reset D5 bit of lcd
    }
        	
	
	if((0x40 & Bits) == 0x40)                        //for lower bits do masking with 0b00000100
    {
        D6_SetHigh();                 //set D5 bit of lcd
    }
		
    else
    {
        D6_SetLow();                  //reset D6 bit of lcd
    }
       

	if((0x80 & Bits) == 0x80)                        //for lower bits do masking with 0b00001000
    {
        D7_SetHigh();               //set D5 bit of lcd
    }
		
    else
    {
        D7_SetLow();                //reset D7 bit of lcd
    }
}
/**
	* @brief  Function to write the string on the LCD
	* @param  Str : String pointer
	* @retval None
	*/
void Lcd_Write_String(unsigned char *Str)
{
	int i;
	for(i=0; Str[i]!='\0'; i++)
	 Lcd_Data(Str[i]);
   __delay_ms(10);   
}
/**
	* @brief  Function to send integer value on lcd  
	* @param  IntToBeDisplayed : integer value which needs to display on lcd
	* @retval None
	*/
void Lcd_Send_Int(int IntToBeDisplayed)
{
    char int2string[5];
    sprintf(int2string, "%d", IntToBeDisplayed);
    Lcd_Write_String(int2string);
}
/**
	* @brief  Function to send float value on lcd  
	* @param  FloatToBeDisplayed : float value which needs to display on lcd
	* @retval None
	*/
void Lcd_Send_Float(float FloatToBeDisplayed)
{
    char float2string[5] = "";
    sprintf(float2string, "%f", FloatToBeDisplayed);
    Lcd_Write_String(float2string);
}
/**
 End of File
*/

