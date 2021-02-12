/*
 * LCD_Prog.c
 *
 *  Created on: Nov 30, 2020
 *      Author: George Ayman
 */


#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../DIO_LIB/DIO_Interface.h"
#include "LCD_Config.h"

void LCD_VoidInit(void)
{
	DIO_VoidSetPinDirection(CONTROL_PORT,RS,OUTPUT);
	DIO_VoidSetPinDirection(CONTROL_PORT,RW,OUTPUT);
	DIO_VoidSetPinDirection(CONTROL_PORT,En,OUTPUT);
	DIO_VoidSetPortDirection(DATA_PORT,0xff);
	_delay_ms(35);
  	#if MODE==EIGHT_BIT
		LCD_VoidSendCmd(LCD_FUNCTIONSET_8BIT);
		_delay_ms(1);
		LCD_VoidSendCmd(LCD_DISPLAYON);
		_delay_ms(1);
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(2);

	#elif MODE==FOUR_BIT

		LCD_VoidSendCmd(LCD_HOME);
		_delay_ms(1);
		LCD_VoidSendCmd(LCD_FUNCTIONSET_4BIT);
		_delay_ms(1);
		LCD_VoidSendCmd(LCD_DISPLAYON);
		_delay_ms(1);
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(15);
		LCD_VoidSendCmd(LCD_ENTERYMODE);
		_delay_ms(2);

    #endif
}

void LCD_VoidSendCmd(u8 Copy_U8Cmd)
{
#if MODE==EIGHT_BIT
	//Reset (RS&RW)pins.
	DIO_VoidSetPinValue(CONTROL_PORT,RS,LOW);
	DIO_VoidSetPinValue(CONTROL_PORT,RW,LOW);
	//Send command through data port
	DIO_VoidSetPortValue(DATA_PORT,Copy_U8Cmd);
	/*Set the (E) pin for a period
		defined in datasheet ( 1ms is
		working) then reset it.*/
	DIO_VoidSetPinValue(CONTROL_PORT,En,HIGH);
	_delay_ms(1);
	DIO_VoidSetPinValue(CONTROL_PORT,En,LOW);
#elif MODE==FOUR_BIT
	//Reset (RS&RW)pins.
	DIO_VoidSetPinValue(CONTROL_PORT,RS,LOW);
	DIO_VoidSetPinValue(CONTROL_PORT,RW,LOW);
	//Send most 4 bits command through data port
	DIO_VoidSetPortValue(DATA_PORT,Copy_U8Cmd);
	/*Set the (E) pin for a period
		defined in datasheet ( 1ms is
		working) then reset it.*/
	DIO_VoidSetPinValue(CONTROL_PORT,En,HIGH);
	_delay_ms(1);
	DIO_VoidSetPinValue(CONTROL_PORT,En,LOW);
	//Send least command through data port
	_delay_ms(5);
		DIO_VoidSetPortValue(DATA_PORT,(Copy_U8Cmd<<4));
		/*Set the (E) pin for a period
			defined in datasheet ( 1ms is
			working) then reset it.*/
		DIO_VoidSetPinValue(CONTROL_PORT,En,HIGH);
		_delay_ms(1);
		DIO_VoidSetPinValue(CONTROL_PORT,En,LOW);
#endif
}


