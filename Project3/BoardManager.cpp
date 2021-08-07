#include"BoardManager.h"

BoardManager::BoardManager()
{
	userList.open("users.txt", ios::app);
	userList.close();
	BoardList.open("boards.txt", ios::app);
	BoardList.close();
	string r = "root";
	string pass = "rootroot";
	User root(r,pass, 3);
	users.push_back(root);
	current_user = -1;

	string password;
	User u;
	
	// read userlist into users
	userList.open("users.txt", ios::in);
	if (!userList.is_open())
	{
		cout << "userList open error"<<endl;
		exit(0);
	}
	while (!userList.eof())
	{
		u.postsID.clear();
		string name;
		userList >> name;
		if (name == "END"||userList.eof())
		{
			break;
		}
		u.name = name;
		u.postsID.clear();
		userList >> password;
		Decrypt(password);
		u.password = password;
		userList >> u.Permission_level;
		string input;
		int num;
		while (!userList.eof())
		{
			userList >> input;
			if (input == "|"||userList.eof())
			{
				break;
			}
			if (Tools::isNumber(input))
			{
				num = stoi(input);
			}
			u.postsID.push_back(num);
		}
		vector<User>::iterator it = find(users.begin(), users.end(), u);
		if (it == users.end())
		{
			users.push_back(u);
		}
		else
		{
			*it = u;
		}
	}
	users;
	userList.close();
	users;
	//read board list into boards

	BoardList.open("boards.txt", ios::in);
	if (!BoardList.is_open())
	{
		cout << "BoardList open error" << endl;
		exit(0);
	}
	documentNumber = 0;
	while (!BoardList.eof())
	{
		Board b;
		b.docuList.clear();
		string name;
		BoardList >> name;
		if (name=="END"||BoardList.eof())
		{
			break;
		}
		b.name = name;
		while (1)
		{
			int num;
			string temp;
			string title;
			BoardList >> temp;
			//BoardList >> title;
			if (temp == "|"||title=="|")
			{
				break;
			}
			if (Tools::isNumber(temp))
			{
				num = stoi(temp);
				if (num > documentNumber)
				{
					documentNumber = num;
					string file = Tools::itos(num) + ".txt";
					document.open(file, ios::in);
					//document >> title;
					Tools::getline(document, title);
					document.close();
				}
			}
			b.docuList.push_back(num);
			b.titleList.push_back(title);
		}
		boards.push_back(b);
	}
	BoardList.close();
}

BoardManager::~BoardManager()
{
	ShutDown();
	userList.close();
	BoardList.close();
	document.close();

	users.clear();
	boards.clear();
}

bool BoardManager::CreateComment(Board& b)
{
	if (current_user < 0)
	{
		cout << "Pls log in first to create your comment." << endl;
		system("pause");
		return 0;
	}
	//system("pause");
	int isCool = 0;
	string num = Tools::itos(currentDoc) + "_comment.txt";
	document.open(num, ios::in);//new file
	string buffer;
	//int runCount = 0;
	
	
	if (document.fail()) goto CREATE_COMMENT_FILE;
	//cout << "Start checking if u have commented" << endl;
	
	while (!document.eof()) {
		//cout << "Running this part for the " << ++runCount << "th time" << endl;
		Tools::getline(document, buffer);
		buffer.erase(0, 2);
		string usertemp;
		while (!buffer.empty()&&buffer[0] != '\t') {
			usertemp.push_back(buffer[0]);
			buffer.erase(0,1);
		}
		if (users[current_user].name == usertemp) {
			isCool = 2;
			break;
		}
	}
	//cout << "Finish checking if u have commented" << endl;
	document.close();

	CREATE_COMMENT_FILE:
	document.open(num, ios::app);
	if (isCool != 2) {
		cout << "Do you like this post? (Enter \"YES\" or \"NO\" to give a rating)" << endl;
		cout << ">>";
		Tools::getline(std::cin, buffer);
		Tools::toUpper(buffer);
		if (buffer == "EXIT")
		{
			return 0;
		}
		if (buffer == "YES")isCool = 1;
		else if (buffer == "NO") isCool = 0;
		else {
			cout << "Unknown Command!" << endl;
			system("pause");
			return 0;
		}
	}
	
	
	//open document
	cout << "Write down what you feel..." << endl;
	cout << ">>";
	Tools::getline(std::cin, buffer);
	
	document << isCool <<"\t"<< users[current_user].name << "\t" << buffer << endl;

	
	document.close();
	if (isCool == 0|| isCool == 1) {
		document.open((Tools::itos(currentDoc) + ".txt"),ios::in);
		string title;
		Tools::getline(document, title);
		string rate;
		while (!title.empty()&&title[0] != '\t') {
			rate.push_back(title[0]);
			title.erase(0, 1);
		}
		if (title.empty()) {
			title = rate;
			rate = "0";
		}
		int score = stoi(rate);
		score += (isCool == 1 ? 1 : -1);
		string content,temp;
		while (Tools::getline(document, temp))content += temp + "\n";
		document.close();
		document.open((Tools::itos(currentDoc) + ".txt"), ios::out);
		document << score << "\t" << title << "\n" << content;
		document.close();
	}
	

	return 1;
}

