/*
 * 7Seg_Prog.c
 *
 *  Created on: Nov 29, 2020
 *      Author: George Ayman
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DIO_LIB/DIO_Interface.h"
#include "util/delay.h"


void  SEG_VoidPrint(u8 Copy_u8Port , u8 Copy_u8Number)
{
	DIO_VoidSetPortValue(Copy_u8Port,Copy_u8Number);
}
