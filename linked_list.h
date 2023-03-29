#pragma once
#include<string>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <initializer_list>

/// <summary>
/// namespace of ssuds for shawnee state university data structures
/// </summary>
namespace ssuds
{

	template <class T>
	/// <summary>
	/// LinkedList of Nodes terminating in a nullptr pointer before the first and after the final item
	/// </summary>
	class LinkedList
	{
	protected:
		/// <summary>
		/// nested class node to create nodes of T types of data
		/// </summary>
		class Node
		{
		public:
			/// <summary>
			/// The data being stored in the node of type T
			/// </summary>
			T mData;

			/// <summary>
			/// A pointer to the next item in the list, nullptr if there is none
			/// </summary>
			Node* mNext;

			/// <summary>
			/// a pointer to the preceding object in the list, can be a nullptr if there is none
			/// </summary>
			Node* mPrev;

			/// <summary>
			/// constructor for the node class taking a value 
			/// </summary>
			/// <param name="val"></param> a value of type T
			Node(T val) : mData(val), mNext(nullptr), mPrev(nullptr) {};
		};

		/// <summary>
		/// a pointer to the first node in the linked list, the head
		/// </summary>
		Node* mStart;

		/// <summary>
		/// a pointer to the ending node in the linked list, the tail
		/// </summary>
		Node* mEnd;

		/// <summary>
		/// an int size of the linked list, This counts number of nodes.
		/// </summary>
		int mSize;

	public:

		/// <summary>
		/// a nested iterator for the Linked List class
		/// </summary>
		class LinkedListIterator
		{
		protected:
			/// <summary>
			/// the interger position, Index of data, for the iterator
			/// </summary>
			int mPosition;
			/// <summary>
			/// a node pointer to feed in a node of datas location to the iterator
			/// </summary>
			Node* mNode;


		public:
			/// <summary>
			/// the constructor for the iterator class
			/// </summary>
			/// <param name="sNode"></param> a node pointer 
			/// <param name="start_index"></param> the index you want to be at in the linked list
			LinkedListIterator(Node* sNode, int start_index) : mPosition(start_index), mNode(sNode)
			{

			}

			/// <summary>
			/// opperator to determin equality of two iterators
			/// </summary>
			/// <param name="other"></param> the other iterator
			/// <returns></returns> true or false
			bool operator==(const LinkedListIterator& other) const
			{
				return mNode == other.mNode && mPosition == other.mPosition;
			}

			/// <summary>
			/// opperator to determin inequality of two iterators
			/// </summary>
			/// <param name="other"></param> the other iterator
			/// <returns></returns> true or false
			bool operator!=(const LinkedListIterator& other) const
			{
				return mNode != other.mNode;
			}

			/// <summary>
			/// incriment operator overload for the iterator class
			/// </summary>
			void operator++()
			{
				mNode = mNode->mNext;
				++mPosition;
			}

			/// <summary>
			/// decriment operator overload for the iterator class
			/// </summary>
			void operator--()
			{
				mNode = mNode->mPrev;
				--mPosition;
			}

			/// <summary>
			/// reference operator for the iterator class
			/// </summary>
			/// <returns></returns> the data of type T at that iterator location
			T& operator*() const
			{
				return mNode->mData;
			}

			/// <summary>
			/// index function to get the interger value of the iterators position
			/// </summary>
			/// <returns></returns> the position as an int
			friend int index()
			{
				return mPosition;
			}
			/// <summary>
			/// makes the linked list a friend class to access data and functions
			/// </summary>
			friend class LinkedList;
		};
		/// <summary>
		/// Default constructor with 0 size and pointing at 2 nullptrptrs
		/// </summary>
		LinkedList() : mSize(0), mStart(nullptr), mEnd(nullptr)
		{
			//empty
		};

		/// <summary>
		/// a copy constructor for Linked lists
		/// </summary>
		LinkedList(const LinkedList& other)  
		{
			mSize = 0;
			mStart = mEnd = nullptr;
			Node* curNode = other.mStart;
			while (mSize != other.mSize)
			{
				this->append(curNode->mData);
				curNode = curNode->mNext;
			}
		}

