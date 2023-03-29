#pragma once
#include <linked_list.h>

namespace ssuds
{
	// This one uses a "has-a" relationship
	template <class T>
	class Queue
	{
	protected:
		LinkedList<T> mIntenalList;
	public:
		void enqueue(const T& val)
		{
			mIntenalList.append(val);
		}
		void dequeue()
		{
			if (mIntenalList.mSize == 0)
			{
				throw std::out_of_range("The queue is empty");
			}
			this->head();
			mIntenalList.removeByIndex(0);
		}
		T head()
		{
			return mIntenalList.mStart;
		}
		void clear()
		{
			mIntenalList.clear();
		}
		int empty()
		{
			if (mIntenalList.mSize == 0) { return 1; }
			else { return 0; }
		}

		///typename linkedlist<T>::linkedListiterator
	
	};
}
