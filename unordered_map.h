#pragma once
#include <utility>
#include<stdio.h>
#include <iostream>
namespace ssuds
{
	template <class K, class V>
	/// <summary>
	/// a unordered map class consisting of an array of std::pair pointers
	/// </summary>
	class UnorderedMap
	{
	protected:

		/// <summary>
		/// an array of std::pair pointers all of type K,V
		/// </summary>
		std::pair<K, V>** mTable;

		/// <summary>
		/// the capacity of the array of pointers, stored as an int
		/// </summary>
		int mCapacity;

		/// <summary>
		/// the size of the array of pointers, stored as an int
		/// </summary>
		int mSize;


	public:


		/// <summary>
		/// default constructor for the unordered Map class
		/// </summary>
		UnorderedMap() : mSize(0), mCapacity(0), mTable(nullptr)
		{

		};

		/// <summary>
		/// destructor for the unordered map class
		/// </summary>
		~UnorderedMap()
		{
			for (int i = 0; i < mCapacity; i++)
			{
				delete mTable[i];
			}
			mSize = 0;
			mCapacity = 0;
			delete[]mTable;
		}

		/// <summary>
		/// an override for the bracket operator
		/// This uses a key to be hashed and either be reallocated or found in the map
		/// This function is also is used to change the value within that key if it already exists
		/// </summary>
		/// <param name="the_key"></param> a reference to a key of type K
		/// <returns></returns> the value of type V
		V& operator[](const K& the_key)
		{
			if (mCapacity == 0 && mSize == 0)
			{
				mCapacity = 10;
				mTable = new std::pair<K, V>* [mCapacity];
				for (int i = 0; i < mCapacity; i++)
				{
					mTable[i] = nullptr;
				}
			}
			else if (mSize > mCapacity * 0.6)
			{
				grow();
			}
			
			signed long hashVal = hash_function(the_key,mCapacity);

			if (mTable[hashVal] == nullptr)
			{
				mTable[hashVal] = new std::pair<K, V>;
				mTable[hashVal]->first = the_key;
				mSize++;
				return mTable[hashVal]->second;
			}
			else
			{
				if (mTable[hashVal]->first == the_key)
				{
					return mTable[hashVal]->second;
				}
				else
				{
					signed long tempVal = hashVal;
					while (mTable[tempVal] != nullptr && mTable[tempVal]->first != the_key)
					{

						tempVal++;
						if (tempVal == mCapacity)
						{
							tempVal = 0;
						}
					}
					if (mTable[tempVal] == nullptr)
					{
						mTable[tempVal] = new std::pair<K, V>;
						mTable[tempVal]->first = the_key;
						mSize++;
						return mTable[tempVal]->second;
					}
					else
					{
						return mTable[tempVal]->second;
					}
				}
			}

		}

		/// <summary>
		/// a helper funtion that outputs the whole map
		/// This is done in the format  " Hash/capacitylocation  :  key    ,    value" 
		/// </summary>
		void debug_output()
		{
			for (int i = 0; i < mCapacity; i++)
			{
				if (mTable[i] != nullptr)
				{
					std::cout << i << " : " << mTable[i]->first << " , " << mTable[i]->second << std::endl;
				}
			}
		}

		/// <summary>
		/// a friend funtion to overload the stream operator
		/// </summary>
		/// <param name="os"></param>  the os stream
		/// <param name="OM"></param>  a reference to an unordered map OM
		/// <returns></returns>  os stream the the out stream
		friend std::ostream& operator <<(std::ostream& os, const UnorderedMap& OM)
		{
			os << "{ ";
			int counter = 0;
			for (int i = 0; i < OM.mCapacity; i++)
			{
				if (OM.mTable[i] != nullptr)
				{
					os << OM.mTable[i]->first << ":" << OM.mTable[i]->second;
					if (counter < OM.mSize - 1)
					{
						os << ",  ";
					}
					counter++;
				}
			}
			os << " }";
			return os;
		}

		/// <summary>
		/// a function to find if a key exists in the unordered map
		/// </summary>
		/// <param name="the_key"></param>  a reference to a key of type K
		/// <returns></returns> true if it is in the map, false if not
		bool contains(const K& the_key)
		{
			signed long hashVal = hash_function(the_key, mCapacity);
			while (mTable[hashVal] != nullptr)
			{
				if (mTable[hashVal]->first == the_key)
				{
					return true;
				}
				hashVal++;
				if (hashVal >= mCapacity)
				{
					hashVal = 0;
				}
			}

			return false;
		}

		/// <summary>
		/// helper grow function to grow the capacity and rehash all the values with a new hash value 
		/// </summary>
		void grow()
		{
			//make a new table at new capacity
			mCapacity *= 2;
			std::pair<K, V>** newTable = new std::pair<K, V>* [mCapacity];
			for (int i = 0; i < mCapacity; i++)
			{
				newTable[i] = nullptr;
			}

			for (int i = 0; i < mCapacity / 2; i++)
			{
				if (mTable[i] != nullptr)
				{
					signed long hashVal = hash_function(mTable[i]->first, mCapacity);
					while (newTable[hashVal] != nullptr)
					{
						hashVal++;
					}
					newTable[hashVal] = new std::pair<K, V>;
					newTable[hashVal]->first = mTable[i]->first;
					newTable[hashVal]->second = mTable[i]->second;
				}
				delete mTable[i];
			}
			delete[]mTable;
			mTable = newTable;

		}

