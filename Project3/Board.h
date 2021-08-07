#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class Board
{
public:
	Board();
	Board(string name);
	Board(string name, string&);
	Board(const Board&);
	~Board();
	friend ostream& operator <<(ostream& ostr, Board& B);
	friend istream& operator>>(istream& istr, Board& b);
	bool operator == (const Board& b);
	Board& operator=(const Board& b);
	string name;
	vector<int> docuList;
	vector<string>titleList;
	fstream document;
};