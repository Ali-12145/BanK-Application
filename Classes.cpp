#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<sstream>
#include "Classes.h"


using namespace std;

BankAccount::BankAccount(string s,int id){
    account_title = s;
    balance = 1000;
    ID = id;
}

void BankAccount::Set_Next(BankAccount* n){
    next = n;
}

void BankAccount::Set_prev(BankAccount* p){
    prev = p;
}

BankAccount* BankAccount::Get_next(){
    return next;
}

BankAccount* BankAccount::Get_prev(){
    return prev;
}

void BankAccount::Set_Balance(double b) {
    balance = b;
}

void BankAccount::Deposit_Balance(double bal){
    balance += bal;
}

double BankAccount::Get_balance(){
    return balance;
}

int BankAccount::Get_id(){
    return ID;
}

string BankAccount::Get_title(){
    return account_title;
}



void BankAccount::Transfer_Transaction(double amount) {
    balance -= amount;
}

void BankAccount::Incoming_Transaction(double am) {
    balance += am;
}






//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------


LinkedAccounts::LinkedAccounts(){
    head = tail = NULL;
}

void LinkedAccounts::Add_Account(string t, int id ){
    bool flag = Search_Linked_Accounts(id);
    if (!flag) {
        BankAccount* b = new BankAccount(t, id);
        if (head == NULL) {
            head = tail = b;

        }
        else {
            tail->Set_Next(b);
            b->Set_prev(tail);
            tail = b;
        }
        Write_files();
        cout << "\nAccount Added to Account List" << endl;
        cin.ignore();
        return;
    }
    else {
        cout << "Account with this id already exists" << endl;
        cin.ignore();
        Sleep(2000);
        return;
    }
 }


bool LinkedAccounts::Search_Linked_Accounts(int id) {
    LinkedAccounts* accounts = Retreive_Accounts();
    BankAccount* ptr = accounts->head;


        while (ptr != NULL && ptr->Get_id() != id) {
            ptr = ptr->Get_next();

        }
        if (ptr!= NULL && ptr->Get_id() == id) {
            return true;
        }
        else return false;
 }



void LinkedAccounts::Write_files(){
    ofstream write;

    write.open("Accounts.csv",ios::app);
    BankAccount *ptr = head;
    while(ptr != NULL){
        if (!Search_Linked_Accounts(ptr->Get_id())) {

        write << ptr->Get_title() << "," << ptr->Get_id() << ",";
        write << ptr->Get_balance()<<endl;
        ptr = ptr->Get_next(); 
        }
        else
         ptr = ptr->Get_next();
    }
    write.close();

}

void LinkedAccounts::Retreive_Add(string s, int d) {
    BankAccount* p = new BankAccount(s, d);
    if (head == NULL) {
        head = tail = p;
    }
    else {
        tail->Set_Next(p);
        p->Set_prev(p);
        tail = p;
    }


}

BankAccount* LinkedAccounts::Search_Account(int id) {
    LinkedAccounts* accounts = Retreive_Accounts();
    BankAccount* ptr = accounts->head;
    BankAccount* result = NULL;

    while (ptr != NULL && ptr->Get_id() != id) {
        ptr = ptr->Get_next();

    }
    if (ptr != NULL && ptr->Get_id() == id) {
        result = ptr;
    }
    
    return result;
}

LinkedAccounts* LinkedAccounts::Retreive_Accounts() {
    BlockInput(true);
    ifstream read("Accounts.csv");
    string line;
    cout << "\nRetreiving Data...." << endl;
    LinkedAccounts* retreived = new LinkedAccounts();
    if (read.is_open()) {
        cout << "\n";
        while (getline(read, line)) {
            string name;
            string id;
            string bal;
            
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, bal,'\n');

            retreived->Retreive_Add(name, stoi(id));
            BankAccount* ptr = retreived->tail;
            ptr->Set_Balance(stod(bal));
        }
    }
    read.close();
    BlockInput(false);
    return retreived;
}

void LinkedAccounts::Display_Accounts() {
    BlockInput(true);
    BankAccount* ptr = head;

    while (ptr != NULL) {
        cout << "\nAccount ID : " << ptr->Get_id() << endl;
        cout << "Account Title : " << ptr->Get_title() << endl;
        cout << "Balance : " << ptr->Get_balance() << endl;
        ptr = ptr->Get_next();
    }

    BlockInput(false);
}






