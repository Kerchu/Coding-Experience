#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include "CreateAndLoad.h"//Self-made library

using namespace std;

void show()//Shows all the saved accounts
{
    system("cls");
    users archive;
    int size = sizeof(users);
    ifstream in;
    in.open("users.dat", ios::binary);
    if (in.fail())
    {
        system("cls");
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    in.read((char*)&archive, size);
    while (!in.eof())
    {
        cout << " User      --> " << archive.numUser << endl;
        cout << " Name      --> " << archive.name << endl;
        cout << " Address   --> " << archive.address << endl;
        cout << " Balance   --> " << archive.balance << endl;
        cout << " Account   --> " << archive.accType << endl;
        cout << "----------------------------------" << endl;
        in.read((char*)&archive, size);
    }
    in.close();
    system("pause");
    system("cls");
}

void consult()//Checks for a specific account
{
    system("cls");
    users archive; 
    int size = sizeof(users);
    ifstream in;
    in.open("users.dat", ios::binary);
    if (in.fail())
    {
        system("cls");
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    in.read((char*)&archive, size);
    cout << "Enter acc's ID to check:" << endl;
    int cod;
    cin >> cod;
    int exist = 0;
    while (!in.eof())
    {
        if (cod == archive.numUser)
        {
            cout << "--------------------------------------------" << endl;
            cout << "User                 --> " << archive.numUser << endl;
            cout << "Name                 --> " << archive.name << endl;
            cout << "Address              --> " << archive.address << endl;
            cout << "Balance              --> " << archive.balance << endl;
            cout << "Account              --> " << archive.accType << endl;
            cout << "--------------------------------------------" << endl;
            exist = 1;
            break;
        }
        in.read((char*)&archive, size);
    }
    if (exist == 0) 
    {
        system("cls");
        cout << "There's not a user with that ID" << endl;
        cout << endl;
    }
    in.close();
    system("pause");
    system("cls");
}
void mod()//Modify a user balance
{
    system("cls");
    fstream arch;
    int pos = 0;
    arch.open("users.dat", ios::in | ios::out | ios::binary);
    if (arch.fail()) {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    cout << "Enter acc's ID to modify:" << endl;
    int cod, exist = 0;
    cin >> cod;
    users archive;
    pos = sizeof(users);
    arch.read((char*)&archive, sizeof(users));

    while (!arch.eof()) {
        if (archive.numUser == cod)
        {
            cout << "------------------------ " << endl;
            cout << "User                 --> " << archive.numUser << endl;
            cout << "Name                 --> " << archive.name << endl;
            cout << "Address              --> " << archive.address << endl;
            cout << "Balance              --> " << archive.balance << endl;
            cout << "Account              --> " << archive.accType << endl;
            cout << "------------------------ " << endl;
            cout << "Enter new balance    --> " << endl;
            cin >> archive.balance;
            if (archive.balance > 2000 && archive.accType == 0 || archive.balance > 1500 && archive.accType == 1 || archive.balance > 1200 && archive.accType == 2 || archive.balance > 1000 && archive.accType == 3)
            {
                cout << "ALERT!! Balance is superior than the account type support. Try again" << endl;
                cout << endl;
                system("pause");
                system("cls");
                break;
            }
            pos = sizeof(users);
            arch.seekg(pos, ios::beg);
            arch.write((char*)&archive, sizeof(users));
            cout << endl;
            cout << "Balance of the selected account has been modified.";
            exist = 1;
            break;
        }
        arch.read((char*)&archive, sizeof(users));
    }
    if (exist == 0) 
    {
        system("cls");
        cout << "There's not a user with that ID" << endl;
        cout << endl;
    }
    arch.close();
    system("pause");
    system("cls");
}

void del()//Deletes a user
{
    system("cls");
    fstream arch; ofstream arch1; int pos = 0;
    arch.open("users.dat", ios::in | ios::out | ios::binary);
    if (arch.fail()) {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        system("pause"); exit(1);
    }
    else {
        string c;
        cout << "Are you sure you want to delete a user's account? (Press 'N' to cancel)" << endl;
        getline(cin, c);
        if (c != "N" && c != "n") 
        {
            system("cls");
            long size = sizeof(users); users archive; int pos = 0;
            arch1.open("usersB.dat", ios::app | ios::out | ios::binary);
            if (arch1.fail()) {
                cout << "Error while opening temporary file" << endl;
                system("pause");
                arch.close();
            }
            else {
                while (1)
                {
                    int x;
                    cout << "Enter user's ID: ";
                    cin >> x;
                    cin.ignore();
                    arch.read((char*)&archive, sizeof(users));
                    while (!arch.eof()) {
                        if (archive.numUser != x) {
                            arch1.write((char*)&archive, sizeof(users));
                        }
                        else {
                            cout << "You have deleted the next user permanently." << endl;
                            cout << " " << archive.numUser << " " << archive.name << " " << archive.address << " " << archive.balance << " " << archive.accType << endl;
                            system("pause");
                        }
                        system("cls");
                        arch.read((char*)&archive, sizeof(users));
                    }
                    cout << "Delete finished. Press 'Enter' to exit" << endl;
                    getline(cin, c);
                    if (c.empty()) {
                        arch.close(); arch1.close();
                        remove("users.dat");
                        if (rename("usersB.dat", "users.dat"))
                        {
                            perror("ERROR");
                            system("pause");
                        }
                        break;
                    }
                }
            }
        }
    }
    system("cls");
}

void cal() //Calculates interests
{
    system("cls");
    fstream arch, arch1;
    int pos = 0;
    users archive;
    arch.open("users.dat", ios::in | ios::out | ios::binary);
    arch1.open("usersB.dat", ios::app | ios::out | ios::binary);
    if (arch.fail()) 
    {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        system("pause");
        exit(1);
    }
    arch.read((char*)&archive, sizeof(users));
    while (!arch.eof() && pos != sizeof(users))
    {
        if (archive.accType == 0)
        {
            if (archive.balance <= 500)
            {
                archive.balance = archive.balance - archive.balance * 20 / 100;
                cout << "ALERT!!! ACCOUNT " << archive.numUser << " TYPE " << archive.accType << " HAS AN INFERIOR OR EQUAL BALANCE THAN 500" << endl;
                cout << endl;
            }
            else {
                archive.balance = archive.balance - archive.balance * 10 / 100;
            }
        }
        if (archive.accType == 1)
        {
            archive.balance = archive.balance - archive.balance * 7 / 100;
        }
        if (archive.accType == 2)
        {
            archive.balance = archive.balance - archive.balance * 4 / 100;
        }
        if (archive.balance == 3)
        {
            archive.balance = archive.balance - archive.balance * 3 / 100;
        }
        arch1.write((char*)&archive, sizeof(users));
        arch.read((char*)&archive, sizeof(users));
        pos++;
    }

    arch.close(), arch1.close();
    remove("users.dat");
    if (rename("usersB.dat", "users.dat"))
    {
        perror("ERROR");
    }
    cout << "Calculation finished!!!" << endl;
    system("pause");
    system("cls");
}

void seek() //Checks on the acc with less balance
{
    float d = 0, y = 2500;
    float x = 2000;
    int i, a = 0;
    string c, b;

    ifstream in;
    system("cls");
    users archive;
    int size = sizeof(users);
    in.open("users.dat", ios::in | ios::out | ios::binary);
    cout << "Enter account type to search" << endl;
    cin >> i;
    in.read((char*)&archive, size);
    while (!in.eof()) 
    {
        if (archive.accType = i && archive.balance < x)
        {
            x = archive.balance;
            if (x < y)
            {
                a = archive.numUser;
                b = archive.name;
                c = archive.address;
                d = archive.balance;
                y = x;
            }
        }
        in.read((char*)&archive, size);
    }
    cout << "--------------------------------------------" << endl;
    cout << "User                 --> " << a << endl;
    cout << "Name                 --> " << b << endl;
    cout << "Address              --> " << c << endl;
    cout << "Balance              --> " << d << endl;
    cout << "--------------------------------------------" << endl;
    system("pause");
    system("cls");
    in.close();
}

void bal() //Gives a total of balance per type of account
{
    float a = 0, b = 0, c = 0, d = 0;
    ifstream in;
    system("cls");
    users archive;
    int size = sizeof(users);
    in.open("users.dat", ios::in | ios::out | ios::binary);
    in.read((char*)&archive, size);
    while (!in.eof())
    {
        if (archive.accType == 0)
        {
            a = archive.balance + a;
        }
        if (archive.accType == 1)
        {
            b = archive.balance + b;
        }
        if (archive.accType == 2)
        {
            c = archive.balance + c;
        }
        if (archive.accType == 3)
        {
            d = archive.balance + d;
        }
        in.read((char*)&archive, size);
    }
    cout << "--------------------------------------------" << endl;
    cout << "Account 0              --> " << a << endl;
    cout << "Account 1              --> " << b << endl;
    cout << "Account 2              --> " << c << endl;
    cout << "Account 3              --> " << d << endl;
    cout << "--------------------------------------------" << endl;
    system("pause");
    system("cls");
    in.close();
}

int main()// Menu
{
    int size = sizeof(users);
    int input;
    do {
        cout << "----------------------------------------------" << endl;
        cout << "[1]  - Create the file" << endl;
        cout << "[2]  - Load new users" << endl;
        cout << "[3]  - Show saved users" << endl;
        cout << "[4]  - Check on a specific user" << endl;
        cout << "[5]  - Modify a user" << endl;
        cout << "[6]  - Delete a user" << endl;
        cout << "[7]  - Calculate interests" << endl;
        cout << "[8]  - Check type of account with less balance" << endl;
        cout << "[9]  - Show total per type of account" << endl;
        cout << "[10] - Exit program" << endl;
        cout << "----------------------------------------------" << endl;
        cin >> input;
        cin.ignore();
        switch (input) {
        case 1: create();
            break;
        case 2: load();
            break;
        case 3: show();
            break;
        case 4: consult();
            break;
        case 5: mod();
            break;
        case 6: del();
            break;
        case 7: cal();
            break;
        case 8: seek();
            break;
        case 9: bal();
            break;
        case 10: cout << "Closing the program" << endl;
            break;
        default: cout << "Not valid input" << endl; system("pause"); system("cls");
        }
    } while (input != 10);
    return 0;
}