void LCD_VoidSendChar(u8 Copy_U8Char)
{
#if MODE==EIGHT_BIT
	//Set RS and Reset RW pins
	DIO_VoidSetPinValue(CONTROL_PORT,RS,HIGH);
	DIO_VoidSetPinValue(CONTROL_PORT,RW,LOW);
	//Send DATA through data port.
	DIO_VoidSetPortValue(DATA_PORT,Copy_U8Char);
	/*Set the (E) pin for a period
		defined in datasheet ( 1ms is
		working) then reset it.*/
	DIO_VoidSetPinValue(CONTROL_PORT,En,HIGH);
	_delay_ms(1);
	DIO_VoidSetPinValue(CONTROL_PORT,En,LOW);
#elif MODE==FOUR_BIT
	//Set RS and Reset RW pins
		DIO_VoidSetPinValue(CONTROL_PORT,RS,HIGH);
		DIO_VoidSetPinValue(CONTROL_PORT,RW,LOW);
		//Send Most 4 bits DATA through data port.
		DIO_VoidSetPortValue(DATA_PORT,Copy_U8Char);
		/*Set the (E) pin for a period
			defined in datasheet ( 1ms is
			working) then reset it.*/
		DIO_VoidSetPinValue(CONTROL_PORT,En,HIGH);
		_delay_ms(1);
		DIO_VoidSetPinValue(CONTROL_PORT,En,LOW);
		//Send Least 4 bits DATA through data port.
		_delay_ms(5);
		DIO_VoidSetPortValue(DATA_PORT,(Copy_U8Char<<4));
		/*Set the (E) pin for a period
			defined in datasheet ( 1ms is
			working) then reset it.*/
		DIO_VoidSetPinValue(CONTROL_PORT,En,HIGH);
		_delay_ms(1);
		DIO_VoidSetPinValue(CONTROL_PORT,En,LOW);
#endif
}

void LCD_VoidSendStr (u8* Ptr_Str)
{
	u8 i=0;
	while(Ptr_Str[i]!='\0')
	{
		LCD_VoidSendChar(Ptr_Str[i]);
		i++;
	}
}
void LCD_VoidSendNum(u16 Copy_U16Num)
{
	if (Copy_U16Num==0)
	{
		LCD_VoidSendChar('0');
	}
	s8 i=0;
	u8 str_num[5];
	while(Copy_U16Num>0)
	{
		str_num[i]=Copy_U16Num%10;
		Copy_U16Num/=10;
		i++;
	}
	i--;
	while(i>=0)
	{
		switch(str_num[i])
		{
			case 0 : LCD_VoidSendChar('0');break;
			case 1 : LCD_VoidSendChar('1');break;
			case 2 : LCD_VoidSendChar('2');break;
			case 3 : LCD_VoidSendChar('3');break;
			case 4 : LCD_VoidSendChar('4');break;
			case 5 : LCD_VoidSendChar('5');break;
			case 6 : LCD_VoidSendChar('6');break;
			case 7 : LCD_VoidSendChar('7');break;
			case 8 : LCD_VoidSendChar('8');break;
			case 9 : LCD_VoidSendChar('9');break;
		}

		i--;
	}
}

void LCD_VoidGoToXY(u8  Copy_U8Col,u8 Copy_U8Row)
{
	if (Copy_U8Row==0)
	{
		LCD_VoidSendCmd(LCD_SETCURSER0+Copy_U8Col);//127
	}
	else if (Copy_U8Row==1)
	{
		LCD_VoidSendCmd(LCD_SETCURSER1+Copy_U8Col);//191
	}
}


void LCD_VoidSendMyName (u8 Copy_U8Row,u8 Copy_U8Col)
{

	const u8 MyName[]=
	{
			0x00, 0x04, 0x00, 0x0A, 0x0B, 0x0A, 0x0E, 0x00,
			0x00, 0x00, 0x04, 0x0A, 0x1B, 0x0A, 0x04, 0x00,
			0x00, 0x00, 0x02, 0x02, 0xFE, 0x00, 0x0C, 0x00,
			0x06, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00,
			0x00, 0x0F, 0x01, 0x0F, 0x08, 0x0A, 0x08, 0x0F,
			0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x18,
			0x00, 0x00, 0x0E, 0x0A, 0x0F, 0x02, 0x04, 0x08,
			0x00, 0x00, 0x07, 0x01, 0xFF, 0x00, 0x02, 0x00,
	};

    u8 i,j;
    LCD_VoidSendCmd(LCD_CGRAM_ADD0);
	for(i=0 ; i<64 ; i++)
	{
		LCD_VoidSendChar(MyName[i]);
	}

	LCD_VoidSendCmd(LCD_DDRAM_ADD0);

	LCD_VoidGoToXY(Copy_U8Row,Copy_U8Col);

	for (j=0; j<=7 ; j++)
	{
		LCD_VoidSendChar(j);
	}
}