		/// <summary>
		/// A move constructor for the linked list class
		/// </summary>
		/// <param name="other"></param> a reference to another linked list
		LinkedList(LinkedList&& other) : mSize(other.mSize)
		{
			other.mSize = 0;
			mStart = other.mStart;
			other.mStart = nullptr;
			other.mEnd = other.mEnd;
			other.mEnd = nullptr;
		}

		/// <summary>
		/// Destructor for the linked list, destroys every node down the chain
		/// </summary>
		~LinkedList()
		{

			Node* tmp = nullptr;
			while (mStart != nullptr)
			{
				tmp = mStart;
				mStart = mStart->mNext;
				delete tmp;
			}
			mStart = nullptr;
			mSize = 0;

		}

		/// <summary>
		/// function to append a new value to the linked list
		/// </summary>
		/// <param name="new_val"></param> a new value of type T
		void append(const T& new_val)
		{

			Node* node = new Node(new_val);
			if (mStart == nullptr)
			{
				mStart = node;
				mEnd = node;
			}
			else
			{
				node->mPrev = mEnd;
				mEnd->mNext = node;
				mEnd = node;
			}
			mSize++;
		}

		/// <summary>
		/// function to append a value to the front of a linked list
		/// </summary>
		/// <param name="new_val"></param> a new value of type T 
		void prepend(T new_val)
		{
			Node* node = new Node(new_val);
			if (mStart == nullptr)
			{
				mStart = node;
				mEnd = node;
			}

			else
			{
				Node* oldNode = mStart;
				node->mNext = oldNode;
				oldNode->mPrev = node;
				mStart = node;
			}
			mSize++;
		}

		/// <summary>
		/// method to insert a node of data into the linked list at a given point
		/// </summary>
		/// <param name="new_val"></param> a value of type T to put into the linked list
		/// <param name="index"></param> a valid index to insert the value at
		void insert(T new_val, int index)
		{
			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			if (index == 0 || mSize == 0)
			{
				prepend(new_val);
			}

			else if (index == mSize)
			{
				append(new_val);
			}

			else
			{
				Node* node = new Node(new_val);
				Node* curNode = mStart;
				int pos = 0;
				while (pos != index && curNode != nullptr)
				{
					curNode = curNode->mNext;
					pos++;
				}

				node->mNext = curNode;
				node->mPrev = curNode->mPrev;

				curNode->mPrev->mNext = node;
				curNode->mPrev = node;
				mSize++;
			}

		}

		/// <summary>
		/// getter for the linked list's mData at a certain index. 
		/// </summary>
		/// <param name="index"></param> the index of mData you want to view
		/// <returns></returns> the data at that index
		T& operator[](int index) const
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			int count = 0;
			Node* temp = mStart;
			while (count != index) {
				temp = temp->mNext;
				count++;
			}
			return temp->mData;
		}

		/// <summary>
		/// a friend function to output a formatted version of all the data in the linked list
		/// </summary>
		/// <param name="os"></param> the output to the system
		/// <param name="Llist"></param> a linked list
		/// <returns></returns> formatted version of the list's data
		friend std::ostream& operator <<(std::ostream& os, const LinkedList<T>& Llist)
		{
			os << "[";
			const Node* cur_node = Llist.mStart;
			for (int i = 0; i < Llist.size(); i++)
			{
				os << cur_node->mData;
				cur_node = cur_node->mNext;
				if (i < Llist.size() - 1)
					os << ", ";
			}
			os << "]";
			return os;
		}

		/// <summary>
		/// Gets the size of the list
		/// </summary>
		/// <returns></returns> the size of the list as an int
		int size() const
		{
			return mSize;
		}

