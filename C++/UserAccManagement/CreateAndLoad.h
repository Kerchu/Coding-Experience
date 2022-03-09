#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

struct users
{
    int numUser, accType;
    char name[20], address[20];
    float balance;
};
users archive;

void create()//Creation of the file
{
    system("cls");
    ofstream f;
    f.open("users.dat", ios::out | ios::app | ios::binary);
    if (f.fail())
    {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    f.close();
    cout << "File creation finished!!!" << endl;
    system("pause");
    system("cls");
}


void load()//Load of data
{
    system("cls");
    users archive;
    int size = sizeof(users);
    string c;
    ofstream f;
    f.open("users.dat", ios::out | ios::app | ios::binary);
    if (f.fail())
    {
        system("cls");
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    while (1)
    {
        system("cls");
        cout << "Enter ID of the user:" << endl;
        cin >> archive.numUser;
        cin.ignore();
        cout << "Enter Name:" << endl;
        gets_s(archive.name);
        cout << "Enter address:" << endl;
        cin >> archive.address;
        cin.ignore();
        cout << "Enter account type:" << endl;
        cin >> archive.accType;
        if (archive.accType > 4) {//Checks that the acc type is valid
            cout << "Alert!!! Account type not valid" << endl;
            system("pause");
            system("cls");
            break;
        }
        cin.ignore();
        cout << "Enter balance:" << endl;
        cin >> archive.balance;
        cin.ignore();
        cout << endl;
        if (archive.balance > 2000 && archive.accType == 0 || archive.balance > 1500 && archive.accType == 1 || archive.balance > 1200 && archive.accType == 2 || archive.balance > 1000 && archive.accType == 3)
        {
            cout << "ALERT!! Balance is superior than the account type support. Try again" << endl;
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        f.write((char*)&archive, size);
        cout << "Do you want to exit? (Press 'Enter' to exit)" << endl;
        getline(cin, c);
        if (c.empty()) {
            f.close();
            system("cls");
            break;
        }
    }
}