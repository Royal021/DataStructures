#pragma once
#include<array_list.h>
#include<random>
#include<chrono>

namespace ssuds
{
	enum class sort_type { ASCENDING, DESCENDING };

	template<class T>
	void swap(T* a, T* b)
	{
		T t = *a;
		*a = *b;
		*b = t;
	}

	template<class T>
	bool outOfOrder(const  T& val1, const T& val2, sort_type st)
	{
		if (st == sort_type::ASCENDING)
			return val1 >= val2;
		else
			return val1 <= val2;
	}



	template <class T>
	void swap(ssuds::ArrayList<T>& Tlist, int value1Index, int value2Index)
	{
		T value1 = Tlist[value1Index];
		T value2 = Tlist[value2Index];

		Tlist.remove(value1Index);
		Tlist.remove(value2Index);

		Tlist.insert(value1, value2Index);
		Tlist.insert(value2, value1Index);

	}

	template <class T>
	long long int bubble_sort(ssuds::ArrayList<T>& Tlist, sort_type stype)
	{
		long long int swap_count = 0;
		int n = Tlist.size();
		for (int i = 0; i < n; i++)
		{
			int sorted = 1;
			for (int j = 0; j < n - 1 - i; j++)
			{
				if (outOfOrder(Tlist[j], Tlist[j + 1], stype))
				{
					swap(&Tlist[j], &Tlist[j + 1]);
					swap_count++;
					sorted = 2;
				}


			}
			if (sorted == 1)
			{
				break;
			}
		}
		return swap_count;
	}

	template <class T>
	void shuffle(ssuds::ArrayList<T>& Tlist)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, Tlist.size() - 1);
		for (int i = Tlist.size() - 1; i > 0; i--)
		{

			int j = dist(rng);
			if (j == i)
			{
				;
			}
			else
			{
				swap(&Tlist[i], &Tlist[j]);
			}

		}
	}

	template <class T>
	long int mergeSort(ssuds::ArrayList<T>& Tlist, sort_type sType)
	{
		return mergeSortRecursive(Tlist, sType, 0, Tlist.size() - 1);
	}

	template <class T>
	long int mergeSortRecursive(ssuds::ArrayList<T>& Tlist, sort_type sType, int left, int right)
	{
		if (left >= right)
		{
			return 0;
		}
		int mid = (left + right) / 2;
		long int a = mergeSortRecursive(Tlist, sType, left, mid);
		long int b = mergeSortRecursive(Tlist, sType, mid + 1, right);
		long int c = mergeSortMerge(Tlist, sType, left, mid, right);
		return a + b + c;

	}

	template <class T>
	long int mergeSortMerge(ssuds::ArrayList<T>& Tlist, sort_type sType, int left, int mid, int right)
	{
		long int counter = 0;
		int n1 = mid - left + 1;
		int n2 = right - mid;
		ssuds::ArrayList<T> list1;
		ssuds::ArrayList<T> list2;
		for (int i = left; i <= mid; i++)
		{
			list1.append(Tlist[i]);
		}
		for (int i = mid + 1; i <= right; i++)
		{
			list2.append(Tlist[i]);
		}

		int index1 = 0;
		int index2 = 0;
		int index_main = left;
		while (index1 < n1 && index2 < n2)
		{

			if (outOfOrder(list2[index2], list1[index1], sType))
			{
				Tlist[index_main++] = list1[index1++];
			}
			else
			{
				Tlist[index_main++] = list2[index2++];
			}
			counter++;
		}
		while (index1 < n1)
		{
			Tlist[index_main++] = list1[index1++];
		}
		while (index2 < n2)
		{
			Tlist[index_main++] = list2[index2++];
		}
		return counter;
	}

	template <class T>
	signed long int binarySearch(const ssuds::ArrayList<T>& Tlist, sort_type stype, T searchValue, long int* counter = nullptr)
	{
		long int min;
		long int max;
		if (stype == sort_type::ASCENDING)
		{
			min = 0;
			max = Tlist.size() - 1;
		}
		else
		{
			max = 0;
			min = Tlist.size() - 1;
		}
		while (min <= max)
		{
			int mid = (min + max) / 2;
			if (Tlist[mid] == searchValue)
			{
				return mid;
			}
			if (Tlist[mid] > searchValue)
			{
				max = mid - 1;
			}
			else
			{
				min = mid + 1;
			}
			if (counter != nullptr)
			{
				(*counter)++;
			}
		}

		return -1;
	}







	
	template <class T>
	long int qspartition(ssuds::ArrayList<T>& Tlist, long int low, long int high, sort_type stype, long int* counter = nullptr) {
		T pivot = Tlist[high];
		
			int i = (low - 1);

			for (int j = low; j < high; j++) {
				if (outOfOrder( pivot, Tlist[j], stype))
				{
					i++;
					swap(&Tlist[i], &Tlist[j]);

					if (counter != nullptr)
					{
						(*counter)++;
					}
				}
			}

			swap(&Tlist[i + 1], &Tlist[high]);
			if (counter != nullptr)
			{
				(*counter)++;
			}

			return (i + 1);
		
		
	}

	template <class T>
	void quickSort(ssuds::ArrayList<T>& Tlist,long int low, long int high, sort_type stype, long int* counter = nullptr) {
		if (low < high) 
		{
			long int qspivot = qspartition(Tlist, low, high, stype, counter);

			quickSort(Tlist, low, qspivot - 1, stype, counter);

			quickSort(Tlist, qspivot + 1, high, stype, counter);
		}
		
	}

	template <class T>
	long int insertionSort(ssuds::ArrayList<T>& Tlist, sort_type stype)
	{
		int i, j;
		long int counter = 0;
		T Temp;
		for (i = 1; i < Tlist.size(); i++)
		{
			Temp = Tlist[i];
			j = i - 1;
			while (j >= 0 && (outOfOrder(Tlist[j], Temp, stype)))
			{
				Tlist[j + 1] = Tlist[j];
				j = j - 1;
			}
			Tlist[j + 1] = Temp;
			counter++;
		}
		return counter;
	}

}

