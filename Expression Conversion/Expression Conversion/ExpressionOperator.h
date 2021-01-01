#pragma once
class ExpressionOperator
{
	public:
		char operator_char;
		int precedence = 0; //2 is for multiplication and division, 1 is for addition and subtraction, 3 for exponent
	
		ExpressionOperator(char character)
		{
			operator_char = character;
	
			switch (operator_char)
			{
			case '^':
				precedence = 3;
				break;
			case '+':
				precedence = 1;
				break;
			case '/':
				precedence = 2;
				break;
			case '-':
				precedence = 1;
				break;
			case '*':
				precedence = 2;
				break;
			default:
				precedence = -1;
				break;
				//default to lower precedence if it doesn't know what this is. ideally it should reject the expression but that should be parsed earlier.
			}
		}
	
		bool operator>(const ExpressionOperator& operator_) const
		{
			return (precedence > operator_.precedence);
		}
	
		bool operator>=(const ExpressionOperator& operator_) const
		{
			return (precedence >= operator_.precedence);
		}
	
		bool operator<=(const ExpressionOperator& operator_) const
		{
			return (precedence <= operator_.precedence);
		}
	
		bool operator<(const ExpressionOperator& operator_) const
		{
			return (precedence < operator_.precedence);
		}
	
};

