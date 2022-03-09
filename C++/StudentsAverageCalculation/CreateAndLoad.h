#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

struct students
{
    int ID;
    char name[20];
    float firTerm, secTerm, thiTerm, prom;
};
students archive;

void create() //Creation of the file
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


void load()//Load of student data
{
    system("cls");
    students archive;
    int size = sizeof(students);
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
        cout << "Enter student's ID:" << endl;
        cin >> archive.dni;
        cin.ignore();
        cout << "Enter name:" << endl;
        gets_s(archive.name);
        cout << "Enter first average:" << endl;
        cin >> archive.firTerm;
        cin.ignore();
        cout << "Enter second average:" << endl;
        cin >> archive.secTerm;
        cin.ignore();
        cout << "Enter third average:" << endl;
        cin >> archive.thiTerm;
        cin.ignore();
        archive.prom = (archive.firTerm + archive.secTerm + archive.thiTerm) / 3;
        cout << endl;
        f.write((char*)&archive, size);
        cout << "Do you wish to exit? (Press 'Enter' to exit)" << endl;
        getline(cin, c);
        if (c.empty()) {
            f.close();
            system("cls");
            break;
        }
    }
}