int BoardManager::ShutDown()
{
	fileOpen(userList, "users", readType::out);
	for (int i = 0; i < users.size(); i++)
	{
		Encryption(users[i].password);
		userList  << users[i] << endl;
	}
	userList << "END";
	userList.close();
	fileOpen(BoardList, "Boards", out);
	for (int i = 0; i < boards.size(); i++)
	{
		BoardList << boards[i] << endl;
	}
	BoardList << "END";
	BoardList.close();
	return 1;
}

bool BoardManager::fileOpen(fstream& fstr, string name,readType select)
{
	if (name.find(".txt")==-1)
	{
		name += ".txt";
	}
	switch (select)
	{
	case 0://read
		fstr.open(name, ios::in);
		break;
	case 1://write
		fstr.open(name, ios::out);
		break;
	case 2://edit
		fstr.open(name, ios::app);
		break;
	case 3://in & out
		fstr.open(name,ios::in | ios::out);
		break;
	case 4://in & append
		fstr.open(name, ios::in || ios::app);
		break;
	default:
		fstr.close();
		break;
	}
	return fstr.is_open();
}

bool BoardManager::Login()
{
	User user;

	cout << "ID: ";
	std::cin >> user.name;
	cout << "Password: ";
	std::cin >> user.password;
	
	for (int i = 0; i < users.size(); i++)
	{
		if (user.Compare(users[i]))
		{
			current_user = i;
			return 1;
		}
	}
	return 0;
}

bool BoardManager::Logout()
{
	cout << "Thanks for watching the board. " << endl;
	cout << "Do you want to login again?(y/n): ";
	char c;
	std::cin >> c;
	current_user = -1;
	if(c=='n')
	{
		current_user = -1;
		//this->ShutDown();
		return 0;
	}
	else
	{
		current_user = -1;
		//this->ShutDown();
		return 1;
	}
}

