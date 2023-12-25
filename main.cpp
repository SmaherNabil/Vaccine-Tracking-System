#include <iostream>
#include <fstream>
#include "System.h"
#include "User.h"
#include <vector>
#include "admin.h"
#include <windows.h>
#include <cwchar>
using namespace std;

int main()
{

    system("Color F5");
    CONSOLE_FONT_INFOEX cfi;
    //cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 24;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    //wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


    cout << "            ________________________________________________________________________________________" << endl;
    cout << "            __________________________________________WELCOME_______________________________________" << endl;
    cout << "            ________________________________________________________________________________________" << endl<<endl;

    int role;
    User u;
    admin a;
    cout << "                                             Press 1 if you are a user." << endl
        << "                                             Press 2 if you are an admin." << endl;
    cin >> role;

    //try recusrion
    while (true) {
        if (role == 1) {

            u.userAccount();
            break;
        }
        else if (role == 2) {

            a.signIn();
            break;
        }
        else {
            cout << "Re-enter correct number." << endl;
            cin >> role;
        }
    }

    return 0;
}