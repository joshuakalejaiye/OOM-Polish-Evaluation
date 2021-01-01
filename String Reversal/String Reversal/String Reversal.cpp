
#include <iostream>
#include "Stack.h"


int main()
{
	std::cout << "Please enter a string to reverse: ";
	std::string word;
	std::string last_letter;
	char character;

	do
	{
		if (word.length() > 13)
			std::cout << "Please enter a string that is 13 characters or shorter: ";

		std::cin >> word;
		std::cout << std::endl;

	} while (word.length() > 13);

	std::unique_ptr<Stack<char>> stack = std::make_unique<Stack<char>>(word.length());

	for (auto i : word)
	{
		stack->push(i);
	}

	last_letter = stack->peek();

	std::cout << "Reversed word: ";
	for (auto i : word)
	{
		if (0 == stack->get_top())
		{
			std::cout << stack->peek();
			last_letter = stack->popWithVal();
		}
		else
		{
			std::cout << stack->peek();
			stack->pop();
		}

	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Return the first letter of the input word? (Y/N): " << std::endl;
	std::cin >> character;
	std::cout << std::endl;


	if (character == 'Y')
		std::cout << "First letter of input word is: " << last_letter;
	std::cout << std::endl;

	return 0;
};

