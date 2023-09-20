/*
 * main.c
 *
 *  Created on: Sep 21, 2021
 *      Author: ibrahim
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/GPIO_interface.h"
#include "../HAL/LCD/CLCD_interface.h"
#include "../HAL/KeyPad/KEYPAD_interface.h"
#include "Calc.h"
#include "StackCalc.h"
#include "util/delay.h"

#define OPERATION			1
#define NUMBER				0

int main (void)
{
	u8 Local_u8LCD_CurrentPosition = CLCD_COL1; //start Displaying from the start of the LCD
	u8 Local_u8ArrayCurrentIndex = 0; // Start adding characters from the first index in the array
	u8 Local_u8ArrayEnteredvalues[100] = {0}; // an array to save the characters
	u8 Local_u8KepadPressed = NOT_PRESSED; // variable to take the input of the keypad
	u8 Local_u8LastVal = NUMBER; // variable indicates that the last entered character either an operation or number

	u16 Local_u16ExpressionArray[20] = {0};

	CLCD_voidInit(); // initialize the LCD
	KEYPAD_voidInit(); // initialize the Keypad
	CLCD_voidClearScreen(); // Clear the LCD
	while(1)
	{
		Local_u8KepadPressed = NOT_PRESSED;

		if(Local_u8LCD_CurrentPosition >= CLCD_COL16)
		{
			CLCD_voidSendCommand(CLCD_SHIFT_LEFT);
		}
		else
		{
			CLCD_voidGoToX_Y(CLCD_ROW1 , Local_u8LCD_CurrentPosition);
		}

		do{
			Local_u8KepadPressed = KEYPAD_voidGetPressedButton();
		}while(Local_u8KepadPressed == NOT_PRESSED);

		if( Local_u8KepadPressed == '=' )
		{
			CLCD_voidSendCharacter(Local_u8KepadPressed);
			u8 Local_u8ExpressionLength = StringTOValues ( Local_u8ArrayEnteredvalues , Local_u16ExpressionArray );

			s32 Local_u32Result = evaluateEquation( Local_u16ExpressionArray , Local_u8ExpressionLength);

			if( Local_u32Result < 0 )
			{
				CLCD_voidSendCharacter('-');
				CLCD_voidSendNumber(Local_u32Result * -1);
			}
			else
			{
				CLCD_voidSendNumber(Local_u32Result);
			}
//			Local_u8LastVal = NUMBER;
//			Local_u8LCD_CurrentPosition = CLCD_COL1;
		}
		else if( Local_u8KepadPressed == 'C' )
		{
			CLCD_voidClearScreen();
			CLCD_voidGoToX_Y(CLCD_ROW1 , CLCD_COL1);
			Array_voidClear(Local_u8ArrayEnteredvalues , 100 , Uint8);
			Array_voidClear(Local_u16ExpressionArray , 20 , Uint16);
			Local_u8ArrayCurrentIndex = 0;
			Local_u8LCD_CurrentPosition = CLCD_COL1;
			CLCD_voidSendCommand(CLCD_SHIFT_DISABEL);
			Local_u8LastVal = NUMBER;
		}
		else // user Entered either operation or Number
		{
			// In case the user Entered any operation
			if( (Local_u8KepadPressed == '+' ) || ( Local_u8KepadPressed == '-' ) ||
					(Local_u8KepadPressed == '*' ) || ( Local_u8KepadPressed == '/') )
			{
				/* if the last input from the user was an operation too then
				 * 1. should back one position on LCD and decrement the index of the array by one
				 * 2. Display the new operation and save it
				 * 3. Increment the LCD position for the next input and increment the array index for the new value
				 * 4. Save the lastVal as operation*/

				if( Local_u8LastVal == OPERATION )
				{
					Local_u8LCD_CurrentPosition -= 1 ;
					Local_u8ArrayCurrentIndex -=1 ;
					Local_u8ArrayEnteredvalues[Local_u8ArrayCurrentIndex] = Local_u8KepadPressed;
					CLCD_voidGoToX_Y(CLCD_ROW1 , Local_u8LCD_CurrentPosition);
					CLCD_voidSendCharacter(Local_u8KepadPressed);
					Local_u8LCD_CurrentPosition +=1;
					Local_u8ArrayCurrentIndex += 1;
					Local_u8LastVal = OPERATION;

				}
				else
				{
					/* User Entered an operation but the last value was a number
					 * 1. Display the Entered value
					 * 2. Save the value into the array
					 * 3. Increment the LCD position and array index for the next value
					 * 4. Save the Last Entered value as operation
					 * */
					CLCD_voidSendCharacter(Local_u8KepadPressed);
					Local_u8ArrayEnteredvalues[Local_u8ArrayCurrentIndex] = Local_u8KepadPressed;
					Local_u8LCD_CurrentPosition +=1 ;
					Local_u8ArrayCurrentIndex += 1;
					Local_u8LastVal = OPERATION;
				}
			}
			else
			{
				/* User Entered a number
				 * 1. Display the Entered value
				 * 2. Save the value into the array
				 * 3. Increment the LCD position and array index for the next value
				 * 4. Save the Last Entered value as operation
				 * */
				CLCD_voidSendCharacter(Local_u8KepadPressed);
				Local_u8ArrayEnteredvalues[Local_u8ArrayCurrentIndex] = Local_u8KepadPressed;
				Local_u8LCD_CurrentPosition +=1 ;
				Local_u8ArrayCurrentIndex += 1;
				Local_u8LastVal = NUMBER;
			}

		}
	}


	return 0;
}
