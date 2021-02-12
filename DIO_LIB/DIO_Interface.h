/*************************************************************************/
/******Auther   : George Ayman Sedky                                    */
/******Date     : 29/11/2020                                           */
/******Version  : V1.0                                                */
/*Description   : Digital Input Output  Interface function Arch      */
/********************************************************************/
#ifndef DIO_Interface_H
#define DIO_Interface_H


#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

#define INPUT  0
#define OUTPUT 1

#define HIGH   1
#define LOW    0


void DIO_VoidSetPortDirection   (u8 Copy_U8Port,u8 Copy_U8Status);

void DIO_VoidSetPortValue       (u8 Copy_U8Port,u8 Copy_U8Status);

void DIO_VoidSetPinDirection    (u8 Copy_U8Port,u8 Copy_U8PinId,u8 Copy_U8Status);

void DIO_VoidSetPinValue        (u8 Copy_U8Port,u8 Copy_U8PinId,u8 Copy_U8Status);

void DIO_VoidTogglePin          (u8 Copy_U8Port,u8 Copy_U8PinId);

u8   DIO_U8GetPinValue          (u8 Copy_U8Port,u8 Copy_U8PinId);

#endif