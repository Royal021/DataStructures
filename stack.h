#pragma once
#include <linked_list.h>

namespace ssuds
{
	// Use an "is-a" (inheritance) relationship with LList
	template <class T>
	class Stack : private LinkedList<T>
	{
		// Probably no attributes at all, only methods!
	public:
		void push(const T& val)
		{
			// Note: the "this" is required here (b/c
			// of the type-dependency issue)
			this->prepend(val);
		}
		void pop()
		{
			if (this->mSize == 0)
			{
				throw std::out_of_range("The stack is empty");
			}
			std::cout << this->top() << std::endl;
			this->removeByIndex(0);
		}
		T top()
		{
			return this->mStart->mData;
		}
		
		using LinkedList<T>::clearall;
		
		int empty()
		{
			if (this->mSize == 0) { return 1; }
			else { return 0; }
		}

		friend std::ostream& operator <<(std::ostream& os, const Stack<T>& S)
		{
			os << dynamic_cast<const LinkedList<T>&>(S);
			return os;
		}

		using LinkedList<T>::LinkedListIterator;
		using LinkedList<T>::end;
		using LinkedList<T>::begin;
		
	};
}