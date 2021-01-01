#include "ExpressionManager.h"



ExpressionManager::ExpressionManager(std::string expression)
{
	expression_ = no_whitespace(expression);
	
	if (is_operator(*(expression.end() - 1))) //if the last char is an operator, this is postfix
	{
		post = true;
	}
	else if (is_operator(*(expression.begin()))) //if the first char is an operator, this is prefix
	{
		pre = true;
	}
	else //if neither it is infix
	{
		in = true;
	}

}


std::string ExpressionManager::GetPrefix()
{
	if (pre) return expression_;
	if (post) return "...";
	return infix_to_prefix(expression_);
}

std::string ExpressionManager::GetPostfix()
{
	if (pre) return "...";
	if (post) return expression_;
	return infix_to_postfix(expression_);
}

std::string ExpressionManager::GetInfix()
{
	if (pre) return "...";
	if (post) return "...";
	return expression_;
}

std::string ExpressionManager::GetExprType()
{
	std::string str = "Expression Type: ";
	if (post) return str + "Postfix";
	if (pre) return str + "Prefix";
	return str + "Infix";
}

int ExpressionManager::Solve()
{
	if (in) return Evaluate(infix_to_postfix(expression_));
	if (post) return Evaluate(expression_);
	if (pre) return Evaluate(expression_);
	return 0;
}


std::string ExpressionManager::infix_to_postfix(std::string infix)
{
	// declaring string to store resulting expression
	std::string postfix;

	// create empty stack  
	std::unique_ptr<Stack<char>> operator_stack = std::make_unique<Stack<char>>(3); //four characters + three operands

	for (int i = 0; i < infix.size(); ++i)
	{
		char character = infix[i];
		ExpressionOperator operator1(character);

		// If the scanned character is an  
		// operand, add it to output.  
		if (is_operand(character) && character != '(' && character != ')')
		{
			postfix += character;
		}
		else if (character == '(')	// If the character is an '(', // push it to the stack.  			{
		{
			operator_stack->push(character);
		}
		else if (character == ')')	//  If the scanned character is an ')',  // pop and output from the stack   // until an '(' is encountered.  
		{
			while (!operator_stack->isEmpty() && operator_stack->peek() != '(')
			{
				postfix += operator_stack->peek();
				operator_stack->pop();
			}

			if (!operator_stack->isEmpty() && operator_stack->peek() != '(')
			{
				return "Expression is invalid";
			}
			else
			{
				operator_stack->pop();
			}

		}
		else // an operator is encountered 
		{
			ExpressionOperator operator2(operator_stack->peek());

			while (!operator_stack->isEmpty() && operator1 <= operator2)
			{
				postfix += operator_stack->peek();
				operator_stack->pop();
			}
			operator_stack->push(character);
		}

	}

	// pop all the operators from the stack  
	while (!operator_stack->isEmpty())
	{
		postfix += operator_stack->peek();
		operator_stack->pop();
	}

	return postfix;
};

std::string ExpressionManager::string_reversal(std::string str)
{
	std::unique_ptr<Stack<char>> stack = std::make_unique<Stack<char>>(str.length());

	// Reverse String
	for (auto i : str)
	{
		stack->push(i);
	}

	int length = str.length();
	str = "";

	for (int i = 0; i < length; i++)
	{
		str += stack->peek();
		stack->pop();
	}

	return str;
}

std::string ExpressionManager::infix_to_prefix(std::string infix)
{

	// Reverse infix 
	infix = string_reversal(infix);

	// Replace ( with ) and vice versa 
	for (int i = 0; i < infix.size(); i++) {

		if (infix[i] == '(') {
			infix[i] = ')';
			i++;
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
			i++;
		}
	}

	//return reversed postfix
	return (string_reversal(infix_to_postfix(infix)));
}

int ExpressionManager::execute_operation(int a, int b, char operator_char)
{
	int result;

	switch (operator_char)
	{
	case '^':
		result = b ^ a;
		break;
	case '+':
		result = b + a;
		break;
	case '/':
		result = b / a;
		break;
	case '-':
		result = b - a;
		break;
	case '*':
		result = b * a;
		break;
	default:
		result = INT_MIN;
		break;
	}

	return result;
}

int ExpressionManager::Evaluate(const std::string& expression)
{
	std::unique_ptr<Stack<int>> stack = std::make_unique<Stack<int>>(expression.length());

	if (is_operator(expression[0])) //prefix
	{
		for (auto it = expression.rbegin(); it != expression.rend(); ++it)
		{
			if (is_operand(*it)) {
				stack->push(int{ *it } - 48);
			}
			else if (is_operator(*it))
			{
				int b = stack->peek();
				stack->pop();

				int a = stack->peek();
				stack->pop();

				stack->push(execute_operation(a, b, *it));
			}
		}
	}
	else
	{
		for (auto it = expression.begin(); it != expression.end(); ++it)
		{
			if (is_operand(*it)) {
				stack->push(int{ *it } - 48);
			}
			else if (is_operator(*it))
			{
				int a = stack->peek();
				stack->pop();

				int b = stack->peek();
				stack->pop();

				stack->push(execute_operation(a, b, *it));
			}
		}
	}

	return stack->peek();
}

std::string ExpressionManager::no_whitespace(std::string str)
{
	std::string cleaned;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ') continue;
		cleaned += str[i];
	}

	return cleaned;

}

bool ExpressionManager::is_operand(char character)
{
	if (character >= '0' && character <= '9')
		return true;
	return false;
}

bool ExpressionManager::is_operator(char character)
{
	return ((character == '-' || character == '+' || character == '*' || character == '/' || character == '^')); //if it is not a legal operator, it is operand
}