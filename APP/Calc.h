/*
 * Calc.h
 *
 *  Created on: Sep 22, 2021
 *      Author: ibrahim
 */

#ifndef APP_CALC_H_
#define APP_CALC_H_

u8 StringTOValues(u8 * Copy_u8String ,  u16 * Copy_u32Expression);
void Array_voidClear(void * Copy_vidptrArray , u8 Copy_u8ArrayLength , u8 Copy_u8Type);

#define Uint16  	1
#define Uint8 		0
#endif /* APP_CALC_H_ */
