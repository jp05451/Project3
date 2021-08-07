#pragma once
#include<iostream>
#include<vector>
#include<sstream>
#include<Windows.h>
using namespace std;

namespace Tools
{
	bool isNumber(const string&);

	string itos(int);

	

	bool getline(istream&, ostream&);
	bool getline(istream&, string&);

	void toUpper(string&);

	void toLower(string&);

	void setColor(int RGB=7);

	void setCursor(int x = 0, int y = 0);

	template<class T>
	int BinarySearch(const T a[], int first, int last, T key)
	{
		int mid;
		while (first <= last)
		{
			mid = (first + last) / 2;
			if (a[mid] == key)
			{
				return mid;
			}
			else if (key < a[mid])
			{
				last = mid - 1;
			}
			else if (key > a[mid])
			{
				first = mid + 1;
			}
		}

		return -1;
	}
	
}