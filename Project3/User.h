#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

enum level
{
	guess,
	user,
	root
};

class User
{
public:
	bool operator == (const User& user);
	friend ostream& operator<<(ostream& ostr, User user);
	friend istream& operator>> (istream&, User& user);
	bool Compare(const User& user) const;
	// Other infos, e.x. comment_nums, post_num, �K.
	User();
	User(string,string,int);
	//void getUser();
	string name;
	string password;
	int Permission_level;	// �v������
	vector <int> postsID;	// �����إ߹L��post
};