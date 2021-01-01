#include "ExpressionManager.h"


int main()
{
	std::string expression;
	std::string last_letter;

	do
	{
		std::cout << "Please enter a valid expression you would like to convert: ";
		std::getline(std::cin, expression);
		std::cout << std::endl;
	} while (expression.length() == 0);

	std::unique_ptr<ExpressionManager> mgr = std::make_unique<ExpressionManager>(expression);
	std::cout << mgr->GetExprType() << "\n";
	std::cout << "Infix: " << mgr->GetInfix() << "\n";
	std::cout << "Prefix: " << mgr->GetPrefix() << "\n";
	std::cout << "Postfix: " << mgr->GetPostfix() << "\n";
	std::cout << "The result of this expression is this: " << mgr->Solve() << "\n";

	return 0;
};
