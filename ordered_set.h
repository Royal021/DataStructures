#pragma once
#include <array_list.h>

//looked at geeks for geeks article for erase

namespace ssuds
{
	/// <summary>
	/// enum helper class for determining traversal type in the ordered set
	/// </summary>
	enum class traversalType { PRE, POST, IN };

	template <class T>
	/// <summary>
	/// an ordered set/binary tree class
	/// </summary>
	class OrderedSet
	{
	protected:
		/// <summary>
		/// a nested Node class of data being stored in the ordered set
		/// </summary>
		class Node
		{
		public:
			/// <summary>
			/// data of type T
			/// </summary>
			T mData;
			/// <summary>
			/// a Node pointer to the left node
			/// </summary>
			Node* mLeft;
			/// <summary>
			/// a node pointer to the right node
			/// </summary>
			Node* mRight;

			/// <summary>
			/// default constructor for a node
			/// </summary>
			/// <param name="val"></param>
			Node(T val) : mData(val), mLeft(nullptr),
				mRight(nullptr)
			{

			}

			/// <summary>
			/// a destructor for a node, actually recursive
			/// </summary>
			~Node()
			{
				if (this)
				{
					if (this->mLeft) { delete this->mLeft; }
					if (this->mRight) { delete this->mRight; }
				}
			}

			/// <summary>
			/// a recursive function to insert a value into the ordered set
			/// </summary>
			/// <param name="val"></param> a value of type T
			/// <returns></returns> True if a new value was added, false if it already existsS
			bool insert_recursive(const T& val)
			{
				if (val < mData)
				{

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
					return false;
				}
			}

			/// <summary>
			/// a function to traverse an ordered set recursively
			/// </summary>
			/// <param name="tArray"></param> a reference to an array list of type T
			/// <param name="tty"></param> a enum to determine what way to traverse
			void traverseRecursive(ArrayList<T>& tArray, traversalType tty)
			{
				if (tty == traversalType::PRE)
				{
					tArray.append(this->mData);
				}

				if (this->mLeft)
				{
					this->mLeft->traverseRecursive(tArray,tty);
				}

				if (tty == traversalType::IN)
				{
					tArray.append(this->mData);
				}

				if (this->mRight)
				{
					this->mRight->traverseRecursive(tArray, tty);
				}

				if (tty == traversalType::POST)
				{
					tArray.append(this->mData);
				}
			}


			/// <summary>
			/// A recursive funtion to get the size of the ordered set
			/// </summary>
			/// <param name="OSize"></param>  a reference to an interger
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

			/// <summary>
			/// a function to rebalance the ordered set
			/// </summary>
			/// <param name="tempArray"></param>  a reference to an array list of type T
			/// <param name="min"></param> a minimum value to search with
			/// <param name="max"></param> a max value to search with
			/// <returns></returns> a Node* ot a new, rebalanced ordered set
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

			/// <summary>
			/// a boolean to check if a value is in the ordered set
			/// </summary>
			/// <param name="val"></param> a reference to a value of type T
			/// <returns></returns>  true if the value exists, false if not
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


			/// <summary>
			/// function to get the height of the ordered set
			/// </summary>
			/// <param name="LD"></param> Left depth
			/// <param name="RD"></param> Right Dept
			/// <returns></returns> an interger of depth
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

			/// <summary>
			/// a helper function to get the minimum value node from the current root
			/// </summary>
			/// <param name="curr"></param> a current node pointer
			/// <returns></returns> a min value node
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

			/// <summary>
			/// recursive function to get the tree string
			/// </summary> 
			/// <param name="depth"></param>  how deep you are in the tree
			/// <param name="prefix"></param>  the prefix string (e.g. "L:" or "R:")
			/// <returns></returns> a formatted string
			std::string tree_string_recursive(int depth, std::string prefix)
			{
				std::string result;
				// push the root data as character

				for (int j = 0; j != depth; j++)
				{
					result.push_back(' ');
					result.push_back(' ');
					result.push_back(' ');
				}
				for (int i = 0; prefix[i] != '\0'; i++)
				{
					result.push_back(prefix[i]);
				}
				//T temp = this->mData;
				result += std::to_string(this->mData);
				 

				// if leaf node, then return
				if (!this->mLeft && !this->mRight)
					return result;
				
				// for left subtree
				if (this->mLeft)
				{
					result.push_back('\n');

					result += this->mLeft->tree_string_recursive(depth + 1, "L:");
				}

				// only if right child is present to
				// avoid extra parenthesis
				if (this->mRight) 
				{
					result.push_back('\n');
					result += this->mRight->tree_string_recursive(depth + 1, "R:");
				}

				return result;
				// Show three space for every depth level

				// Show the prefix string (e.g. "L:" or "R:")

				// Call this function recursively, passing the left child
				//   "L:" and the right child "R:".  Add one to our depth for
				//   this call.
			}