void LinkedAccounts::Account_Deposit() {
    int key;
    cout << "Please Input your Account ID ";
    cin >> key;

    BankAccount* acc = Search_Account(key);
    bool flag = false;
    if (acc) {
        cout << "\nAccount Found!" << endl;
        Sleep(500);

        while (!flag) {
            system("CLS");
            double amount;
            cout << "\t\nPlease Enter amount you want to deposit to Account ID : " << acc->Get_id();
            cout << "\n_________________________________________________________________________" << endl;
            cout << "\n\n Amount : ";
            cin >> amount;

            if (amount > 0) {
                acc->Deposit_Balance(amount);
                flag = true;
                cout << "New Account Balance: " << acc->Get_balance() << endl;
                Update_balance_file(acc);
            }
            else {
                cout << "Input a positive number" << endl;
            }

        }

    }
    else cout << "Account Not Found !" << endl;

}

void LinkedAccounts::Update_file(BankAccount* to , BankAccount* from) {
    BlockInput(true);
    LinkedAccounts* newlist = Retreive_Accounts();
    BankAccount* toptr = newlist->Search_Node(to->Get_id());
    BankAccount* fromptr = newlist->Search_Node(from->Get_id());

    toptr->Set_Balance(to->Get_balance());
    fromptr->Set_Balance(from->Get_balance());

    BankAccount* tempptr = newlist->head;
    ofstream write("Accounts.csv", ios::out);

    while (tempptr != NULL) {
        write << tempptr->Get_title() << "," << tempptr->Get_id() << ",";
        write << tempptr->Get_balance() << endl;
        tempptr = tempptr->Get_next();

    }
    write.close();
    BlockInput(false);
}

BankAccount* LinkedAccounts::Search_Node(int id) {
    BlockInput(true);
    BankAccount* ptr = head;
    BankAccount* result = NULL;

    while (ptr && ptr->Get_id() != id) {
        ptr = ptr->Get_next();
    }

    if (ptr) {
        result = ptr;
    }
    BlockInput(false);
    return result;


}



void LinkedAccounts::Update_balance_file(BankAccount* acc) {
    BlockInput(true);
    LinkedAccounts* newlist = Retreive_Accounts();
    BankAccount* ptr = newlist->Search_Node(acc->Get_id());

    if (ptr) {
        ptr->Set_Balance(acc->Get_balance());
        ofstream write;

        write.open("Accounts.csv", ios::out);
        BankAccount* ptr1 = newlist->head;
        while (ptr1 != NULL) {
                write << ptr1->Get_title() << "," << ptr1->Get_id() << ",";
                write << ptr1->Get_balance() << endl;
                ptr1 = ptr1->Get_next();
            
        }
        write.close();

    }
    BlockInput(false);
}

void LinkedAccounts::Payable_transaction() {
    system("CLS");
    int from_id;
    int to_id;
    double amount;
    cout << "\t\t\t\t\tWelcome to Online Transfer System" << endl;
    cout << "\t\n\nHere you can transfer funds between valid accounts\n" << endl;
    cout << "\n\nInput Your ID : " ;
    cin >> from_id;
    cout << "\nInput the receivable ID : ";
    cin >> to_id;
    cout << "\nEnter the amount you want to Transfer : " ;
    cin >> amount;

    BankAccount* ptrto = Search_Account(to_id);
    BankAccount* ptrfrom = Search_Account(from_id);

    if (ptrfrom != NULL && ptrto != NULL) {
        if (ptrfrom->Get_balance() >= amount) {
            ptrfrom->Transfer_Transaction(amount);
            ptrto->Incoming_Transaction(amount);
            Update_file(ptrfrom, ptrto);

            cout << "Transaction Successfull!" << endl;
            cout << "New Balance of ID: ";
            cout << ptrfrom->Get_id();
            cout << "\n" << ptrfrom->Get_balance() << endl;

            cout << "New Balance of ID: ";
            cout << ptrto->Get_id();
            cout << "\n" << ptrto->Get_balance() << endl;
            return;
        }
        else {
            cout << "Insufficient Funds! " << endl;
            cout << "______________________" << endl;

            Sleep(3000);
            return;
    }
    }
    else if (ptrfrom == NULL){
        cout << "Your Account ID is not found in Database" << endl;
        cout << "Redirecting to Main Menu....." << endl;
        Sleep(4000);
        system("CLS");
    }
    else {
        cout << "Receivable ID not found in Database" << endl;
        cout << "Redirecting to Main Menu....." << endl;
        Sleep(4000);
        system("CLS");
    }
}





void LinkedAccounts::Transaction_Menu() {
    int key;
    while (1) {
        system("CLS");
        cout << "\t\t\t\t\tWelcome to Transactions" << endl;
        cout << "\t\t\t\t\t__________________________" << endl;
        cout << "Press 1 to go to Inter Account Transfer" << endl;
        cout << "Press 0 to exit Transactions" << endl;
        cin >> key;
        if (key == 1) {
            Payable_transaction();
            break;
        }
        else if (key == 0) {
            return;
        }
        else {
            cout << "\nInvalid Input" << endl;
            Sleep(2000);
        }
    }
}