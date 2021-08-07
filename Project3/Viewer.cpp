#include"Viewer.h"

bool Viewer::showBoardList(const vector<Board>& boards)
{
	system("cls");
	cout << "Boards:" << endl;
	cout << "-3\tUser information" << endl;
	cout << "-2\tDelete" << endl;
	cout << "-1\tLogout" << endl;
	cout << "0\tCreate" << endl;
	cout << endl;
	if (boards.empty())
	{
		cout << "There's no board, yet. You should create one!" << endl;
		return 0;
	}

	for (int i = 0; i < boards.size(); i++)
	{
		cout<<i+1<<"\t" << boards[i].name << endl;
	}
}
void Viewer::showComment(int number)
{
	cout << "Comments:" << endl;
	//cout << "-1\tExit" << endl;
	//cout << "0\tNew Comment" << endl;
	string name = Tools::itos(number) + "_comment.txt";
	document.open(name, ios::in);
	if (document.fail()) {
		cout << "   @A<\nIt seems like there's no comment for now. Enter \"0\" to create a new one." << endl;
		//system("pause");
		return;
	}
	
	while (!document.eof())
	{
		string buffer;
		Tools::getline(document, buffer);
		while (!buffer.empty()&&buffer[0] == '\n')buffer.erase(buffer.begin());
		if (buffer.empty())continue;
		if (buffer[0] == '1') {
			Tools::setColor(BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY|FOREGROUND_BLUE);
			cout << "COOL";
			Tools::setColor();
		}
		else if (buffer[0] == '0') {
			Tools::setColor(BACKGROUND_BLUE|BACKGROUND_RED|FOREGROUND_RED);
			cout << "LAME";
			Tools::setColor();
		}
		else {
			cout << " -->";
		}
		buffer.erase(0,2);
		cout << " ";
		Tools::setColor(FOREGROUND_GREEN | FOREGROUND_RED);
		while (buffer[0] != '\t') {
			cout << buffer[0];
			buffer.erase(0, 1);
		}
		buffer.erase(0, 1);
		cout << ":";
		Tools::setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << buffer << endl;
		Tools::setColor();
	}
	document.close();
	cout << endl;
	cout << "-1\tExit" << endl;
	cout << "0\tNew Comment" << endl;
	//system("pause");
}
void Viewer::showDocument(int number)
{
	system("cls");
	string name=Tools::itos(number)+".txt";
	document.open(name, ios::in);
	string title;
	Tools::getline(document, title);
	string rate;
	while (!title.empty() && title[0] != '\t') {
		rate.push_back(title[0]);
		title.erase(0, 1);
	}
	title.erase(0, 1);
	if (title.empty()) {
		title = rate;
		rate = "0";
	}
	int score = stoi(rate);
	
	if (score > 0)Tools::setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (score < 0)Tools::setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << score << "\t";
	
	
	Tools::setColor(160);
	cout << title;
	cout << endl<<endl;
	Tools::setColor();
	while (!document.eof())
	{
		Tools::getline(document, cout);
		cout << endl;
	}
	document.close();
	//system("pause");
	cout << endl;
	showComment(number);
}

bool Viewer::showDocumentList(Board& b)
{
	system("cls");
	cout <<"Board: " << b.name << endl<<endl ;
	cout << "-2\tDelete" << endl;
	cout << "-1\tExit" << endl;
	cout << "0\tCreate" << endl<<endl;
	
	if (b.titleList.size() == 0)
	{
		cout << "The board is so empty! You should create a post!" << endl;
		return 0;
	}

	for (int i = 0; i < b.titleList.size(); i++)
	{
		string rate;
		string title = b.titleList[i];
		while (!title.empty() && title[0] != '\t') {
			rate.push_back(title[0]);
			title.erase(0, 1);
		}
		title.erase(0, 1);
		if (title.empty()) {
			title = rate;
			rate = "0";
		}
		int score = stoi(rate);
		cout << i + 1 << "\t";
		if (score > 0)Tools::setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (score < 0)Tools::setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << score << " ";
		Tools::setColor();
		cout << title << endl;
	}
	return 1;
}

void Viewer::Manu()
{
	cout << "please Select the following Options " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout <<"\t"<< list[i] << endl;
	}
	cout << ">>";

}
void Viewer::showUser(const User& u,  vector<Board>& b)
{
	cout <<"Name: " << u.name << endl;
	cout << "Permission Level: ";
	switch (u.Permission_level)
	{
	case 3:
		cout << "Root" << endl;
		break;
	case 2:
		break;
	case 1:
		cout << "Users" << endl;
		break;
	default:
		cout << "Guest" << endl;
		break;
	}
	cout << "Posts:" << endl;
	for (int i = 0; i < u.postsID.size(); i++)
	{
		cout << u.postsID[i] << "\t";
		//read all the board to find the title name
		for (int board = 0; board < b.size(); board++)
		{
			vector<int>::iterator it = find(b[board].docuList.begin(), b[board].docuList.end(), u.postsID[i]);
			if (it != b[board].docuList.end())
			{
				cout << b[board].name << " " << b[board].titleList[distance(b[board].docuList.begin(),it)] << endl;
			}
		}
	}
}