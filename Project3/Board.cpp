#include"Board.h"

ostream& operator <<(ostream& ostr, Board& B)
{
	ostr << B.name<<"\t";
	for (int i = 0; i < B.docuList.size()&&i<B.titleList.size(); i++)
	{
		ostr << B.docuList[i] << " ";// << B.titleList[i] << " ";

	}
	ostr << "|";
	return ostr;
}
istream& operator>>(istream& istr, Board& b)
{
	istr >> b.name;
	return istr;
}
bool Board::operator==(const Board& b)
{
	if (b.name == name)
		return 1;
	return 0;
}
Board::~Board()
{

}
Board::Board(const Board& b)
{
	docuList=b.docuList;
	titleList = b.titleList;
	name = b.name;
}
Board& Board::operator=(const Board& b)
{
	name = b.name;
	docuList = b.docuList;
	titleList = b.titleList;
	return *this;
}

Board::Board()
{
	name = "";
	//docuList.resize(1, 0);
}

Board::Board(string name, string& list)
{
	this -> name = name;
	docuList.clear();
	for (int i = 0; i < list.length(); i++)
	{
		docuList.push_back(list[i]);
	}
}
Board::Board(string name)
{
	this->name = name;
	//docuList.resize(1, 0);
}