#pragma once
#include <iostream>
#include <string>
#include <vector>


template <class T>
class Stack
{
	private:
		std::unique_ptr<T[]> stack_;
	
		int max_size_ = 13;
		int top_ = -1;
		
		bool isFull()
		{
			return (top_ >= max_size_ - 1);
		}
	
		int current_size() const
		{
			return sizeof(stack_) / sizeof(stack_);
		}

	
	public:
		Stack(){}

		bool isEmpty()
		{
			return (top_ == -1);
		}

		Stack(int size)
		{
			max_size_ = size;
			stack_ = std::make_unique<T[]>(max_size_);
		}
	
		bool pop()
		{
			if (!isEmpty())
			{
				//stack_[top_] = NULL
				top_--;
				return true;
			}
			return false;
		}

		int get_top()
		{
			return top_;
		}
	
		bool push(T item)
		{
			if (!isFull())
			{
				top_++;
				stack_[top_] = item;
				return true;
			}
			return false;
		}

		T peek()
		{
			return stack_[top_];
		}
};
