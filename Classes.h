#pragma once

#include<iostream>
using namespace std;

class BankAccount;
class LinkedAccounts;


class BankAccount{
    string account_title;
    int ID;
    double balance;
    BankAccount *next;
    BankAccount *prev;

public:
        BankAccount(string,int );
        void Set_Next(BankAccount *);
        void Set_prev(BankAccount *);
        BankAccount *Get_next();
        BankAccount *Get_prev();

        string Get_title();
        void Transfer_Transaction(double amount);
        void Incoming_Transaction(double amount);
        int Get_id();
        void Set_Balance(double);
        void Deposit_Balance(double num);
        double Get_balance();
};








class LinkedAccounts{
    BankAccount *head;
    BankAccount *tail;
    
    public:
        LinkedAccounts();

        void Add_Account(string,int);
        void Retreive_Add(string, int);
        void Write_files();
        LinkedAccounts* Retreive_Accounts();
        //void Retreived_write_file();
        void Display_Accounts();
        BankAccount* Search_Node(int id);
        void Transactions();
        void Transaction_Menu();

        void Payable_transaction();
        BankAccount* Search_Account(int id);
        void Account_Deposit();
        void Update_file(BankAccount* , BankAccount*);

        void Update_balance_file(BankAccount*);

        bool Search_Linked_Accounts(int id);

};