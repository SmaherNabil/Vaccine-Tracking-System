#pragma once
#include <queue>
#include<string>
#include<iostream>
#include<unordered_map>
using namespace std;

struct citizen
{
    string full_name;
    string national_id;
    string password;
    char gender;
    int age;
    string governorate;
    char first_dose;
    char second_dose;
};

class System
{
public:
	vector<citizen>Data;
	queue<pair <string, string>>WaitingList;
	string TypOfDose;
    unordered_map<string, int>FindMap;
public:
    System();
    void save();
    void load();
    int find(string Nid);
    int findInWaitingList(string id);
    void displayUserFound(string Nid);
    void  deleteUser(string Nid);
    ~System();
};

