/*
 * lcd_lib.h
 * Created By: Ramandeep Singh
 * Created date: 11-Sep-2023
 */

#include <inttypes.h>

#define LCD_CONTROL_DDR		DDRC
#define LCD_CONTROL_PORT	PORTC
#define LCD_RS_PIN			6
#define LCD_RW_PIN			5
#define LCD_ENABLE_PIN		4
//
#define LCD_DATA1_DDR		DDRC
#define LCD_DATA1_PORT		PORTC
#define LCD_DATA1_PIN		PINC
#define LCD_D4				0
#define LCD_D5				1
#define LCD_D6				2
#define LCD_D7				3

#define LED_GREEN PORTA4
#define LED_RED PORTA5

 void lcd_cmd(uint8_t command)  //used to write instruction to LCD
 {
	 PORTC = command>>4;
	 PORTC &= (~(1<<LCD_RS_PIN)); //RS=0
	 PORTC &= (~(1<<LCD_RW_PIN));  //RW=0
	 PORTC |= (1<<LCD_ENABLE_PIN);	//EN=1
	 _delay_ms(10);		//10ms
	 PORTC &= (~(1<<LCD_ENABLE_PIN));	//EN=0
	 
	 PORTC = (command & 0x0F);
	 PORTC &= (~(1<<LCD_RS_PIN)); //RS=0
	 PORTC &= (~(1<<LCD_RW_PIN));  //RW=0
	 PORTC |= (1<<LCD_ENABLE_PIN);	//EN=1
	 _delay_ms(10);		//10ms
	 PORTC &= (~(1<<LCD_ENABLE_PIN));	//EN=0
	 
	 }
 
  void lcd_data(uint8_t data)  //for writing data to LCD
  {
	  PORTC = data>>4 ;
	  PORTC |=(1<<LCD_RS_PIN);  //RS=1
	  PORTC &=(~(1<<LCD_RW_PIN));  //RW=0
	  PORTC |=(1<<LCD_ENABLE_PIN);  //EN=1
	  _delay_ms(10);  //10ms
	  PORTC &=(~(1<<LCD_ENABLE_PIN)); //EN=0
	  
	  PORTC = (data & 0x0F);
	  PORTC |=(1<<LCD_RS_PIN);  //RS=1
	  PORTC &=(~(1<<LCD_RW_PIN));  //RW=0
	  PORTC |=(1<<LCD_ENABLE_PIN);  //EN=1
	  _delay_ms(10);  //10ms
	  PORTC &=(~(1<<LCD_ENABLE_PIN)); //EN=0
	  
  }
  
  void LCD_print(char *str)		/* Send string to LCD function */
  {
	  int i;
	  for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	  {
		  lcd_data(str[i]);
	  }
  }

void LCD_print_xy(uint8_t x, uint8_t y, char *str) {
	uint8_t position = 0x80; // Starting address of the first line
	if (y == 1) {
		position = 0xC0; // Starting address of the second line
		} else if (y == 2) {
		position = 0x94; // Starting address of the third line
		} else if (y == 3) {
		position = 0xD4; // Starting address of the fourth line
	}
	position += x; // Add the x-coordinate to the position
	lcd_cmd(position);  // Send the command to set the cursor position
	LCD_print(str);
	
}

void LCD_goto_XY(uint8_t x, uint8_t y) {
	// Define the starting addresses for each line of a 20x4 LCD
	static const uint8_t line_offsets[] = {0x00, 0x40, 0x14, 0x54};
	
	// Ensure x and y are within bounds
	if (x >= 20 || y >= 4) {
		return;  // Invalid coordinates
	}
	
	// Calculate the DDRAM address based on x and y
	uint8_t position = line_offsets[y] + x;
	
	// Set the cursor to the desired position
	lcd_cmd(0x80 | position);
}

//LCD_goto_XY(16, 3);
// Example usage to print a character at the cursor position
//lcd_data('A');

 void LCD_init()
 {
	 lcd_cmd(0x02);   //Set cursor to home position
	 lcd_cmd(0x28);  //4bit mode
	 lcd_cmd(0x06); //Entry Mode
	 lcd_cmd(0x0c); //display ON cursor OFF
	 lcd_cmd(0x01);   //clear the display
	 lcd_cmd(0x80);   //set cursor at line1
 }
 
void  LCD_clear()
{
lcd_cmd(0x01);	
lcd_cmd (0x80);
}

 
//void  LCD_pin_init();
//void  LCD_init();
//void  LCD_clear();
//void	LCD_send_data (uint8_t  data);
//void 	LCD_print (char *str);
//void 	LCD_print_xy (uint8_t x, uint8_t y, char *str); 
//void 	LCD_goto_XY (uint8_t x, uint8_t y);  
