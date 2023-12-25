#include "User.h"
#include"admin.h"
#include <iostream>
using namespace std;
void User::AddingRecord()
{
    string full_name;
    string national_id;
    string password;
    char gender;
    int age;
    string governorate;
    char first_dose;
    char second_dose;


    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, full_name);


    //check unique 

    bool id_len = false, id_flag = false;
    int id;
    cout << "Enter your Egyptian National ID: ";
    do {
        string temp_id;
        cin >> temp_id;
        ID = temp_id;
        id = find(temp_id);
       
        //case of id length and uniquness is valid

        if (temp_id.size() == 14 && id == -1)
        {
            id_len = true;
            national_id = temp_id;
            id_flag = true;
            break;
        }
        //id not unique and id length is valid 
        else if (temp_id.size() == 14 && id != -1)
        {
            cout << "This ID already exist, please review your ID again." << endl;
            id_len = true;
            id_flag = false;


        }
        //id is unique and id length not valid
        else if (temp_id.size() != 14 && id == -1)
        {
            id_flag = true;
            id_len = false;
            cout << " Incorrect ID!" << endl << "ID should be 14 numbers!" << endl;



        }
        //both cases not valid
        else {
            id_len = false;
            id_flag = false;
            cout << "You should enter an ID with 14 digits and unique , Please recheck this and reenter " << endl;


        }

    } while (id_len == false || id_flag == false);



    bool same_pass = false;
    do {
        cout << "Create new password: ";
        string pass_one;
        cin >> pass_one;

        cout << "Reenter password: ";
        string pass_two;
        cin >> pass_two;

        if (pass_one.compare(pass_two) == 0) {
            password = pass_one;
            same_pass = true;
        }
        else {
            cout << "The passwords don't match!" << endl;
        }

    } while (!same_pass);

    cout << "Enter f for female and m for male: ";
    cin >> gender; cout << endl;

    bool legal_age = false;
    int temp_age;
    do {
        cout << "Enter your age: ";
        cin >> temp_age; cout << endl;


        if (temp_age >= 18) {
            age = temp_age;
            legal_age = true;
        }
        else {
            cout << "Come back when you're older! " << endl;
            return;

        }

    } while (!legal_age);


    cout << "Enter your governorate: ";
    cin >> governorate; cout << endl;


    //char check_doses;
    bool first_valid_input = false;
    bool second_valid_input = false;
    bool dose = true;
    bool bothdoses = false;
    do {
        cout << "Enter 'y' if you took the first dose  " << endl;
        cout << "If you didn't enter 'n' : " << endl;
        dose = true;
        bothdoses = false;

        cin >> first_dose;
        cout << endl;

        switch (first_dose)
        {
        case 'y':
            cout << "Enter 'y' if you took the second dose " << endl
                << "If you didn't enter 'n' : " << endl;
            cin >> second_dose;
            cout << endl;
            first_valid_input = true;
            switch (second_dose)
            {
            case 'y':
                bothdoses = true;
                second_valid_input = true;
                break;
            case 'n':
                second_valid_input = true;
                break;
            default:
                cout << "Invalid option ,Please try again!" << endl;
                second_valid_input = false;
                cout << endl;
                break;
            }
            break;
        case'n':
            dose = false;
            first_valid_input = true;
            break;
        default:
            cout << "Invalid option, Please try again!" << endl;
            first_valid_input = false;
            break;
        }
    }

    while (!first_valid_input && !second_valid_input);

    if (dose == true)
        first_dose = '1';
    else if (dose == false)
        first_dose = '0';
    if (bothdoses == true)
        second_dose = '1';
    else if (bothdoses == false)
        second_dose = '0';


    

    citizen temp;
    temp.full_name = full_name, temp.national_id = national_id, temp.password = password, temp.gender = gender
        , temp.age = age, temp.governorate = governorate,
        temp.first_dose = first_dose, temp.second_dose = second_dose;
    Data.push_back(temp);
    
    if (!(temp.first_dose == '1' && second_dose == '1'))
    {

        if (first_dose == '1' && second_dose == '0')
            TypOfDose = "Second";
        else if (first_dose == '0' && second_dose == '0')
            TypOfDose = "First";
        pair<string, string>tempPair;
        tempPair.first = temp.national_id;
        tempPair.second = TypOfDose;
        WaitingList.push(tempPair);
    }


}

