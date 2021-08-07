#include<iostream>
#include<Windows.h>
#include"Tools.h"
#include"Board.h"
#include"User.h"

#pragma once



using namespace std;

class Viewer
{
public:
	void showUser(const User& u, vector<Board>& b);
	void showComment(int);//i added this
	void showDocument(int);//i edited this so it runs showComment after finish
	bool showBoardList(const vector<Board>& boards);
	bool showDocumentList(Board& b);
	fstream document;
	void Manu();
	string list[3] = { "Read","Creat","Exit" };

};
