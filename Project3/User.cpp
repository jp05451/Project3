#include"User.h"
/*bool User::Compare(const User& user) const
{
	return password == user.password && name == user.name;
}*/
ostream& operator<<(ostream& ostr,  User user)
{
	ostr << user.name<<"\t";
	ostr << user.password << "\t";
	ostr << user.Permission_level << "\t";
	for (vector<int>::iterator it = user.postsID.begin(); it < user.postsID.end(); it++)
	{
		ostr << (*it) << " ";
	}
	ostr << "|";
	return ostr;
}
istream& operator>> (istream& istr, User& user)
{
	string name;
	string password;
	istr >> name >> password;
	user.name = name;
	user.password = password;
	return istr;
}

User::User()
{
	name = "guess";
	password = "0";
	Permission_level = 0;
	postsID.resize(1, 0);
}
User::User(string name,string password,int l)
{
	this->name = name;
	this->password = password;
	Permission_level = l;
	postsID.resize(1, 0);
}
bool User::operator==(const User& user)
{
	return  name == user.name;//&&password == user.password;
}
bool User::Compare(const User& user) const
{
	return user.name == name && user.password == password;
}