#pragma once
#include <linked_list.h>

namespace ssuds
{
	template <class T>
	/// <summary>
	/// A Queue class with a has-a relationship with Linked list.
	/// </summary>
	class Queue
	{
	protected:
		/// <summary>
		/// the LinkedList that the Queue will be stored in
		/// </summary>
		LinkedList<T> mInternalList;
		
	public:

		/// <summary>
		/// an append to the end of the queue
		/// </summary>
		/// <param name="val"></param> a value of type T
		void enqueue(const T& val)
		{
			mInternalList.append(val);
		}
		/// <summary>
		/// a removal of the 'head' value of the queue
		/// </summary>
		void dequeue()
		{
			if (mInternalList.size() == 0)
			{
				throw std::out_of_range("The queue is empty");
			}
			this->head();
			mInternalList.removeByIndex(0);
		}

		/// <summary>
		/// A getter for the head value of the Queue
		/// </summary>
		/// <returns></returns> a value of type T
		T head()
		{
			return mInternalList[0];
		}

		/// <summary>
		/// A utility clear funtion for the queue, uses the linked list clear
		/// </summary>
		void clear()
		{
			mInternalList.clearall();
		}

		/// <summary>
		/// a true or false function to check if the queue is empty
		/// </summary>
		/// <returns></returns> 1 if the queue is empty, 0 if not
		int empty()
		{
			if (mInternalList.size() == 0) { return 1; }
			else { return 0; }
		}

		/// <summary>
		/// overload for the stream operator
		/// </summary>
		/// <param name="os"></param>  the os stream
		/// <param name="Q"></param>  the queue
		/// <returns></returns> the queue to the os stream
		friend std::ostream& operator <<(std::ostream& os, const Queue<T>& Q)
		{
			os << Q.mInternalList;
			return os;
		}

		/// <summary>
		/// a linked list iterator for queue class, points to the beginning of the queue
		/// </summary>
		/// <returns></returns> an iterator pointing to the start of the queue
		typename LinkedList<T>::LinkedListIterator begin()
		{
			return mInternalList.begin();
		}
		
		/// <summary>
		/// a linked list iterator for queue class, points to the end of the queue
		/// </summary>
		/// <returns></returns> an iterator pointing to the end of the queue
		typename LinkedList<T>::LinkedListIterator end()
		{
			return mInternalList.end();
		}
	
	};
}
