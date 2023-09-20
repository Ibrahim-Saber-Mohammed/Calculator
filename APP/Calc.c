/*
 * Calc.c
 *
 *  Created on: Sep 22, 2021
 *      Author: ibrahim
 */


#include "../LIB/STD_TYPES.h"
#include "Calc.h"


void Array_voidClear(void * Copy_vidptrArray , u8 Copy_u8ArrayLength , u8 Copy_u8Type)
{
	for( u8 Local_u8LoopIterator = 0; Local_u8LoopIterator <Copy_u8ArrayLength ; Local_u8LoopIterator++ )
	{
		if( Copy_u8Type == Uint8 )
		{
			*(u8*)(Copy_vidptrArray+Local_u8LoopIterator) = 0;
		}
		else if( Copy_u8Type == Uint16 )
		{
			*(u16*)(Copy_vidptrArray+Local_u8LoopIterator) = 0;
		}
	}
}


u8 StringTOValues(u8 * Copy_u8String ,  u16 * Copy_u16Expression)
{
	u8 Local_u8ArrayStringCounter = 0;
	u8 Local_u8ExpressionArrayIndexCounter = 0;
	u8 Local_u8Temp = 0;
	while( Copy_u8String[ Local_u8ArrayStringCounter ] != '\0' )
	{
		switch(Copy_u8String[ Local_u8ArrayStringCounter ])
		{
		case '+':
		case '-':
		case '*':
		case '/':	Local_u8ExpressionArrayIndexCounter++;
		Copy_u16Expression[Local_u8ExpressionArrayIndexCounter] = ( Copy_u8String[Local_u8ArrayStringCounter] | (1 << 15) );
		Local_u8ExpressionArrayIndexCounter++;
		break;
		default:
			Local_u8Temp = Copy_u8String[Local_u8ArrayStringCounter] - '0';
			Copy_u16Expression[Local_u8ExpressionArrayIndexCounter] = Copy_u16Expression[Local_u8ExpressionArrayIndexCounter]*10 + Local_u8Temp;

		}
		Local_u8ArrayStringCounter++;
	}
	return Local_u8ExpressionArrayIndexCounter;
}
