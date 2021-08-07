#include"Tools.h"



bool Tools::getline(istream& istr, ostream& ostr)
{
	char c = 1;
	ostr.clear();
	bool count = 0;
	while (c!='\n'&&c>0&&!istr.eof())
	{
		istr.get(c);
		if (c == '\n' && count == 0)
		{
			count = 1;
			c = 1;
			continue;
		}
		count = 1;
		if (c == '\n' || c <= 0 || istr.eof())
		{
			break;
		}
		ostr << c;
	}
	if (c  <= 0||istr.eof())
		return 0;
	return 1;
}
bool Tools::getline(istream& istr, string& str)
{
	char c=1;
	str.clear();
	bool count = 0;
	while (c != '\n' && c > 0&&!istr.eof())
	{
		istr.get(c);
		if (c == '\n' && count == 0)
		{
			count = 1;
			c = 1;
			continue;
		}
		if (c == '\n' || c <= 0||istr.eof())
		{
			break;
		}
		count = 1;
		str += c;
	}

	if (c <= 0||istr.eof())
		return 0;
	return 1;
}

bool Tools::isNumber(const string& str)
{
	if (str.length() == 0)
		return 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return 0;
		}
	}
	return 1;
}

string Tools::itos(int i)
{
	string str;
	stringstream ss;
	ss << i;
	ss >> str;
	return str;
}



void Tools::toUpper(string& str)
{
	for (char& c:str)
	{
		c = toupper(c);
	}
}

void Tools::toLower(string& str)
{
	for (char& c : str)
	{
		c = tolower(c);
	}
}

void Tools::setColor(int RGB)
{
	HANDLE Console;
	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, RGB);
}

void Tools::setCursor(int x, int y)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x; scrn.Y = y;
	SetConsoleCursorPosition(hOuput, scrn);
}

