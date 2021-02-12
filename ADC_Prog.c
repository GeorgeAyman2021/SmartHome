/*
 * ADC_Prog.c
 *
 *  Created on: Dec 7, 2020
 *      Author: George Ayman
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DIO_LIB/DIO_Interface.h"
#include "ADC_Private.h"
void ADC_VidInit(void)
{
	//Voltage Reference Selection AVCC
	CLR_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
	//ADC Right Adjust Result
	CLR_BIT(ADMUX,ADLAR);
	//ADC Enable
	SET_BIT(ADCSRA,ADEN);
	//ADC Prescaler Select Bits I set it F/64
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	//Disable Interrupt
	CLR_BIT(ADCSRA,ADIE);
}


u16 ADC_U16Read(u8 Copy_U8Channel)
{
	u16 result=0;
	//Select Channel
	ADMUX&=0b11100000;
	ADMUX|=Copy_U8Channel;
	//Start Conversion
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADIF)==0);
	//Clear The Flag by put 1 in IT
	SET_BIT(ADCSRA,ADIF);
	//Read ADC
	result=ADCD;


	return result;
}
