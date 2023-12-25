#pragma once
#include <iostream>
#include <string>
#include "System.h"
#include <unordered_map>
using namespace std;

class User : public System
{
public:
	string ID;
	unordered_map<string, citizen>user_map;
public:
	void AddingRecord();
	void RecordToEdit(int ID, int IDinwaiting,citizen tmp);
	void AddInWaitingList(int id, pair<string, string>x);
	void UpdateData();
	void DisplayWaitingListNo(string id);
	void userMenu();
	void userAccount();
	void login();
};