		/// <summary>
		/// function to rebalance and shrink the capacity of the unordered map
		/// </summary>
		void shrink()
		{
			
			int newCap = mCapacity / 2;
			std::pair<K, V>** newTable = new std::pair<K, V>* [newCap];
			for (int i = 0; i < newCap; i++)
			{
				newTable[i] = nullptr;
			}

			for (int i = 0; i < mCapacity; i++)
			{
				if (mTable[i] != nullptr)
				{
					signed long hashVal = hash_function(mTable[i]->first, newCap);
					while (newTable[hashVal] != nullptr)
					{
						hashVal++;
					}
					newTable[hashVal] = new std::pair<K, V>;
					newTable[hashVal]->first = mTable[i]->first;
					newTable[hashVal]->second = mTable[i]->second;
				}
				delete mTable[i];
			}
			delete[]mTable;
			mTable = newTable;
			mCapacity = newCap;
			
		}


		/// <summary>
		/// A helper hash function, mods a key by the capacity of the map
		/// </summary>
		/// <param name="key"></param>  a key value of type K
		/// <returns></returns> a hash value for the key
		signed long hash_function(K key , int cap)
		{
			std::hash<K> myhash;
			return myhash(key) % cap;
		}


		/// <summary>
		/// a function to remove a key and value pair in the unordered map
		/// This removes both the key and the value and replaces it with a nullptr,
		/// if there are values immediately after the location it reorders those up to the next nullptr
		/// if a value was removed returns true, else false
		/// </summary>
		/// <param name="the_key"></param>  a const reference of type K
		/// <returns></returns> true if a value was removed, false if not
		bool remove(const K& the_key)
		{
			if (mCapacity > 10 && mSize <= mCapacity * 0.2)
			{
				shrink();
				std::cout << mSize << 'size' << std::endl;

			}
			
			signed long hashVal = hash_function(the_key,mCapacity);
			while (mTable[hashVal] != nullptr)
			{
				if (mTable[hashVal]->first == the_key)
				{
					delete mTable[hashVal];
					mTable[hashVal] = nullptr;
					mSize--;
					//redo the array afterwards
					hashVal++;
					while (mTable[hashVal] != nullptr)
					{
						std::pair<K, V>* Temp = mTable[hashVal];
						mTable[hashVal] = nullptr;
						signed long hashValNew = hash_function(Temp->first, mCapacity);
						while (mTable[hashValNew] != nullptr)
						{
							hashValNew++;
						}
						mTable[hashValNew] = Temp;

						hashVal++;
						if (hashVal == mCapacity)
						{
							hashVal = 0;
						}
					}


					return true;
				}
				hashVal++;
				if (hashVal >= mCapacity)
				{
					hashVal = 0;
				}
			}
			return false;
		}


		class UnorderedMapIterator
		{
		protected:
			/// <summary>
			/// the interger position, Index of data, for the iterator
			/// </summary>
			int mHash;

			/// <summary>
			/// a reference to the map you want to iterate through
			/// </summary>
			const UnorderedMap& mMap;

		public:
			/// <summary>
			/// the constructor for the iterator class
			/// </summary>
			/// <param name="sNode"></param> a node pointer 
			/// <param name="start_index"></param> the index you want to be at in the linked list
			UnorderedMapIterator(const UnorderedMap& itTable, int start_hash) : mHash(start_hash), mMap(itTable)
			{
				while (mMap.mTable[mHash] == nullptr)
				{
					mHash++;
				}
			}

			/// <summary>
			/// opperator to determine equality of two iterators
			/// </summary>
			/// <param name="other"></param> the other iterator
			/// <returns></returns> true or false
			bool operator==(const UnorderedMapIterator& other) const
			{
				return mMap.mTable[mHash]->first == other.mMap.mTable[mHash]->first && mMap.mTable[mHash]->second == other.mMap.mTable[mHash]->second;
			}

			/// <summary>
			/// opperator to determin inequality of two iterators
			/// </summary>
			/// <param name="other"></param> the other iterator
			/// <returns></returns> true or false
			bool operator!=(const UnorderedMapIterator& other) const
			{

				return mMap.mTable != other.mMap.mTable || mHash != other.mHash;
			}

			/// <summary>
			/// incriment operator overload for the iterator class
			/// </summary>
			void operator++()
			{
				mHash++;
				while (mMap.mTable[mHash] == nullptr && mHash < mMap.mCapacity)
				{
					mHash += 1;
				}

			}


			/// <summary>
			/// reference operator for the iterator class
			/// </summary>
			/// <returns></returns> the data of type T at that iterator location
			K& operator*() const
			{
				return mMap.mTable[mHash]->first;
			}

			/// <summary>
			/// index function to get the interger value of the iterators position
			/// </summary>
			/// <returns></returns> the position as an int
			int index()
			{
				return mHash;
			}

			/// <summary>
			/// makes the unordered a friend class to access data and functions
			/// </summary>
			friend class UnorderedMap;
		};

		/// <summary>
		/// begin function for a linked list iterator
		/// </summary>
		/// <returns></returns> a linked list iterator at the begining of the list
		UnorderedMapIterator begin() const
		{
			return UnorderedMapIterator(*this, 0);
		}

		/// <summary>
		/// end function for a linked list iterator
		/// </summary>
		/// <returns></returns> a linked list iterator at the end of the list
		UnorderedMapIterator end() const
		{
			return UnorderedMapIterator(*this, mCapacity);
		}

		/// <summary>
		/// a helper function that makes the results the way i want for parsing a book.
		/// </summary>
		void makeResultsHowIWant() const
		{
			std::ofstream results_csv("../data/Bookresults.csv");
			for (int i = 0; i < mCapacity; i++)
			{
				if (mTable[i] != nullptr)
				{
					results_csv << mTable[i]->first << " , " << mTable[i]->second << std::endl;
				}
			}
		}
	};
}