			/// <summary>
			/// helper function to remove values recursively
			/// </summary>
			/// <param name="val"></param>  a vvalue of type T 
			/// <returns></returns> true or false if a value was removed
			bool removeRecursive(const T& val)
			{
				
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

		/// <summary>
		/// the root node of the ordered set class
		/// </summary>
		Node* mRoot;	
		/// <summary>
		/// the size of the ordered set
		/// </summary>
		int mSize;

	public:

		/// <summary>
		/// iterator class for ordered set
		/// </summary>
		class OrderedSetIterator
		{
		protected:

			/// <summary>
			/// a stack of nodes to hold on to
			/// </summary>
			ssuds::Stack<Node*> holdingStack;
			/// <summary>
			/// a pointer to the node we are currently at
			/// </summary>
			Node* currNode;

		public:

			/// <summary>
			/// default constructor for the iterator, pushes it to the far right of the node
			/// </summary>
			/// <param name="ItNode"></param> the node you wish to start on
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
					holdingStack.pop();
				}
			}

			/// <summary>
			/// equal operator for the iterator
			/// </summary>
			/// <param name="other"></param> another iterator
			/// <returns></returns> true if same, false if not
			bool operator==(const OrderedSetIterator& other) const
			{
				return currNode == other.currNode && holdingStack == other.holdingStack;
			}

			/// <summary>
			/// inequality operator for ordered set iterator
			/// </summary>
			/// <param name="other"></param> another ordered set
			/// <returns></returns> true if different, false if not
			bool operator!=(const OrderedSetIterator& other) const
			{
				return currNode != other.currNode;
			}

			/// <summary>
			/// increment for the iterator
			/// </summary>
			void operator++()
			{
				currNode = currNode->mRight;
				while (currNode)
				{
					holdingStack.push(currNode);
					currNode = currNode->mLeft;
				}
				if (currNode == NULL && holdingStack.empty() != 1)
				{
					currNode = holdingStack.top();
					holdingStack.pop();
				}
				if (holdingStack.empty() == 1 && currNode == NULL)
				{
					currNode = nullptr;
				}

			}

			/// <summary>
			/// dereference for the iterator, gets the data
			/// </summary>
			/// <returns></returns>
			T& operator*()
			{
				return currNode->mData;
			}

		};

		/// <summary>
		/// default constructor for the ordered set
		/// </summary>
		OrderedSet() : mSize(0), mRoot(nullptr)
		{

		}

		/// <summary>
		/// destructor for the ordered set
		/// </summary>
		~OrderedSet()
		{
			delete mRoot;
			mSize = 0;
		}

		/// <summary>
		/// a copy constructor for ordered set
		/// </summary>
		/// <param name="other"></param> another order set to make a deep copy of
		OrderedSet( OrderedSet& other)
		{
			
			ArrayList<T> temp = other.traversal(ssuds::traversalType::PRE);
			
			for (int i = 0; i < temp.size(); i++)
			{
				this->insert(temp[i]);
			}
			
		}

		/// <summary>
		/// A move constructor for the Ordered set class
		/// </summary>
		/// <param name="other"></param> a reference to another ordered
		OrderedSet(OrderedSet&& other) : mSize(other.mSize), mRoot(other.mRoot)
		{
			
			other.mRoot = nullptr;
			other.mRoot->mLeft = nullptr;
			other.mRoot->mRight = nullptr;
			other.mSize = 0;
		}

		/// <summary>
		/// initializer list constructor for Orderedset
		/// </summary>
		/// <param name="ilist"></param> a list of type T
		OrderedSet(std::initializer_list<T> ilist) : mSize((int)ilist.size())
		{
			mSize = 0;
			for (T val : ilist)
				this->insert(val);				
		}

		/// <summary>
		/// OrderedSet = operator, overloads the operator
		/// </summary>
		/// <param name="other"></param> the other OrderedSet you want to copy
		/// <returns></returns> a copied OrderedSet
		OrderedSet<T>& operator= (const OrderedSet<T>& other)
		{
			if (mSize != nullptr)
			{
				clear();
			}
			if (other.mSize == nullptr)
			{
				clear();
				return *this;
			}
			else
			{
				ArrayList<T> temp = other.traversal(ssuds::traversalType::PRE);

				for (int i = 0; i < temp.size(); i++)
				{
					this->insert(temp[i]);
				}
			}
			return *this;
		}


		/// <summary>
		/// insert function for ordered set, callse the recursive fucntion in the node calss
		/// </summary>
		/// <param name="val"></param> a value of type t
		/// <returns></returns> true if value was added, false if not
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

