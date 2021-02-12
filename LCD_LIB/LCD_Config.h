/*
 * LCD_Config.h
 *
 *  Created on: Nov 30, 2020
 *      Author: George Ayman
 */

#ifndef LCD_LIB_LCD_CONFIG_H_
#define LCD_LIB_LCD_CONFIG_H_

#define MODE  			FOUR_BIT

#define	RS				PIN7
#define RW				PIN6
#define En				PIN5

#define D0				PIN0
#define	D1				PIN1
#define D2				PIN2
#define	D3				PIN3
#define D4				PIN4
#define	D5				PIN5
#define D6				PIN6
#define	D7				PIN7

#define DATA_PORT		PORTD
#define CONTROL_PORT 	PORTA




#define EIGHT_BIT					0
#define FOUR_BIT					1


#define LCD_CLEAR    			    0X01
#define LCD_HOME       				0x02
#define LCD_ENTERYMODE 				0x06
#define LCD_DISPLAYOFF 				0x08
#define LCD_DISPLAYON			 	0x0c
#define LCD_SETCURSER0              0x80
#define LCD_SETCURSER1              0xc0
#define LCD_FUNCTION_RESET  		0x30
#define LCD_FUNCTIONSET_8BIT        0x38
#define LCD_FUNCTIONSET_4BIT        0x28
#define LCD_SHIFT_LEFT				0x18
#define LCD_SHIFT_RIGHT				0x1c
#define LCD_CGRAM_ADD0				0x40
#define LCD_DDRAM_ADD0				0x80



// Ø­Ø±Ù� Ø§Ù„ Ø¬
//   0x00,0x00,0x0E,0x02,0xFE,0x04,0x00,0x00



#endif /* LCD_LIB_LCD_CONFIG_H_ */
