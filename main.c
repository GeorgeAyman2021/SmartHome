/*
 * main.c
 *
 *  Created on: Dec 7, 2020
 *      Author: George Ayman
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DIO_LIB/DIO_Interface.h"
#include "LCD_LIB/LCD_Init.h"
#include "LCD_LIB/LCD_Config.h"
#include "KYP_LIB/KYP_Init.h"
#include "KYP_LIB/KYP_Config.h"
#include "ADC_Init.h"
#include "7Seg_Int.h"
#include "util/delay.h"

#define Potentiometer		PIN0
#define LDR 				PIN1
#define Buzzer				PIN2
#define Rknown				10000


void GET_PASS(void)
{
	u8 pass[4]={0};
	u8 i=0 ,j =0;
	u8 press=0;
	DIO_VoidSetPinValue(PORTA,PIN4,HIGH);
	while(j<3)
	{
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(10);
		LCD_VoidGoToXY(0,0);
		LCD_VoidSendStr("Enter Password :");
		LCD_VoidGoToXY(0,1);
		if(j==0)
		{
			SEG_VoidPrint(PORTC,three);
		}
		else if (j==1)
		{
			SEG_VoidPrint(PORTC,two);
		}
		else if(j==2)
		{
			SEG_VoidPrint(PORTC,one);
		}

		while(press!=16)
		{
			press=0;
			while(press==0)
			{press=KYP_U8GetButton();}
			if(i<4)
				pass[i]=press;
			LCD_VoidSendNum(press);
			i++;
		}
		i=0;
		press=0;
		if(pass[0]==1&&pass[1]==2&&pass[2]==3&&pass[3]==4)
		{
			LCD_VoidSendCmd(LCD_CLEAR);
			_delay_ms(10);
			LCD_VoidGoToXY(0,0);
			LCD_VoidSendStr("Wellcome Gogo");
			_delay_ms(1000);
			LCD_VoidSendCmd(LCD_CLEAR);
			_delay_ms(10);
			break;
		}
		else{
			LCD_VoidSendCmd(LCD_CLEAR);
			_delay_ms(10);
			LCD_VoidGoToXY(0,0);
			LCD_VoidSendStr("Wrong Password !");
			LCD_VoidGoToXY(0,1);
			LCD_VoidSendStr("Try Again");
			_delay_ms(500);
			if(j==2)
			{
				LCD_VoidSendCmd(LCD_CLEAR);
				_delay_ms(10);
				LCD_VoidGoToXY(0,0);
				LCD_VoidSendStr("You Enter Wrong Password 3 Times");
				SEG_VoidPrint(PORTC,zero);
				while(1){
					LCD_VoidSendCmd(LCD_SHIFT_LEFT);
					_delay_ms(750);

				}

			}
		}
		j++;
	}
}

u8 Meneu(void)
{
	u8 press=0;
	LCD_VoidSendCmd(LCD_CLEAR);
	_delay_ms(10);
	while(press==0){

		LCD_VoidGoToXY(0,0);
		LCD_VoidSendStr("1-Pot    2-LDR");
		LCD_VoidGoToXY(0,1);
		LCD_VoidSendStr("3-both   4-close");

		press=KYP_U8GetButton();
		Check_LDR();
	}

	return press;
}

void Poten_Read(void)
{
	u8 press=0;

	while(press!=16){
		Check_LDR();
		press=KYP_U8GetButton();
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(10);
		LCD_VoidGoToXY(0,0);
		LCD_VoidSendStr("Analog value : ");
		LCD_VoidGoToXY(0,1);
		u16 Dig_ADC=ADC_U16Read(Potentiometer);
		u16 Anl_Pot=(Dig_ADC * 5000UL )/1023;
		LCD_VoidSendNum(Anl_Pot);
		_delay_ms(500);
	}

}

void LDR_Read(void)
{
	u8 press=0;

	while(press!=16){
		Check_LDR();
		press=KYP_U8GetButton();
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(10);
		LCD_VoidGoToXY(0,0);
		LCD_VoidSendStr("LDR Value : ");
		LCD_VoidGoToXY(0,1);
		u16 Dig_ADC=ADC_U16Read(LDR);
		u16 Anl_LDR=(Dig_ADC * 5000UL )/1023;
		u16 read = (((Rknown*5000)-(Rknown*Anl_LDR))/Anl_LDR);
		LCD_VoidSendNum(read);
		_delay_ms(500);
	}

}
void Both_Read(void)
{
	u8 press=0;
	u16 Dig_ADCPOT,Anl_ADC, Dig_ADCLDR, Anl_LDR,read;
	while(press!=16){
		Check_LDR();
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(10);
		LCD_VoidGoToXY(0,0);
		LCD_VoidSendStr("Pot : ");
		Dig_ADCPOT=ADC_U16Read(Potentiometer);
		Anl_ADC=(Dig_ADCPOT * 5000UL )/1023;
		LCD_VoidSendNum(Anl_ADC);
		LCD_VoidGoToXY(0,1);
		LCD_VoidSendStr("LDR Value : ");
		Dig_ADCLDR=ADC_U16Read(LDR);
		Anl_LDR=(Dig_ADCLDR * 5000UL )/1023;
		read = (((Rknown*5000)-(Rknown*Anl_LDR))/Anl_LDR);
		LCD_VoidSendNum(read);
		_delay_ms(1000);
		press=KYP_U8GetButton();
	}
}
void Check_LDR(void)
{
	u16 Dig_ADC=ADC_U16Read(LDR);
	u16 Anl_LDR=(Dig_ADC * 5000UL )/1023;
	u16 read = (((Rknown*5000)-(Rknown*Anl_LDR))/Anl_LDR);
	while(read>2500)
	{
		LCD_VoidSendCmd(LCD_CLEAR);
		_delay_ms(10);
		LCD_VoidGoToXY(5,0);
		LCD_VoidSendStr("Warning");
		LCD_VoidGoToXY(5,1);
		LCD_VoidSendStr("No Light ");
		DIO_VoidSetPinValue(PORTA,Buzzer,HIGH);
		_delay_ms(250);
		DIO_VoidSetPinValue(PORTA,Buzzer,LOW);
		_delay_ms(250);
		Dig_ADC=ADC_U16Read(LDR);
		Anl_LDR=(Dig_ADC * 5000UL )/1023;
		read = (((Rknown*5000)-(Rknown*Anl_LDR))/Anl_LDR);
	}
}

void main(void){

	u8 Men_res=0;
	DIO_VoidSetPinDirection(PORTA,Potentiometer,INPUT);
	DIO_VoidSetPinDirection(PORTA,LDR ,INPUT);
	DIO_VoidSetPinDirection(PORTA,Buzzer,OUTPUT);
	DIO_VoidSetPinDirection(PORTA,PIN4,OUTPUT);
	DIO_VoidSetPortDirection(PORTC,0xff);

	ADC_VidInit();
	LCD_VoidInit();
	KYP_VoidInit();
	LCD_VoidSendCmd(LCD_CLEAR);
	_delay_ms(10);
	LCD_VoidGoToXY(0,0);
	LCD_VoidSendStr("Wellcom to Gogo");
	LCD_VoidGoToXY(0,1);
	LCD_VoidSendStr("Smart Home ");
	_delay_ms(1000);
	GET_PASS();
	DIO_VoidSetPinValue(PORTA,PIN4,LOW);


	while(1)
	{

		Men_res=Meneu();

		if(Men_res==1)
		{
			Poten_Read();
		}
		else if(Men_res==2)
		{
			LDR_Read();
		}
		else if (Men_res==3)
		{
			Both_Read();
		}
		else if( Men_res==4)
		{
			LCD_VoidSendCmd(LCD_CLEAR);
			_delay_ms(10);
			LCD_VoidGoToXY(0,0);
			LCD_VoidSendStr("System Closed");
			while(1);
		}
		else
		{
			LCD_VoidSendCmd(LCD_CLEAR);
			_delay_ms(10);
			LCD_VoidGoToXY(0,0);
			LCD_VoidSendStr("Wrong Choise");
			_delay_ms(500);

		}
		Check_LDR();
		Men_res=0;

	}
}