		/// <summary>
		/// A helper remove  by index function for arrays and queues
		/// </summary>
		/// <param name="index"></param> the index you want to remove
		/// <returns></returns> the value you remove
		T removeByIndex(int index)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			Node* cur_node = mStart;
			int counter = 0;
			if (mSize == 1)
			{
				T result = cur_node->mData;
				delete cur_node;
				mStart = nullptr;
				mEnd = nullptr;
				mSize--;
				return result;
			}
			if (index == 0)
			{
				mStart = cur_node->mNext;
				T result = cur_node->mData;
				delete cur_node;
				mSize--;
				return result;
			}
			if (index == mSize - 1)
			{
				while (counter != mSize - 1)
				{
					cur_node = cur_node->mNext;
					counter++;
				}
				cur_node->mPrev->mNext = nullptr;
				mEnd = cur_node->mPrev;
				T result = cur_node->mData;
				delete cur_node;
				mSize--;
				return result;
			}
			while (counter != index)
			{
				cur_node = cur_node->mNext;
				counter++;
			}
			T result = cur_node->mData;
			cur_node->mNext->mPrev = cur_node->mPrev;
			cur_node->mPrev->mNext = cur_node->mNext;
			delete cur_node;
			mSize--;
			return result;

		}
		

		/// <summary>
		/// a function to find a vallue in a linked list returning an iterator pointing to that nodes location
		/// </summary>
		/// <param name="value"></param> the value of Type T you want to find
		/// <returns></returns> an iterator to the first location of the value or the end iterator
		LinkedListIterator find(const T value) const
		{
			Node* cur_node = mStart;
			int counter = 0;
			while (cur_node != nullptr)
			{
				if (cur_node->mData == value)
				{
					return LinkedListIterator(cur_node, counter);
				}
				cur_node = cur_node->mNext;
				counter++;
			}

			return this->end();
		}

		/// <summary>
		/// a function to remove a value from the linked list
		/// </summary>
		/// <param name="position"></param> a linked list iterator at the position of the value you wish  to remove
		/// <returns></returns> an iterator at the next, now current value.
		LinkedListIterator remove(LinkedListIterator position)
		{
			if (mSize == 1)
			{
				mStart = nullptr;
				mEnd = nullptr;
				mSize--;
				return LinkedListIterator(mStart, 0);
			}

			int tempPos = position.mPosition;
			Node* tempNode = position.mNode->mNext;

			if (position.mNode == mEnd)
			{
				mEnd = position.mNode->mPrev;
				position.mNode->mPrev->mNext = nullptr;
				mSize--;
				return this->end();
			}
			if (position.mNode == mStart)
			{
				mStart = position.mNode->mNext;
			}
			if (position.mNode->mNext != nullptr)
			{
				position.mNode->mNext->mPrev = position.mNode->mPrev;
			}
			if (position.mNode->mPrev != nullptr)
			{
				position.mNode->mPrev->mNext = position.mNode->mNext;
			}
			delete position.mNode;
			mSize--;
			return LinkedListIterator(tempNode, tempPos);

		}

		/// <summary>
		/// begin function for a linked list iterator
		/// </summary>
		/// <returns></returns> a linked list iterator at the begining of the list
		LinkedListIterator begin() const
		{
			return LinkedListIterator(mStart, 0);
		}

		/// <summary>
		/// end function for a linked list iterator
		/// </summary>
		/// <returns></returns> a linked list iterator at the end of the list
		LinkedListIterator end() const
		{
			return LinkedListIterator(nullptr, mSize);
		}

		/// <summary>
		/// Linked list = operator, overloads the operator
		/// </summary>
		/// <param name="other"></param> the other array list you want to copy
		/// <returns></returns> a copied linked list
		LinkedList<T>& operator= (const LinkedList<T>& other)
		{
			if (mStart != nullptr)
			{
				clearall();
			}
			if (other.mStart == nullptr)
			{
				clearall();
				return *this;
			}
			else
			{
				Node* curNode = other.mStart;
				while (mSize != other.mSize)
				{
					this->append(curNode->mData);
					curNode = curNode->mNext;
				}
			}
			return *this;
		}
		/// <summary>
		/// a clear helper function for the linked list class, works like destructor but keeps the list
		/// </summary>
		/// <returns></returns> an empty list
		LinkedList<T> clearall()
		{
			if (mStart == nullptr && mEnd == nullptr && mSize ==0)
			{
				return *this;
			}
			Node* curNode = mStart;
			Node* nextNode = nullptr;
			while (curNode != nullptr) {
				nextNode = curNode->mNext;
				delete(curNode);
				curNode = nextNode;

			}
			mStart = nullptr;
			mEnd = nullptr;
			mSize = 0;
			return *this;
		}


		
		
		/// <summary>
		/// an initializer list constructor for the linked list clast
		/// </summary>
		/// <param name="ilist"></param> a list of T values to be put into that list
		LinkedList(std::initializer_list<T> ilist) 
		{
			mSize = 0;
			mStart = mEnd = nullptr;
			for (T val : ilist)
				append(val);
		}

		
	};

}