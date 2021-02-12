/*
 * 7Seg_Int.h
 *
 *  Created on: Nov 29, 2020
 *      Author: George Ayman
 */

#ifndef SEG_INT_H_
#define SEG_INT_H_

#define Cathod 		1
#define Anode		2

#ifndef SEV_SEG_TYPE
#define SEV_SEG_TYPE 	Anode
#endif

#if SEV_SEG_TYPE == Anode
#define zero    0b11000000
#define one 	0b11111001
#define two	    0b10100100
#define three   0b10110000
#define four 	0b10011001
#define five 	0b10010010
#define six		0b10000010
#define seven 	0b11111000
#define eight 	0b10000000
#define nine 	0b10010000

#elif SEV_SEG_TYPE == Cathod
#define zero    0b00111111
#define one 	0b00000110
#define two	    0b01011011
#define three   0b01001111
#define four 	0b01100110
#define five 	0b01101101
#define six		0b01111101
#define seven 	0b00000111
#define eight 	0b01111111
#define nine 	0b01101111
#endif

void  SEG_VoidPrint(u8 Copy_u8Port , u8 Copy_u8Number);
#endif /* 7SEG_INT_H_ */
