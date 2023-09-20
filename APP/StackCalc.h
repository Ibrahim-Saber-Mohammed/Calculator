/*
 * StackCalc.h
 *
 *  Created on: Sep 22, 2021
 *      Author: ibrahim
 */

#ifndef APP_STACKCALC_H_
#define APP_STACKCALC_H_

#define EMPTY 1
#define NOT_EMPTY 0

u8 infixToPostfix(u16 * exp, u8 Copy_u8ExpressionLength);
s32 evaluateEquation(u16 *exp , u8 Copy_u8ExpressionLength);


#endif /* APP_STACKCALC_H_ */
