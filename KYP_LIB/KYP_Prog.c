//*************************************************************************/
/******Auther   : George Ayman Sedky                                     */
/******Date     : 30/11/2020                                            */
/******Version  : V1.0                                                 */
/*********************************************************************/

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../DIO_LIB/DIO_Interface.h"
#include "../LCD_LIB/LCD_Config.h"
#include "KYP_Config.h"

u8 KYP_U8GetButton(void)
{
	u8 buttonValue=0;
	u8 col=0;
	u8 row=0;
	for(col=0;col<COL_NUM;col++)
	{
		DIO_VoidSetPinValue(KYP_PORT,col,LOW);
		for(row=0;row<ROW_NUM;row++)
		{
			if(DIO_U8GetPinValue(KYP_PORT,row+4)==0)
			{
				while(DIO_U8GetPinValue(KYP_PORT,row+4)==0);
				buttonValue=((row*COL_NUM)+col+1);
			}
		}
		DIO_VoidSetPinValue(KYP_PORT,col,HIGH);
		_delay_ms(10);
	}
	return buttonValue;
}
void KYP_VoidInit(void)
{
	DIO_VoidSetPortDirection(KYP_PORT,0x0F);
	DIO_VoidSetPortValue(KYP_PORT,0xFF);
}