int BoardManager::signUp()
{
	cout << "Please enter the following detail to creat account" << endl;
	string password1, password2,name;
	cout << "ID: ";
	std::cin >> name;
	
	//check if ID is exist

	for (int i = 0; i < users.size(); i++)
	{
		if (name == users[i].name)
		{
			cout << "The user ID has already exist" << endl;
			return -1;//userid exist
		}
	}

	//check if password is enouth length

	cout << "Password: ";
	std::cin >> password1;
	if (password1.length() < 8)
	{
		cout << "password too short" << endl;
		return 2;//password too short
	}
	cout << "Password again: ";
	std::cin >> password2;

	if (password1 != password2)
	{
		cout << "two password are not the same" << endl;
		return 0;//password not same
	}
	
	
	
	string password = password1;
	//Encryption(password);
	User temp(name, password, user);
	users.push_back(temp);
	cout << "You have successfully creat your account" << endl;
	return 1;
}
void BoardManager::Encryption(string& password)
{
	if (password.length() < 1)
	{
		return;
	}
	char sign = 127;
	if (*(password.end()-1) != 127)
	{
		for (int i = 0; i < password.length(); i++)
		{
			password[i]++;
		}
		password += sign;
	}
}
void BoardManager::Decrypt(string& password)
{
	if (password.length() < 8)
	{
		return;
	}
	char sign = 127;
	if (*(password.end()-1) == 127)
	{
		for (int i = 0; i < password.length(); i++)
		{
			password[i]--;
		}
		password.erase(password.end()-1);
	}
}


bool BoardManager::DeleteBoard()
{
	//viewer.showBoardList(boards);
	system("cls");
	cout << "-1\tEXIT" << endl<<endl;
	for (int i=0;i<boards.size();i++)
	{
		
		cout << i + 1 << "\t" << boards[i].name << endl;
	}
	if (current_user != 0)
	{
		cout << "only root can delete board" << endl;
		system("pause");
		return 0;
	}
	cout << "please enter the number of the board(\"-1\" to EXIT)" << endl;
	cout << ">>";
	int number;
	cin >> number;
	if (number == -1)
	{
		return 0;
	}
	if (number > boards.size()||number<=0)
	{
		while (number <= boards.size()&&number>0)
		{
			viewer.showBoardList(boards);
			cout << "unable to find the board" << endl;
			system("pause");
			/*cout << "please enter the number of the board" << endl;
			cout << ">>";
			cin >> number;*/
			return 0;
		}
	}
	number--;
	for (int i = 0; i < boards[number].docuList.size(); i++)
	{
		DeleteDocument(boards[number].docuList[i]);
	}
	boards.erase(boards.begin() + number);
	return 1;
}
bool BoardManager::DeleteDocument(int number)
{
	vector<int>::iterator it;
	for (int i = 0; i < users.size(); i++)
	{
		it = find(users[i].postsID.begin(), users[i].postsID.end(), number);
		if (it != users[i].postsID.end())
		{
			users[i].postsID.erase(it);
			return 1;
		}
	}
	return 0;
}
bool BoardManager::DeleteDocument(Board& b)
{
	//viewer.showDocumentList(b);
	system("cls");
	if (current_user < 0)
	{
		cout << "Guess are not allow to Delete document" << endl;
		system("pause");
		return 0;
	}
	cout << "-1\tEXIT" << endl << endl;
	for (int i = 0; i < b.docuList.size(); i++)
	{
		cout << i + 1 << "\t" << b.titleList[i] << endl;
	}
	cout << "please enter the Document number to delete(\"-1\" to EXIT)" << endl;
	cout << ">>";
	int num;
	cin >> num;
	if (num == -1)
	{
		return 0;
	}
	while(num <= 0 || num > b.docuList.size())
	{
		cout << "document not found...." << endl;
		system("pause");
		return 0;
	}
	int docunum = b.docuList[num - 1];
	//find the id in current_user
	vector<int>::iterator it;
	it = find(users[current_user].postsID.begin(), users[current_user].postsID.end(), docunum);
	//not root and the post is not in the postsid
	if (current_user != 0)
	{
		if (it == users[current_user].postsID.end())
		{
			cout << "You can only delete your posts" << endl;
			system("pause");
			return 0;
		}
	}
	//remove document from user and board
	string file = Tools::itos(docunum) + ".txt";
	users[current_user].postsID.erase(it);
	std::remove(file.c_str());
	b.docuList.erase(b.docuList.begin() + num - 1);
	b.titleList.erase(b.titleList.begin() + num - 1);
	return 1;
}