void User::RecordToEdit(int ID, int IDinwaiting,citizen tmp) 
{
    string full_name;
    string national_id;
    string password;
    char gender;
    int age;
    string governorate;
    char first_dose=false;
    char second_dose=false;

    bool first_valid_input = false;
    bool second_valid_input = false;
    bool dose = true;
    bool bothdoses = false;
    char again;
    do {
        cout << "please choose what you want to edit : " << endl;
        cout << " 1 for name " << endl;
        cout << " 2 for age " << endl;
        cout << " 3 for password " << endl;
        cout << " 4 for gender " << endl;
        cout << " 5 for governorate " << endl;
        cout << " 6 for the dose you took " << endl;
        bool legal_age = false;
        int temp_age;
        string pass_one;
        string pass_two;
        bool same_pass = false;
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cin.ignore();
            cout << "Enter your name: ";
            getline(cin, full_name);
            cout << endl;
            tmp.full_name = full_name;
            break;
        case 2:

            do {
                cout << "Enter your age: ";
                cin >> temp_age; cout << endl;


                if (temp_age >= 18) {
                    age = temp_age;
                    legal_age = true;
                }
                else {
                    cout << "Come back when you're older! " << endl;
                    return;

                }

            } while (!legal_age);
            tmp.age = age;
            break;
        case 3:

            do {
                cout << "Create new password: ";

                cin >> pass_one;

                cout << "Reenter password: ";

                cin >> pass_two;

                if (pass_one.compare(pass_two) == 0) {
                    password = pass_one;
                    same_pass = true;
                }
                else {
                    cout << "The passwords don't match!" << endl;
                }

            } while (!same_pass);
            tmp.password = password;
            break;
        case 4:
            cout << "Enter f for female and m for male: ";
            cin >> gender; cout << endl;
            tmp.gender = gender;
            break;
        case 5:
            cout << "Enter your governorate: ";
            cin >> governorate; cout << endl;
            tmp.governorate = governorate;
            break;
        case 6:

            do {
                cout << "Enter 'y' if you took the first dose  " << endl;
                cout << "If you didn't enter 'n' : " << endl;
                dose = true;
                bothdoses = false;

                cin >> first_dose;
                cout << endl;

                switch (first_dose)
                {
                case 'y':
                    cout << "Enter 'y' if you took the second dose " << endl
                        << "If you didn't enter 'n' : " << endl;
                    cin >> second_dose;
                    cout << endl;
                    first_valid_input = true;
                    switch (second_dose)
                    {
                    case 'y':
                        bothdoses = true;
                        second_valid_input = true;
                        break;
                    case 'n':
                        second_valid_input = true;
                        break;
                    default:
                        cout << "Invalid option ,Please try again!" << endl;
                        second_valid_input = false;
                        cout << endl;
                        break;
                    }
                    break;
                case'n':
                    dose = false;
                    first_valid_input = true;
                    break;
                default:
                    cout << "Invalid option, Please try again!" << endl;
                    first_valid_input = false;
                    break;
                }
            } while (!first_valid_input && !second_valid_input);

            if (dose == true)
                first_dose = '1';
            else if (dose == false)
                first_dose = '0';
            if (bothdoses == true)
                second_dose = '1';
            else if (bothdoses == false)
                second_dose = '0';

            tmp.first_dose = first_dose;
            tmp.second_dose = second_dose;
            break;


        }
        cout << "please enter y if you want to edit another type of data : ";
        cin >> again;
       // system("cls");
    }while (again == 'y');
    
    Data.insert(Data.begin() + ID, tmp);

    if (!(tmp.first_dose == '1' && second_dose == '1'))
    {

        if (first_dose == '1' && second_dose == '0')
            TypOfDose = "Second";
        else if (first_dose == '0' && second_dose == '0')
            TypOfDose = "First";

        pair<string, string>tempPair;
        tempPair.first = tmp.national_id;
        tempPair.second = TypOfDose;
        AddInWaitingList(IDinwaiting, tempPair);


        //WaitingList.push(tempPair);
    }

}

