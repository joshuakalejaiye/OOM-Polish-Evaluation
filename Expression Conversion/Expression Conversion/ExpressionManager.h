#pragma once
#include <stack>
#include "Stack.h"
#include "ExpressionOperator.h"

class ExpressionManager
{
	public:
		ExpressionManager(std::string expression);

		std::string GetPostfix();
		std::string GetPrefix();
		std::string GetInfix();
		std::string GetExprType();
		int Solve();

	private:
		std::string expression_;
	
		bool in = false;
		bool post = false;
		bool pre = false;
	
		static bool is_operand(char character);
		static bool is_operator(char character);
		static std::string no_whitespace(std::string str);
		std::string infix_to_postfix(std::string infix);
		std::string string_reversal(std::string str);
		std::string infix_to_prefix(std::string infix);
		int execute_operation(int a, int b, char operator_char);
		int Evaluate(const std::string& expression);
	
};

