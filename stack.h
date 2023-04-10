#pragma once
#include <linked_list.h>

namespace ssuds
{
	
	template <class T>
	/// <summary>
	/// Stack class using an inherited Linked List of T type
	/// </summary>
	class Stack : private LinkedList<T>
	{
	public:

		/// <summary>
		/// Adds or pushes an item, of type T, into the stack
		/// </summary>
		void push(const T& val)
		{
			this->prepend(val);
		}

		/// <summary>
		/// Removes or pops an item, of type T, out of the stack
		/// </summary>
		void pop()
		{
			if (this->mSize == 0)
			{
				throw std::out_of_range("The stack is empty");
			}
			//std::cout << this->top() << std::endl;
			this->removeByIndex(0);
		}

		/// <summary>
		/// Gets the top value of Type T off the stack
		/// </summary>
		T top()
		{
			return this->mStart->mData;
		}
		
		/// <summary>
		/// helper clear all function from linked list, clears out the stack
		/// </summary>
		using LinkedList<T>::clearall;
		
		/// <summary>
		/// a true or false check if the stack is empty
		/// </summary>
		int empty()
		{
			if (this->mSize == 0) { return 1; }
			else { return 0; }
		}


		/// <summary>
		/// a os stream function to print out the stack to the stream
		/// </summary>
		friend std::ostream& operator <<(std::ostream& os, const Stack<T>& S)
		{
			os << dynamic_cast<const LinkedList<T>&>(S);
			return os;
		}

		/// <summary>
		/// A inherited linked list iterator of type T
		/// </summary>
		using LinkedList<T>::LinkedListIterator;

		/// <summary>
		/// The linked list iterator to the end value of type T
		/// </summary>
		using LinkedList<T>::end;

		/// <summary>
		/// the linked list iterator to the beginning value of type T
		/// </summary>
		using LinkedList<T>::begin;
		
	};
}