/*************************************************************************/
/******Auther   : George Ayman Sedky                                    */
/******Date     : 29/11/2020                                           */
/******Version  : V1.0                                                */
/*Description   : DIO  Interface function Implemntation              */
/********************************************************************/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "DIO_PrivateRegisters.h"

void DIO_VoidSetPortDirection   (u8 Copy_U8Port,u8 Copy_U8Status)
{ 
	switch (Copy_U8Port)
	{
	case 0: DDRA=Copy_U8Status ;break;
	case 1: DDRB=Copy_U8Status ;break;
	case 2: DDRC=Copy_U8Status ;break;
	case 3: DDRD=Copy_U8Status ;break;
	}

}

void DIO_VoidSetPortValue       (u8 Copy_U8Port,u8 Copy_U8Status)
{   

	switch (Copy_U8Port)
	{
	case 0: PORTA=Copy_U8Status ;break;
	case 1: PORTB=Copy_U8Status ;break;
	case 2: PORTC=Copy_U8Status ;break;
	case 3: PORTD=Copy_U8Status ;break;
	}
}

void DIO_VoidSetPinDirection    (u8 Copy_U8Port,u8 Copy_U8PinId,u8 Copy_U8Status)
{
	if (Copy_U8Status == 1)
	{
		switch (Copy_U8Port)
		{
		case 0: SET_BIT(DDRA,Copy_U8PinId);break;
		case 1: SET_BIT(DDRB,Copy_U8PinId);break;
		case 2: SET_BIT(DDRC,Copy_U8PinId);break;
		case 3: SET_BIT(DDRD,Copy_U8PinId);break;
		}
	}
	else if (Copy_U8Status==0)
	{
		switch (Copy_U8Port)
		{
		case 0: CLR_BIT(DDRA,Copy_U8PinId);break;
		case 1: CLR_BIT(DDRB,Copy_U8PinId);break;
		case 2: CLR_BIT(DDRC,Copy_U8PinId);break;
		case 3: CLR_BIT(DDRD,Copy_U8PinId);break;
		}
	}
}

void DIO_VoidSetPinValue        (u8 Copy_U8Port,u8 Copy_U8PinId,u8 Copy_U8Status)
{
	if (Copy_U8Status == 1)
	{
		switch (Copy_U8Port)
		{
		case 0: SET_BIT(PORTA,Copy_U8PinId);break;
		case 1: SET_BIT(PORTB,Copy_U8PinId);break;
		case 2: SET_BIT(PORTC,Copy_U8PinId);break;
		case 3: SET_BIT(PORTD,Copy_U8PinId);break;
		}
	}
	else if (Copy_U8Status==0)
	{
		switch (Copy_U8Port)
		{
		case 0: CLR_BIT(PORTA,Copy_U8PinId);break;
		case 1: CLR_BIT(PORTB,Copy_U8PinId);break;
		case 2: CLR_BIT(PORTC,Copy_U8PinId);break;
		case 3: CLR_BIT(PORTD,Copy_U8PinId);break;
		}
	}
}

void DIO_VoidTogglePin          (u8 Copy_U8Port,u8 Copy_U8PinId)
{
	switch (Copy_U8Port)
	{
	case 0: TOG_BIT(PORTA,Copy_U8PinId);break;
	case 1: TOG_BIT(PORTB,Copy_U8PinId);break;
	case 2: TOG_BIT(PORTC,Copy_U8PinId);break;
	case 3: TOG_BIT(PORTD,Copy_U8PinId);break;
	}
}

u8   DIO_U8GetPinValue          (u8 Copy_U8Port,u8 Copy_U8PinId)
{
	u8 Local_Result=0;
	switch (Copy_U8Port)
	{
	case 0: Local_Result=GET_BIT(PINA,Copy_U8PinId);break;
	case 1: Local_Result=GET_BIT(PINB,Copy_U8PinId);break;
	case 2: Local_Result=GET_BIT(PINC,Copy_U8PinId);break;
	case 3: Local_Result=GET_BIT(PIND,Copy_U8PinId);break;
	}
	return Local_Result;
}
