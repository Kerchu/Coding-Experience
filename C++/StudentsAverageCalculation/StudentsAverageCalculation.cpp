#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include "CreateAndLoad.h"//self-made library

using namespace std;

void show()//Shows all the students
{
    system("cls");
    students archive;
    int size = sizeof(students);
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
        cout << " ID        --> " << archive.dni << endl;
        cout << " Name      --> " << archive.name << endl;
        cout << "-------------Trimester------------" << endl;
        cout << " 1         --> " << archive.firTerm << endl;
        cout << " 2         --> " << archive.secTerm << endl;
        cout << " 3         --> " << archive.thiTerm << endl;
        cout << "----------------------------------" << endl;
        in.read((char*)&archive, size);
    }
    in.close();
    system("pause");
    system("cls");
}

void consult()//Checks for a specific student
{
    system("cls");
    students archive;
    int size = sizeof(students);
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
    printf("Enter ID of the student:");
    int cod;
    cin >> cod;
    int exist = 0;
    while (!in.eof())
    {
        if (cod == archive.dni)
        {
            cout << "----------------------------------" << endl;
            cout << " ID        --> " << archive.dni << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << "-------------Trimester------------" << endl;
            cout << " 1         --> " << archive.firTerm << endl;
            cout << " 2         --> " << archive.secTerm << endl;
            cout << " 3         --> " << archive.thiTerm << endl;
            cout << "----------------------------------" << endl;
            exist = 1;
            break;
        }
        in.read((char*)&archive, size);
    }
    if (exist == 0)
    {
        system("cls");
        cout << "No existe un alumno con dicho DNI" << endl;
        cout << endl;
    }
    in.close();
    system("pause");
    system("cls");
}

void del()//Delete a student
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
        cout << "Are you sure you want to delete a student? (Press 'N' to cancel)" << endl;
        getline(cin, c);
        if (c != "N" && c != "n")
        {
            long size = sizeof(students); students archive; int pos = 0;
            arch1.open("usersB.dat", ios::app | ios::out | ios::binary);
            if (arch1.fail()) {
                cout << "Error during opening of temporary archive" << endl;
                system("pause");
                arch.close();
            }
            else {
                string i;
                while (1)
                {
                    int x;
                    cout << "Enter ID of the student: ";
                    cin >> x;
                    cin.ignore();
                    arch.read((char*)&archive, sizeof(students));
                    while (!arch.eof()) {
                        if (archive.dni != x) {
                            arch1.write((char*)&archive, sizeof(students));
                        }
                        else {
                            cout << "You have deleted the following student." << endl;
                            cout << " " << archive.dni << " " << archive.name << " " << endl;
                            system("pause");
                        }
                        system("cls");
                        arch.read((char*)&archive, sizeof(students));
                    }
                    cout << "Delete complete... Do you wish to exit? ('Enter' to exit)" << endl;
                    getline(cin, i);
                    if (i.empty()) {
                        arch.close(); arch1.close();
                        remove("users.dat");
                        if (rename("usersB.dat", "users.dat"))
                        {
                            perror("ERROR");
                        }
                        break;
                    }
                }
            }
        }
    }
    system("cls");
}

void prom()//General average calculations
{
    system("cls");
    fstream arch;
    int pos = 0, pos2 = 0, pos3 = 0;
    students archive;
    arch.open("users.dat", ios::in | ios::out | ios::binary);
    if (arch.fail())
    {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        system("pause");
        exit(1);
    }
    
    arch.read((char*)&archive, sizeof(students));
    while (!arch.eof())
    {
        if (archive.prom >= 7)//Calculates promotional students
        {
            cout << "----------------------------------" << endl;
            cout << " ID        --> " << archive.dni << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << "-------------Trimester------------" << endl;
            cout << " 1         --> " << archive.firTerm << endl;
            cout << " 2         --> " << archive.secTerm << endl;
            cout << " 3         --> " << archive.thiTerm << endl;
            cout << "----------------------------------" << endl;
            cout << "Promotion!!" << endl; cout << endl;
            pos++;
        }
        if (archive.prom >= 4 && archive.prom < 7) //Calculates students that have to do the exams at December
        {
            cout << "----------------------------------" << endl;
            cout << " ID        --> " << archive.dni << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << "-------------Trimester------------" << endl;
            cout << " 1         --> " << archive.firTerm << endl;
            cout << " 2         --> " << archive.secTerm << endl;
            cout << " 3         --> " << archive.thiTerm << endl;
            cout << "----------------------------------" << endl;
            cout << "Exam at December!!" << endl; cout << endl;
            pos2++;
        }
        if (archive.prom < 4) //Calculates students that have to do the exams at March
        {
            cout << "----------------------------------" << endl;
            cout << " ID        --> " << archive.dni << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << "-------------Trimester------------" << endl;
            cout << " 1         --> " << archive.firTerm << endl;
            cout << " 2         --> " << archive.secTerm << endl;
            cout << " 3         --> " << archive.thiTerm << endl;
            cout << "----------------------------------" << endl;
            cout << "Exam at March!!" << endl; cout << endl;
            pos3++;
        }
        arch.read((char*)&archive, sizeof(students));
    }

    arch.close();
    cout << "----------------------------------------------" << endl;
    cout << "Calculation finished!!!" << endl; cout << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Amount of promotional students: " << pos << endl;
    cout << "Amount of students that do exam at December: " << pos2 << endl;
    cout << "Amount of students that do exam at March: " << pos3 << endl;
    cout << "----------------------------------------------" << endl;
    system("pause");
    system("cls");
}


int main()
{
    int size = sizeof(students);
    int input;
    do {
        cout << "----------------------------------------------" << endl;
        cout << "[1] - Create the file" << endl;
        cout << "[2] - Load students" << endl;
        cout << "[3] - Show saved students" << endl;
        cout << "[4] - Check a specific student" << endl;
        cout << "[5] - Delete a student" << endl;
        cout << "[6] - Calculate general averages" << endl;
        cout << "[7] - Exit the program" << endl;
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
        case 5: del();
            break;
        case 6: prom();
            break;
        case 7: cout << "Closing the program" << endl;
            break;
        default: cout << "Not valid input" << endl; system("pause"); system("cls");
        }
    } while (input != 7);
    return 0;
}