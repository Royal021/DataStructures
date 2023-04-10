#pragma once
#include <array_list.h>

//looked at geeks for geeks article for erase

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
				if (this)
				{
					if (this->mLeft) { delete this->mLeft; }
					if (this->mRight) { delete this->mRight; }
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
					{
						mRight->insert_recursive(val);
					}
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

			void traverseRecursivePre(ArrayList<T>& tArray)
			{

				tArray.append(this->mData);
				if (this->mLeft)
				{
					this->mLeft->traverseRecursivePre(tArray);
				}
				if (this->mRight)
				{
					this->mRight->traverseRecursivePre(tArray);
				}

			}

			void traverseRecursivePost(ArrayList<T>& tArray)
			{

				if (this->mLeft)
				{
					this->mLeft->traverseRecursivePost(tArray);
				}

				if (this->mRight)
				{
					this->mRight->traverseRecursivePost(tArray);
				}
				tArray.append(this->mData);
			}

			void traverseRecursiveOrder(ArrayList<T>& tArray)
			{

				if (this->mLeft)
				{
					this->mLeft->traverseRecursiveOrder(tArray);
				}

				tArray.append(this->mData);

				if (this->mRight)
				{
					this->mRight->traverseRecursiveOrder(tArray);
				}

			}

			void SizeRecursive(int& OSize)
			{
				OSize++;
				if (this->mLeft)
				{
					this->mLeft->SizeRecursive(OSize);
				}
				if (this->mRight)
				{
					this->mRight->SizeRecursive(OSize);
				}


			}

			Node* rebalance_recursive(ArrayList<T>& tempArray, int min, int max)
			{

				int mid = (max + min) / 2;
				Node* tempNode = new Node(tempArray[mid]);
				if (min < mid)
				{
					tempNode->mLeft = tempNode->mLeft->rebalance_recursive(tempArray, min, mid - 1);
				}
				if (mid < max)
				{
					tempNode->mRight = tempNode->mRight->rebalance_recursive(tempArray, mid + 1, max);
				}
				return tempNode;
			}

			bool contains_recursive(const T& val)
			{
				if (this->mData == val)
				{
					return true;
				}
				else if (val < this->mData && this->mLeft)
				{
					this->mLeft->contains_recursive(val);
				}
				else if (val > this->mData && this->mRight)
				{
					this->mRight->contains_recursive(val);
				}
				else
				{
					return false;
				}
			}

			int get_height_recursive(int LD, int RD)
			{
				int lDepth = LD;
				int rDepth = RD;
				if (this->mLeft)
					lDepth = this->mLeft->get_height_recursive(LD, RD);
				if (this->mRight)
					rDepth = this->mRight->get_height_recursive(LD, RD);


				if (lDepth > rDepth)
					return (lDepth + 1);
				else
					return (rDepth + 1);
			}

			Node* getMinNode(Node* curr)
			{
				if (this->mRight == nullptr) { curr = curr->mLeft; }
				else { curr = curr->mRight; }
				while (curr->mLeft != nullptr) 
				{
					curr = curr->mLeft;
				}
				return curr;
			}

			bool removeRecursive(const T& val)
			{
				// If the key to be deleted is
				// smaller than the root's
				// key, then it lies in left subtree
				if (this == nullptr)
				{
					return false;
				}
				else if (val < this->mData)
				{
					if (this->mLeft != nullptr)
					{
						if (this->mLeft->mData == val && this->mLeft->mRight == nullptr && this->mLeft->mLeft == nullptr)
						{
							Node* temp = this->mLeft;
							this->mLeft = nullptr;
							delete temp;
							return true;
						}
						else if (this->mLeft->mData == val && this->mLeft->mRight != nullptr && this->mLeft->mLeft == nullptr)
						{
							Node* temp = this->mLeft->mRight;
							this->mLeft->mData = temp->mData;
							this->mLeft->mLeft = temp->mLeft;
							this->mLeft->mRight = temp->mRight;
							temp->mRight = nullptr;
							temp->mLeft = nullptr;
							delete temp;
							
							return true;

						}
						else if (this->mLeft->mData == val && this->mLeft->mRight == nullptr && this->mLeft->mLeft != nullptr)
						{
							Node* temp = this->mLeft->mLeft;
							this->mLeft->mData = temp->mData;
							this->mLeft->mLeft = temp->mLeft;
							this->mLeft->mRight = temp->mRight;
							temp->mRight = nullptr;
							temp->mLeft = nullptr;
							delete temp;
							return true;

						}
					}
					this->mLeft->removeRecursive(val);
				}

				// If the key to be deleted is
				// greater than the root's
				// key, then it lies in right subtree
				else if (val > this->mData)
				{
					if (this->mRight != nullptr)
					{
						if (this->mRight->mData == val && this->mRight->mRight == nullptr && this->mRight->mLeft == nullptr)
						{
							Node* temp = this->mRight;
							this->mRight = nullptr;
							delete temp;
							return true;
						}
						else if (this->mRight->mData == val && this->mRight->mRight != nullptr && this->mRight->mLeft == nullptr)
						{
							Node* temp = this->mRight->mRight;
							this->mRight->mData = temp->mData;
							this->mRight->mLeft = temp->mLeft;
							this->mRight->mRight = temp->mRight;
							temp->mRight = nullptr;
							temp->mLeft = nullptr;
							delete temp;
							return true;

						}
						else if (this->mRight->mData == val && this->mRight->mRight == nullptr && this->mRight->mLeft != nullptr)
						{
							Node* temp = this->mRight->mLeft;
							this->mRight->mData = temp->mData;
							this->mRight->mLeft = temp->mLeft;
							this->mRight->mRight = temp->mRight;
							temp->mRight = nullptr;
							temp->mLeft = nullptr;
							delete temp;
							return true;

						}
					}
					this->mRight->removeRecursive(val);
				}
			
				else {
				
					Node* temp = getMinNode(this);
					this->mData = temp->mData;
					if (this->mRight)
					{
						if (this->mRight->mData == temp->mData && this->mRight->mRight == nullptr && this->mRight->mLeft == nullptr)
						{
							this->mRight = nullptr;
							delete temp;
							return true;
						}
						this->mRight->removeRecursive(this->mData);
					}
					else
					{
						if (this->mLeft->mData == temp->mData && this->mLeft->mRight == nullptr && this->mLeft->mLeft == nullptr)
						{
							this->mLeft = nullptr;
							delete temp;
							return true;
						}
						this->mLeft->removeRecursive(this->mData);
					}

					return true;
				}
			}
		};

		// These are the attributes of the OrderedSet (not
		//    the Node class)
		Node* mRoot;	// a little like mStart/mEnd in LList
		int mSize;

	public:

		class OrderedSetIterator
		{
		protected:
			ssuds::Stack<Node*> holdingStack;

			Node* currNode;
		public:
			OrderedSetIterator(Node* ItNode) : currNode(ItNode)
			{
				
				while (currNode)
				{
					holdingStack.push(currNode);
					currNode = currNode->mLeft;
					
				}
				if (holdingStack.empty() == 0)
				{
					currNode = holdingStack.top();
				}
			}

			bool operator==(const OrderedSetIterator& other) const
			{
				return currNode == other.currNode && holdingStack == other.holdingStack;
			}

			bool operator!=(const OrderedSetIterator& other) const
			{
				return currNode != other.currNode;
			}

			void operator++()
			{
				if (currNode->mRight)
				{
					currNode = currNode->mRight;
					while (currNode)
					{
						holdingStack.push(currNode);
						currNode = currNode->mLeft;
					}
					if (holdingStack.empty() == 0)
					{
						currNode = holdingStack.top();
					}
				}
				else if (currNode->mRight == NULL)
				{
					holdingStack.pop();
					currNode = holdingStack.top();		
				}
				else if (holdingStack.empty() == 1)
				{
					currNode = nullptr;
				}
			}
			T& operator*()
			{
				return currNode->mData;
			}

		};
		OrderedSet() : mSize(0), mRoot(nullptr)
		{

		}

		~OrderedSet()
		{
			delete mRoot;
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

		ssuds::ArrayList<T> traversal(traversalType tt)
		{

			if (mRoot)
			{
				ssuds::ArrayList<T> TraversedArray;
				if (tt == traversalType::PRE)
				{
					this->mRoot->traverseRecursivePre(TraversedArray);
				}
				else if (tt == traversalType::POST)
				{
					this->mRoot->traverseRecursivePost(TraversedArray);
				}
				else if (tt == traversalType::IN)
				{
					this->mRoot->traverseRecursiveOrder(TraversedArray);
				}
				return TraversedArray;
			}
			else
			{
				ssuds::ArrayList<T> EmptyTraversedArray;
				return EmptyTraversedArray;
			}
		}

		void clear()
		{
			delete mRoot;
			mSize = 0;
			mRoot = nullptr;
		}

		int size()
		{
			int totalSize = 0;
			if (mRoot)
			{
				mRoot->SizeRecursive(totalSize);
			}
			return totalSize;
		}

		void rebalance()
		{
			ArrayList<T> temp = this->traversal(ssuds::traversalType::IN);
			this->clear();
			this->mRoot = this->mRoot->rebalance_recursive(temp, 0, temp.size() - 1);
			this->mSize = temp.size();
		}

		bool contains(const T& val)
		{
			if (mSize == 0)
			{
				return false;
			}
			else
			{
				if (this->mRoot->contains_recursive(val) == true)
				{
					return true;
				}
				return false;
			}
		}

		int get_height()
		{
			int HCount = 0;
			if (this->mRoot)
			{
				HCount = mRoot->get_height_recursive(0, 0);
			}
			else { ; }
			return HCount;
		}

		bool erase(const T& val)
		{
			if (mSize > 0)
			{
				if (mRoot->removeRecursive(val))
				{
					mSize--;
					return true;
				}
			}
			return false;
		}


		OrderedSetIterator begin() const
		{
			return OrderedSetIterator(mRoot);
		}

		
		OrderedSetIterator end() const
		{
			return OrderedSetIterator(nullptr);
		}
	};
}