bool BoardManager::CreatBoard()
{
	//current_user = 0;
	if (current_user != 0)
	{
		cout << "only root can creat board" << endl;
		system("pause");
		return 0;
	}

	string boardName;
	cout << "Please enter a title of a board to creat a board" << endl;
	cout << ">>";
	std::cin >> boardName;
	while (boardName == "creat" || boardName == "Creat")
	{
		cout << "\"Creat\" or \"creat\" can't be a board name " << endl;
		cout << "Please enter a new title of a board to creat a board" << endl;
		std::cin >> boardName;
	}
	for (int i = 0; i < boards.size(); i++)
	{
		if (boards[i].name == boardName)
		{
			cout << "board already exist\n";
			system("pause");
			return 0;
		}
	}
	Board b(boardName);
	boards.push_back(b);
	return 1;
}
bool BoardManager::CreatDocument(Board& b)
{

	//if (users[current_user].Permission_level < 0)
	if(current_user<0)
	{
		cout << "guest are unable to creat a document" << endl;
		system("pause");
		return 0;
	}
	//system("pause");
	string title;
		//read title
	cout << "please enter the title of the document (\"EXIT\" to quit)" << endl;
	cout << ">>";
	Tools::getline(std::cin, title);
	if (title == "EXIT")
	{
		return 0;
	}
	//title can't be creat
	/*while (title == "creat" || title == "Creat")
	{
		cout << "\"Creat\" or \"creat\" can't be a board name " << endl;
		cout << "Please enter a new title of a board to creat a board" << endl;
		cout << ">>";
		Tools::getline(std::cin, title);
	}*/
	//open document
	documentNumber++;
	string num = Tools::itos(documentNumber) + ".txt";
	document.open(num, ios::out);//open document file
	document << title << endl << endl;

	cout << "Please enter text(\"EXIT\" to quit)" << endl;
	cout << ">>";
	string sentence;
	while (Tools::getline(std::cin, sentence))
	{
		if (sentence == "EXIT")
		{
			break;
		}
		document << sentence<<endl;
		cout << ">>";
	}
	b.titleList.push_back(title);
	b.docuList.push_back(documentNumber);
	users[current_user].postsID.push_back(documentNumber);
	vector<int>::iterator it = find(users[current_user].postsID.begin(), users[current_user].postsID.end(), 0);
	if (it != users[current_user].postsID.end())
	{
		users[current_user].postsID.erase(it);
	}
	document.close();
	return 1;
}



