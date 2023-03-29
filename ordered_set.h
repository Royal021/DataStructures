#pragma once

namespace ssuds
{

	enum class traversalType { PRE, POST, IN };

	template <class T>
	class OrderedSet
	{
	protected:
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;

			Node(T val) : mData(val), mLeft(nullptr),
				mRight(nullptr)
			{

			}

			~Node()
			{
				if (Node)
				{
					DestroyRecursive(Node->mleft);
					DestroyRecursive(Node->mright);
					delete Node;
				}
			}

			bool insert_recursive(const T& val)
			{
				// I'm some Node in the tree.  I need
				//  to (maybe) add this value below me
				if (val < mData)
				{
					// The value is less than us.  Tell
					// our left child to handle it
					if (mLeft)
					{
						return mLeft->insert_recursive(val);
					}
					else
					{
						mLeft = new Node(val);
						return true;
					}
				}
				else if (val > mData)
				{
					// The value is greater than us.  Tell
					//  our right child to handle it
					if (mRight)
						mRight->insert_recursive(val);
					else
					{
						mRight = new Node(val);
						return true;
					}
				}
				else
				{
					// If we don't get either of these if cases,
					//   then val == mData, and it's a duplicate!
					return false;
				}
			}

			void traverseRecursivePre()
			{

				std::cout << this->mData << std::endl;
				if (this->mLeft)
				{
					this->mLeft->traverseRecursivePre();
				}
				if (this->mRight)
				{
					this->mRight->traverseRecursivePre();
				}

			}

			void traverseRecursivePost()
			{

				if (this->mLeft)
				{
					this->mLeft->traverseRecursivePost();
				}
				
				if (this->mRight)
				{
					this->mRight->traverseRecursivePost();
				}
				std::cout << this->mData << std::endl;
			}

			void traverseRecursiveOrder() 
			{
				
				if (this->mLeft)
				{
					this->mLeft->traverseRecursiveOrder();
				}

				std::cout << this->mData << std::endl;
				
				if (this->mRight)
				{
					this->mRight->traverseRecursiveOrder();
				}

			}
		};

		// These are the attributes of the OrderedSet (not
		//    the Node class)
		Node* mRoot;	// a little like mStart/mEnd in LList
		int mSize;

	public:
		OrderedSet() : mSize(0), mRoot(nullptr)
		{

		}

		~OrderedSet()
		{
			mRoot = nullptr;
			mSize = 0;
		}

		bool insert(const T& val)
		{
			if (mSize == 0)
			{
				mRoot = new Node(val);
				mSize++;
				return true;
			}
			else
			{
				if (mRoot->insert_recursive(val))
					mSize++;
			}

		}

		void traversal(traversalType tt)
		{
			if (mRoot)
			{
				if (tt == traversalType::PRE)
				{
					mRoot->traverseRecursivePre();
				}
				else if (tt == traversalType::POST)
				{
					mRoot->traverseRecursivePost();
				}
				else if (tt == traversalType::IN)
				{
					mRoot->traverseRecursiveOrder();
				}
			}
			else
			{
				std::cout << "this set empty! yeet!" << std::endl;
			}
		}
	};
}

