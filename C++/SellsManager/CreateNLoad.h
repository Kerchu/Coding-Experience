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
    int numBill = 0, artCode = 0, flag = 0;
    char name[20] = "";
    float imp = 0, total = 0;
};
users archive;

void create()//Creation of the file
{
    system("cls");
    ofstream f, f2;
    f.open("sells.fac", ios::out | ios::app | ios::binary);
    f2.open("sells20.fac", ios::out | ios::app | ios::binary);
    if (f.fail() || f2.fail())
    {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    f.close(), f2.close();
    cout << "File creation finished!!!" << endl;
    system("pause");
    system("cls");
}


void load()//Load of client's data and buy
{
    system("cls");
    users archive;
    int size = sizeof(users);
    int p = 0;
    ofstream f, f2;
    f.open("sells.fac", ios::out | ios::app | ios::binary);
    f2.open("sells20.fac", ios::out | ios::app | ios::binary);
    if (f.fail() || f2.fail())
    {
        system("cls");
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    cout << "Enter amount of products:" << endl; cin >> p;
    cout << "Enter invoice number:" << endl;
    cin >> archive.numBill;
    cin.ignore();
    cout << "Enter client's name:" << endl;
    gets_s(archive.name);
    int t = 0;
    while (t < p) {
        if (p >= 20) //Distribution according amount of products
        {
            do {
                cout << "Enter product's code:" << endl;
                cin >> archive.artCode;
                cin.ignore();
                cout << "Enter price:" << endl;
                cin >> archive.imp;
                cin.ignore();
                archive.total = archive.total + archive.imp;
                f2.write((char*)&archive, size);
                t++;
                archive.flag++;
                system("cls");
            } while (t < p);
        }
        else 
        {
            do {
                cout << "Enter product's code:" << endl;
                cin >> archive.artCode;
                cin.ignore();
                cout << "Enter price:" << endl;
                cin >> archive.imp;
                cin.ignore();
                archive.total = archive.total + archive.imp;
                f.write((char*)&archive, size);
                t++;
                archive.flag++;
                system("cls");
            } while (t < p);
        }
        system("cls");
    }
    f.close(), f2.close();
}