int BoardManager::SelectBoard()
{
	viewer.showBoardList(boards);
	cout << endl;
	int number;
	cout << "please enter the number of a board"<<endl;
	cout << ">>";
	cin >> number;
	cin.ignore();
	if (number == -3)
	{
		UserInformation();
		return 0;
	}
	if (number == -2)
	{
		DeleteBoard();
		return 0;//delete
	}
	if (number == -1)
	{
		return -1;//exit
	}
	if (number == 0)
	{
		CreatBoard();//creat
		return 0;
	}
	if(number>boards.size()||number==0)
	{
		cout << "board isn't exist, please select again" << endl;
		system("pause");
		return -2;
	}
	return number;
}
int BoardManager::SelectDocument( Board& b)
{
	viewer.showDocumentList(b);
	cout << endl;
	string title;
	cout << "please select a number of the document" << endl;
	cout << ">>";
	int number;
	cin >> number;
	if (number == -2)
	{
		DeleteDocument(b);
		return 0;
	}
	if (number == -1)
	{
		return -1;
	}
	if (number == 0)
	{
		CreatDocument(b);
		return 0;
	}
	if (number>b.docuList.size()||number==0)
	{
		cout << "Document are not exist please select again" << endl;
		system("pause");
		return -2;
	}
	currentDoc = number;
	return b.docuList[number-1];
}
void BoardManager::getCommand()
{
	bool relog=1;
	while (relog)
	{
		string command;//get the command of user
		//login or signup 
		bool flag = 0;
		int count = 0;

		//the login or signup section
		//***********************************
		while (flag == 0)
		{
			count = 0;
			system("cls");
			cout << "please Enter  \"Login\"  or  \"SignUp\" or \"Guest\" (\"EXIT\" to quit): " << endl;
			cout << ">>";
			std::cin >> command;
			system("cls");
			Tools::toLower(command);
			if (command == "login")
			{
				flag = Login();
				while (flag == 0 && count < 2)//login error
				{
					system("cls");
					cout << "ID or Password Error.\nPlease Retry" << endl;
					flag = Login();
					count++;
				}
				if (flag)
				{
					continue;
				}
				if (count == 2)
				{
					cout << "You Have try 3 times, Do you want to signup ? (y/n)" << endl;
					char c;
					cin >> c;
					if (c == 'y')
					{
						command = "signup";
					}
					else
					{
						continue;
					}
				}
				count = 0;
				//continue;
			}
			if (command == "signup")
			{
				system("cls");
				int error;
				error = signUp();
				while (error != 1)
				{
					error = signUp();
				}
				continue;
			}
			if (command == "exit")
			{
				ShutDown();
				exit(0);
			}
			if (command == "guest")
			{
				current_user = -1;
				break;
			}
			else
			{
				cout << "command error" << endl;
				system("pause");
			}
		}

		//current_user = 0;
		flag = 1;
		//*********************************

		//read command
		//*********************************
		bool recommand = 1;//re select board
		bool redocu = 1;//re select document
		while (recommand)
		{
			int b;
			b=SelectBoard();
			if (b == 0)//creat board or delete board
			{
				continue;
			}
			if (b == -1)//exit board manu
			{
				relog=Logout();
				break;
			}
			if (b == -2)//reselect board
			{
				continue;
			}
			b--;
			redocu = 1;
			while (redocu)
			{
				int docu = SelectDocument(boards[b]);
				if (docu == 0)
				{
					continue;
				}
				if (docu == -1)
				{
					redocu = 0;
					break;
				}
				//mah edit start from here
				while (true) {
					viewer.showDocument(docu);
					string commentCommand;
					reCommentCommand:
						cout << ">>";
						cin >> commentCommand;
						if (commentCommand == "-1")break;
						else if (current_user < 0)
						{
							cout << "only users can creat comments" << endl;
							system("pause");
							continue;
						}
						else if (commentCommand != "0")
						{
							cout << "Unknown command! Pls enter the command, again.\n";
							//continue;
							goto reCommentCommand;
						}
						else
						{
							CreateComment(boards[b]);
						}
				}
			}
		}
	}
}

bool BoardManager::UserInformation()
{
	if (current_user < 0)
	{
		cout << "Guest has no user information" << endl;
		system("pause");
		return 0;
	}
	viewer.showUser(users[current_user],boards);
	cout << endl;
	cout << "Please enter the document number to Edit or -1 to EXIT" << endl;
	cout << ">>";
	int select;
	cin >> select;
	if (select == -1)
	{
		return 0;
	}
	string name = Tools::itos(select)+".txt";
	viewer.showDocument(select);
	
	string title;
	cout << "Please enter your Title\"EXIT\" to quit(you can copy the title on top and edit it)" << endl;
	cout << ">>";
	Tools::getline(cin, title);
	if (title == "EXIT")
	{
		return 0;
	}
	document.open(name, ios::out);
	document << title << endl;
	cout << "Please enter your document(\"EXIT\" to quit)" << endl;
	string text;
	cout << ">>";
	getline(cin, text);
	while (text != "EXIT")
	{
		cout << ">>";
		document << text;
		getline(cin, text);
	}
	document.close();
	for (int i = 0; i < boards.size(); i++)
	{
		vector<int>::iterator it = find(boards[i].docuList.begin(), boards[i].docuList.end(), select);
		if (it != boards[i].docuList.end())
		{
			boards[i].titleList[distance(boards[i].docuList.begin(), it)] = title;
			break;
		}
	}
	return 1;
}