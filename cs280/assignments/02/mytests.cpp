#include <iostream>
#include "SortedList.h"
#include <functional>

int main()
{
	SortedList<int> myList;
	myList.push_back(1);
	myList.push_back(4);
	myList.push_back(3);
	myList.push_back(7);
	myList.push_back(2);
	myList.push_back(-14);
	myList.push_back(5);

	myList.merge_sort(std::less<int>());
//	myList.merge_sort(std::less<int>());

	SortedList<int>::const_iterator iter = myList.begin();

	while (iter != myList.end())
	{
		std::cout << *iter << " ";
		++iter;
	}

	std::cout << std::endl;

	return(0);
}

