#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<stdio.h>
#include"User.h"
#include"Board.h"
#include"Viewer.h"
#include"Tools.h"
#pragma once

using namespace std;



enum readType
{
	in=0,
	out=1,
	app=2,
	inout=3,
	inapp=4,
	close=5
};


class BoardManager
{
public:
	BoardManager();
	~BoardManager();
	bool fileOpen(fstream&,string,readType);//openfile
	bool Login();//login level:root=3
	int signUp();//return -1=user exist 0=password notsame,1=access, 2=password too short
	bool Logout();//logout for relogin or shutdown
	void getCommand();//i edited this //only the last bits so that it shows post and comments at the same time

	
	bool DeleteBoard();//deleteboard(only root)
	int SelectBoard();//selectboard
	bool CreatBoard();//creatboard

	bool DeleteDocument(Board& b);//delete document b: the document 
	int SelectDocument( Board& b);//show document and select
	bool CreatDocument(Board& b);//creat new document
	bool DeleteDocument(int number);//delete document(creator or root)
	void EditDocument();

	bool CreateComment(Board& b);//i added this
	int ShutDown();//flush all data into file
	
	bool UserInformation();//show user detail
private:
	int documentNumber;
	int currentDoc;//i added this
	void Encryption(string&);
	void Decrypt(string&);
	vector <User> users;
	vector <Board> boards;
	int current_user;

	Viewer viewer;

	fstream userList;//save the user detail
	fstream BoardList;//save the board list
	fstream document;//save document;
};