void User::AddInWaitingList(int id, pair<string, string>x)
{

    queue<pair<string, string>>tmp;
    while (id != -1)
    {
        tmp.push(WaitingList.front());
        WaitingList.pop();
        id--;

    }
    WaitingList.pop();
    tmp.push(x);
    while (!WaitingList.empty())
    {

        tmp.push(WaitingList.front());
        WaitingList.pop();
    }
    WaitingList = tmp;
}

void User::UpdateData() {
    string id;
    int lol;
    int numInWait;
    citizen temp;
    lol = find(ID);
    numInWait = findInWaitingList(ID);
    

    temp.full_name = Data.at(lol).full_name;
    temp.age = Data.at(lol).age;
    temp.national_id= Data.at(lol).national_id;
    temp.governorate= Data.at(lol).governorate;
    temp.gender = Data.at(lol).gender;
    temp.first_dose = Data.at(lol).first_dose;
    temp.second_dose = Data.at(lol).second_dose;
    temp.password= Data.at(lol).password;

    Data.erase(Data.begin() + find(ID));


    ////lazm a3ml erase ml waiting list w a7ot akher update mkano
    RecordToEdit(lol, numInWait,temp);
}

void User::DisplayWaitingListNo(string id)
{
    int UsereInList = 0;
    bool flag = false;
    queue<pair<string, string>> tmp;
    tmp = WaitingList;
    while (!flag)
    {
        if (tmp.front().first == id)
        {
            flag = true;

        }
        else
        {
            UsereInList++;
            tmp.pop();
        }

    }
    cout << " you have to wait : " << UsereInList << endl;

}

void User::userMenu() {
    int choice;
    char check;
    int temp_num;
    int n;

    do {

        cout << "Please choose a number" << endl;
        cout << "1 display record" << endl;
        cout << "2 edit record" << endl;
        cout << "3 delete record" << endl;
        cout << "4 display your number in waiting list" << endl;
        cout << "0 to go back" << endl;
        cin >> choice;

        switch (choice)
        {
        case 0:
            system("cls");
            userAccount();
            break;
        case 1:


            system("CLS");
            displayUserFound(ID);

            break;
        case 2:
            system("cls");
            UpdateData();
            break;
        case 3:
            system("CLS");
            deleteUser(ID);
            break;
        case 4:
            system("cls");
            DisplayWaitingListNo(ID);
            break;
        default:
            break;
        }
        cout << "Please enter y if you want to do another operation" << endl;
        cin >> check;
        system("cls");
    } while (check == 'y');
}

void User::userAccount()
{
    cout << "Please enter 1 to sign up or 2 to log in " << endl;
    int option;
    cin >> option;
    switch (option)
    {
 
    case 1:
        system("cls");
        AddingRecord();
        system("cls");
        userMenu();
        break;
    case 2:
        system("cls");
        login();
        break;
    default:
        break;
    }
}

void User::login() {
    bool checker = false;
    string id, password;
    for (const auto& user : Data) {
        user_map[user.national_id] = user;
    }
    do {
        cout << "Please Enter you National ID: ";
        cin >> id;
        ID = id;
        cout << endl << "Please Enter your password: ";
        cin >> password;
        auto it = user_map.find(id);
        if (it != user_map.end()) {
            if (it->second.password == password) {
                system("cls");
                userMenu();
                // User id and password match
                checker = true;
            }
            else {
                cout << "Wrong password, please try again." << endl;
                // User id and password do not match
                checker = false;
            }

        }
        else if (it == user_map.end()) {
            //id not found
            cout << "National ID doesn't exist. Sign up." << endl;
            AddingRecord();
            checker = true;
        }

    } while (checker == false);
}