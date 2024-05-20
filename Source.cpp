#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<string>
#include "Classes.h"

using namespace std;

void Menu();


int main() {
    
	Menu();


}





void Menu() {
    LinkedAccounts file; 
    char key;
    COORD c;
    c.X = 45;
    c.Y = 2;

    do {
        system("CLS");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        cout << "Welcome to Online Transaction System"<< endl;
        cout << "\t\t\t\t\t______________________________________________\n\n" << endl;
        cout << "Press 0 to Exit the Program" << endl;
        cout << "Press 1 to Open a New Account" << endl;
        cout << "Press 2 to retreive all accounts" << endl;
        cout << "Press 3 to deposit to your Account" << endl;
        cout << "Press 4 to go to Transactions " << endl;
        cin >> key;

        switch (key) {
        case '0':
            cout << "Thanks for using this program." << endl;
            file.Write_files();
            system("PAUSE");
            break;
        case '1':
        {
            int id = -1;
            string input;
            bool flag = false;
            cin.ignore();
            cout << "Input Account Title : ";
            getline(cin, input);
            while (!flag) {
                cout << "\nInput Your Account ID (3 digits) : ";
                cin >> id;
                cin.ignore();
                if (id >= 000 && id <= 999)
                {
                    flag = true;
                }
                else {
                    cout << "\nInput only 3 digit number try again!! " << endl;
                }

            }
            file.Add_Account(input, id);
            break;
        }
        case '2':
        {
            system("ClS");
            cout << "Retreiving Data Please Wait..." << endl;
            LinkedAccounts* retreived = file.Retreive_Accounts();
            cout << "\nDisplaying Data Please wait" << endl;
            retreived->Display_Accounts();
            Sleep(4000);

            break;
        }
        case '3':
            
            file.Account_Deposit();
            Sleep(4000);
            break;
        case '4':
            file.Transaction_Menu();
            Sleep(4000);
            break;
        }

       
        cin.ignore();
    } while (key != '0');
}