void LCD_VoidSendSpcial (u8 Copy_U8Row,u8 Copy_U8Col) //BING BONG
{

	u8 Game[]= {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,// Right
				0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,//Left
				0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00 //Ball

	};


    u8 i,j;
    LCD_VoidSendCmd(LCD_CGRAM_ADD0);
	for(i=0 ; i<24 ; i++)
	{
		LCD_VoidSendChar(Game[i]);
	}

	LCD_VoidSendCmd(LCD_DDRAM_ADD0);

	LCD_VoidGoToXY(Copy_U8Row,Copy_U8Col);
	for(j=0;j<3;j++){
	LCD_VoidSendChar(j);
	}

}
void LCD_VoidSendCAT (u8 Copy_U8Col)
{
	const u8 MyCat[]=
		{

				0x00, 0x1f,	 0x11, 0x15, 0B10001, 0B11111, 0B00000, 0B00000,

				0B00000,
				 0B00000,
				 0B00000,
				  0B00000,
				 0B00000,
				  0B11111,
				  0B11111,
				  0B11111,

				  0x00, 0x1f,	 0x11, 0x15, 0B10001, 0B11111, 0B00000, 0B00000,

				  0B00000,
				  					 0B00000,
				  					  0B11000,
				  					  0B11000,
				  					  0B11000,
				  					  0B11000,
				  					  0B11000,
				  					  0B11000,


					 0B00000,
					 0B00000,
					  0B11000,
					  0B11000,
					  0B11000,
					  0B11000,
					  0B11000,
					  0B11000



		};

	    u8 i,j;
	    LCD_VoidSendCmd(LCD_CGRAM_ADD0);
		for(i=0 ; i<40 ; i++)
		{
			LCD_VoidSendChar(MyCat[i]);
		}

		LCD_VoidSendCmd(LCD_DDRAM_ADD0);

		LCD_VoidGoToXY(0,Copy_U8Col);
		for(j=0;j<3;j++){
			LCD_VoidSendChar(j);
			}
		LCD_VoidGoToXY(1,Copy_U8Col);
		LCD_VoidSendChar(3);
		LCD_VoidGoToXY(1,Copy_U8Col+2);
		LCD_VoidSendChar(4);

}
void LCD_VoidSendCAT2 (u8 Copy_U8Col)
{
	const u8 MyCat[]=
		{

				 0B00000,
									   0B00000,
									   0B00000,
									   0B11111,
									   0B00000,
									   0B00000,
									   0B00000,
									   0B00000,

				0B00000,
				 0B00000,
				 0B00000,
				  0B00000,
				 0B00000,
				  0B11111,
				  0B11111,
				  0B11111,

				  0B00000,
				 					   0B00000,
				 					   0B00000,
				 					   0B11111,
				 					   0B00000,
				 					   0B00000,
				 					   0B00000,
				 					   0B00000,

									   0B00000,
									     0B00000,
									     0B11000,
									     0B11000,
									     0B01100,
									     0B00110,
									     0B00011,
									     0B00000,

										 0B00000,
										 									     0B00000,
										 									     0B11000,
										 									     0B11000,
										 									     0B01100,
										 									     0B00110,
										 									     0B00011,
										 									     0B00000



		};

	    u8 i,j;
	    LCD_VoidSendCmd(LCD_CGRAM_ADD0);
		for(i=0 ; i<40 ; i++)
		{
			LCD_VoidSendChar(MyCat[i]);
		}

		LCD_VoidSendCmd(LCD_DDRAM_ADD0);

		LCD_VoidGoToXY(0,Copy_U8Col);
		for(j=0;j<3;j++){
			LCD_VoidSendChar(j);
			}
		LCD_VoidGoToXY(1,Copy_U8Col);
		LCD_VoidSendChar(3);
		LCD_VoidGoToXY(1,Copy_U8Col+2);
		LCD_VoidSendChar(4);

}

