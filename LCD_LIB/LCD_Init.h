//*************************************************************************/
/******Auther   : George Ayman Sedky                                     */
/******Date     : 30/11/2020                                            */
/******Version  : V1.0                                                 */
/*Description   : 16x2  LCD Initialization And Control Header         */
/*********************************************************************/

#ifndef LCD_LIB_LCD_INIT_H_
#define LCD_LIB_LCD_INIT_H_




void LCD_VoidInit(void);

void LCD_VoidSendCmd(u8 Copy_U8Cmd);


void LCD_VoidSendChar(u8 Copy_U8Char);

void LCD_VoidSendStr (u8* Ptr_Str);

void LCD_VoidSendNum(u16 Copy_U16Num);

void LCD_VoidGoToXY(u8 Copy_U8Row,u8 Copy_U8Col);

void LCD_VoidSendMyName (u8 Copy_U8Row,u8 Copy_U8Col);

void LCD_VoidSendSpcial (u8 Copy_U8Row,u8 Copy_U8Col);

void LCD_VoidSendCAT (u8 Copy_U8Col);
void LCD_VoidSendCAT2 (u8 Copy_U8Col);

#endif /* LCD_LIB_LCD_INIT_H_ */
