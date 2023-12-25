#include "System.h"
#include"admin.h"
#include"User.h"
#include<fstream>
#include<vector>
#include <queue>
System::System()
{
    load();
}

void System::save()
{
    

    ofstream all_citizens;
    all_citizens.open("VACCINE.txt");
    for (int i = 0; i < Data.size(); i++) {
        all_citizens << Data[i].full_name << ' ' << Data[i].national_id << ' '
            << Data[i].password << ' ' << Data[i].gender << ' '
            << Data[i].age << ' ' << Data[i].governorate << ' '
            << Data[i].first_dose << ' ' << Data[i].second_dose << endl;
    }

    ofstream WaitList;
    WaitList.open("WaitingList.txt");
    while (!WaitingList.empty())
    {
        WaitList << WaitingList.front().first << ' ' << WaitingList.front().second << endl;
        WaitingList.pop();
    }
    /*  for (int i = 0; i < WaitingList.size(); i++) {
          all_citizens <<WaitingList << ' ' << endl;
      }*/

}

void System::load()
{

    ifstream all_citizens;
    all_citizens.open("VACCINE.txt");
    string full_name;
    string national_id;
    string password;
    char gender;
    int age;
    string governorate;
    char first_dose;
    char second_dose;

    while (all_citizens >> full_name >> national_id >> password >> gender
        >> age >> governorate >> first_dose >> second_dose)
    {
        citizen temp;
        temp.full_name = full_name, temp.national_id = national_id, temp.password = password, temp.gender = gender
            , temp.age = age, temp.governorate = governorate,
            temp.first_dose = first_dose, temp.second_dose = second_dose;

        Data.push_back(temp);
       
    }
    ifstream WaitList;
    WaitList.open("WaitingList.txt");
    while (WaitList >> national_id >> TypOfDose)
    {
        pair<string, string>WAITPair;
        WAITPair.first = national_id, WAITPair.second = TypOfDose;
        WaitingList.push(WAITPair);
        //cout << WaitingList.front().second;

    }

    //cout << WaitingList.size();
   /* cout << WaitingList.front().first;
    cout << Data.size();*/

}

int System::find(string Nid)
{
    for (int i = 0; i < Data.size(); i++) {
        FindMap[Data[i].national_id] = i;
    }

    auto it = FindMap.find(Nid);
    if (it != FindMap.end()) {
        // Found the person with the given national id
        return it->second;
    }
    else {
        // Person with the given national id not found
        return -1;
    }

}

int System::findInWaitingList(string id)
{
    int n = -1;
    queue<pair<string, string>>tmp;
    tmp = WaitingList;
    bool flag = false;
    while (!flag)
    {
        if (tmp.front().first == id)
        {
            flag = true;

        }
        else
        {
            n++;
            tmp.pop();
        }

    }

    return n;
}

void System::displayUserFound(string Nid)
{
    system("CLS");
    int userIndex = find(Nid);
    citizen user = Data.at(userIndex);
    cout << "Name: " << user.full_name << endl;
    cout << "National ID: " << user.national_id << endl;
    cout << "Age: " << user.age << endl;
    cout << "Governorate: " << user.governorate << endl;
    cout << "Gender: " << user.gender << endl;
    cout << "Vaccination Status: ";
    if (user.first_dose == '1')
    {
        if (user.second_dose == '1') {
            cout << "Second dose is done." << endl;
        }
        else {
            cout << "First dose is done and in the waiting list of the second dose." << endl;
        }
    }
    else {
        cout << "In the waiting list of the first dose." << endl;
    }
    
}

void  System::deleteUser(string Nid) {
    int index = find(Nid);
    int i = 0;
    for (auto it = Data.begin(); it != Data.end(); it++) {

        if (Data.at(i).national_id == Nid) {
            Data.erase(it);
            break;
        }
        i++;
    }

    //delete in waiting list 

    int id = findInWaitingList(Nid);
    queue<pair<string, string>>tmp;
    while (id != -1)
    {
        tmp.push(WaitingList.front());
        WaitingList.pop();
        id--;

    }
    WaitingList.pop();
    while (!WaitingList.empty())
    {

        tmp.push(WaitingList.front());
        WaitingList.pop();
    }
    WaitingList = tmp;
}

System::~System()
{
    save();
}