#include "array_list.h"
#include <iostream>
#include <stdexcept>
ssuds::ArrayList::ArrayList() :mData(nullptr), mSize(0)
{
}

ssuds::ArrayList::~ArrayList()
{
	delete[] mData;
	mData = nullptr;
	std::cout << "array list destroyed!" << std::endl;
}

void ssuds::ArrayList::append(std::string new_string)
{

	std::string* temp = new std::string[mSize + 1];

	for (int i = 0; i < mSize; i++)
	{
		temp[i] = mData[i];
	}
	
	temp[mSize] =  new_string ;
	delete[] mData;		
	mData = temp;	
	mSize++;
}

int ssuds::ArrayList::size()
{
	return mSize;
}

void ssuds::ArrayList::insert(std::string new_string, int index)
{
	if (mSize <= index)
	{
		throw std::out_of_range ("index out of range of the Array list");
	}
	std::string* temp = new std::string[mSize + 1]; 

	for (int i = 0; i < index; i++)
	{
		temp[i] = mData[i];
	}
	
	temp[index] = new_string;

	for (int placehold = index; placehold < mSize; placehold++)
	{
		temp[(placehold + 1)] = mData[placehold];
	}
	
	delete[] mData;
	mData = temp;
	mSize++;
}

void ssuds::ArrayList::clear()
{
	mData = nullptr;
	mSize = 0;
}

std::string ssuds::ArrayList::get(int index)
{
	if (mSize <= index)
	{
		throw std::out_of_range ("index out of range of the Array list");
	}
	return mData[index];
}

signed int ssuds::ArrayList::find(std::string old_string, int index)
{
	if (mSize <= index)
	{
		throw std::out_of_range("index out of range of the Array list");
	}

	for (int i = index; i < mSize; i++)
	{
		if (mData[i] == old_string)
		{
			return i;
		}
	}
	return -1;	
}

void ssuds::ArrayList::remove(int index)
{
	std::string* temp = new std::string[mSize - 1];

	for (int i = 0; i < index; i++)
	{
		temp[i] = mData[i];
	}
	for (int placehold = index; placehold < mSize - 1; placehold++)
	{
		temp[(placehold)] = mData[placehold + 1];
	}
	delete[] mData;
	mData = temp;
	mSize--;

}

int ssuds::ArrayList::remove_all(std::string old_string)
{
	int count = 0;
	
	while (find(old_string) > -1)
	{
		int index = find(old_string);
		remove(index);
		count++;
	}
	
	return count;
}