		/// <summary>
		/// function to traverse the ordered set 
		/// </summary>
		/// <param name="tt"></param> a traversal enumerator type
		/// <returns></returns> an arraylist of type T
		ssuds::ArrayList<T> traversal(traversalType tt)
		{

			if (mRoot)
			{
				ssuds::ArrayList<T> TraversedArray;
				
				this->mRoot->traverseRecursive(TraversedArray, tt);
			
				return TraversedArray;
			}
			else
			{
				ssuds::ArrayList<T> EmptyTraversedArray;
				return EmptyTraversedArray;
			}
		}

		/// <summary>
		/// function to clear to the ordered set
		/// </summary>
		void clear()
		{
			delete mRoot;
			mSize = 0;
			mRoot = nullptr;
		}

		/// <summary>
		/// function to get the size of the ordered set
		/// </summary>
		/// <returns></returns> the size of the set as an interger
		int size()
		{
			int totalSize = 0;
			if (mRoot)
			{
				mRoot->SizeRecursive(totalSize);
			}
			return totalSize;
		}

		/// <summary>
		/// function to rebalance the ordered set
		/// </summary>
		void rebalance()
		{
			ArrayList<T> temp = this->traversal(ssuds::traversalType::IN);
			this->clear();
			this->mRoot = this->mRoot->rebalance_recursive(temp, 0, temp.size() - 1);
			this->mSize = temp.size();
		}

		/// <summary>
		/// a function to see if a value is currently in the ordered set
		/// </summary>
		/// <param name="val"></param> a value of type T
		/// <returns></returns> true if it is in the set, false if not
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

		/// <summary>
		/// a function to get the max height of the ordered set
		/// </summary>
		/// <returns></returns> the height of the ordered set
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

		/// <summary>
		/// function to erase a value in a ordered set
		/// </summary>
		/// <param name="val"></param> a value of type t
		/// <returns></returns> true if removed, false if not
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

		/// <summary>
		/// iterator for ordered set begin function. calls the constructor on first value
		/// </summary>
		/// <returns></returns> an iterator for the ordered set
		OrderedSetIterator begin() const
		{
			return OrderedSetIterator(mRoot);
		}

		/// <summary>
		/// iterator for ordered set end function. calls the constructor on first value
		/// </summary>
		/// <returns></returns> a iterator at an end 
		OrderedSetIterator end() const
		{
			return OrderedSetIterator(nullptr);
		}

		/// <summary>
		/// gets the intersection of two ordered sets
		/// </summary>
		/// <param name="other"></param> another ordered set
		/// <returns></returns> an arraylist of type T with the intersecting values
		ssuds::ArrayList<T> Intersection(OrderedSet& other)
		{
			ArrayList<T> result;
			ArrayList<T> OS1 = this->traversal(ssuds::traversalType::IN);
			ArrayList<T> OS2 = other.traversal(ssuds::traversalType::IN);
			int i = 0, j = 0;
			while (i < OS1.size() && j < OS2.size()) {
				if (OS1[i] == OS2[j]) 
				{
					result.append(OS1[i]);
					i++;
					j++;
				}
				else if (OS1[i] < OS2[j]) {
					i++;
				}
				else {
					j++;
				}
			}
			return result;
		}

		/// <summary>
		/// a function to get an array list of the union of two data sets, (the same values between the two)
		/// </summary>
		/// <param name="other"></param>  another ordered set
		/// <returns></returns> an array list with the union
		ssuds::ArrayList <T> Union(OrderedSet & other)
		{
			ArrayList<T> result;
			ArrayList<T> OS1 = this->traversal(ssuds::traversalType::IN);
			ArrayList<T> OS2 = other.traversal(ssuds::traversalType::IN);			
			int i = 0, j = 0;

			while (i < OS1.size() && j < OS2.size()) 
			{
				if (OS1[i] < OS2[j])
					result.append(OS1[i++]);

				else if (OS2[j] < OS1[i])
					result.append(OS2[j++]);

				else {
					result.append(OS2[j++]);
					i++;
				}
			}

			while (i < OS1.size())
			{
				result.append(OS1[i++]);
			}
			while (j < OS2.size())
			{
				result.append(OS2[j++]);
			}
			
			return result;
		}

		/// <summary>
		/// get the relative difference of two ordered sets
		/// </summary>
		/// <param name="other"></param> another ordered set
		/// <returns></returns> a in order array list
		ssuds::ArrayList<T> RelativeDifference(OrderedSet& other)
		{
			OrderedSet<T> OS1 = other;
			

			ArrayList<T> OS2 = this->traversal(ssuds::traversalType::IN);
			for (int i = 0; i < OS2.size(); i++)
			{
				OS1.erase(OS2[i]);
			}
			ArrayList<T> result = OS1.traversal(ssuds::traversalType::IN);
			return result;
		}

		/// <summary>
		/// a function to make a tree string version of the orderedset to visualize it
		/// </summary>
		/// <returns></returns>  a string formatted
		std::string tree_string()
		{
			if (mRoot)
				return mRoot->tree_string_recursive(0, "");
			else
				return "";
		}
	};
}

