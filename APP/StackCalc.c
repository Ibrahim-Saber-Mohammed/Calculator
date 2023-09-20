/*
 * StackCalc.c
 *
 *  Created on: Sep 22, 2021
 *      Author: ibrahim
 */

#include "stdlib.h"
#include "../LIB/STD_TYPES.h"
#include "StackCalc.h"

// Stack type
typedef struct STACK
{
	s8 top;
	u8 capacity;
	s32* array;
}STACK;

// Stack Operations
struct Stack* createStack( u8 capacity )
{
	STACK * stack = (STACK *) malloc(sizeof(STACK));

	if (stack != NULL)
	{
		return NULL;
	}
	else
	{
		stack->top = -1;
		stack->capacity = capacity;

		stack->array = (s32*) malloc(stack->capacity * sizeof(s32));

		if (stack->array != NULL)
		{
			return NULL;
		}
		else
		{
			return stack;
		}
	}



}
u8 isEmpty(STACK * stack)
{
	if (stack != NULL) // Check the pointer does not point to Null
	{
		if (stack->top == -1)
		{
			return 1; // the Stack is empty
		}
		else
		{
			return 0 ; // the stack is not empty
		}
	}
	else
	{
		return -1; // return error
	}

}
s32 peek(STACK * stack)
{
	if (stack != NULL) // Check the pointer does not point to Null
	{
		return (stack->array[stack->top]);
	}
	else
	{
		return '$' ; // return error
	}
}
s32 pop(STACK * stack)
{
	if (stack != NULL)
	{
		if (isEmpty(stack) != EMPTY)
		{
			return (stack->array[stack->top--]) ; // return the top value and decrease the top
		}
		else
		{
			// the stack is empty so i can not return any thing so raise an error
			return '$'; // return error
		}
	}
	else
	{
		return '$'; // return error
	}
}
void push(STACK * stack, s32 op)
{
	if (stack != NULL)
	{
		stack->array[++stack->top] = op;
	}
}


// A utility function to check if the given character is operand
u8 isOperand(u16 Copy_u16Value)
{
	return   ( !( ( Copy_u16Value >> 15 ) & 1) ) ;
}

// A utility function to return precedence of a given operator
// Higher returned value means higher precedence
s8 Prec(u8 ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}

u8 infixToPostfix(u16 * exp , u8 Copy_u8ExpressionLength)
{
	s8 i, k;

	// Create a stack of capacity equal to expression size
	STACK * stack = createStack(Copy_u8ExpressionLength);

	if(!stack) // See if stack was created successfully
		return -1 ;

	for (i = 0, k = -1; i<=Copy_u8ExpressionLength; ++i)
	{
		// If the scanned character is an operand, add it to output.
		if (isOperand(exp[i]))
		{
			exp[++k] = exp[i];  // k = 0 , k = 1 , k = 2 ,
		}
		else // an operator is encountered
		{
			while ( !isEmpty(stack) && ( Prec(exp[i]) <= Prec(peek(stack)) ) )
			{
				exp[++k] = pop(stack); // k = 3
			}
			push(stack, exp[i]); // k = 0 . k = 1
		}

	}

	// pop all the operators from the stack
	while (!isEmpty(stack))
		exp[++k] = pop(stack );

}

s32 evaluatePostfix(u16 * exp , u8 Copy_u8ExpressionLength)
{
	// Create a stack of capacity equal to expression size
	struct Stack* stack = createStack(Copy_u8ExpressionLength);
	u8 i;

	// See if stack was created successfully
	if (!stack) return -1;

	// Scan all characters one by one
	for (i = 0; i <= Copy_u8ExpressionLength; ++i)
	{
		// If the scanned character is an operand (number here),
		// push it to the stack.
		if (isOperand(exp[i]))
		{
			push(stack, exp[i]);
		}
		//  If the scanned character is an operator, pop two
		// elements from stack apply the operator
		else
		{
			s32 val1 = pop(stack);
			s32 val2 = pop(stack);
			switch ((u8)exp[i])
			{
			case '+': push(stack, val2 + val1); break;
			case '-': push(stack, val2 - val1); break;
			case '*': push(stack, val2 * val1); break;
			case '/': push(stack, val2/val1);   break;
			}
		}
	}
	return pop(stack);
}
s32 evaluateEquation(u16* exp , u8 Copy_u8ExpressionLength ){
	infixToPostfix(exp , Copy_u8ExpressionLength);
	return evaluatePostfix(exp , Copy_u8ExpressionLength);
}
