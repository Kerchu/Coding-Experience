#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "CreateNLoad.h"//Self-made library

using namespace std;

void show()//Shows all sells
{
    system("cls");
    users archive;
    int size = sizeof(users);
    ifstream in,in2;
    in.open("sells.fac", ios::binary);
    in2.open("sells20.fac", ios::binary);
    if (in.fail() || in2.fail())
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
        cout << " Invoice   --> " << archive.numBill << endl;
        cout << " Name      --> " << archive.name << endl;
        cout << " Product   --> " << archive.artCode << endl;
        cout << " Price     --> " << archive.imp << endl;
        cout << "----------------------------------" << endl;
        in.read((char*)&archive, size);
    }
    in.close();
    cout << endl;
    cout << "+20 products buyings: " << endl;
    cout << endl;
    in2.read((char*)&archive, size);
    while (!in2.eof())
    {
        cout << " Invoice   --> " << archive.numBill << endl;
        cout << " Name      --> " << archive.name << endl;
        cout << " Product   --> " << archive.artCode << endl;
        cout << " Price     --> " << archive.imp << endl;
        cout << "----------------------------------" << endl;
        in2.read((char*)&archive, size);
    }
    in2.close();
    system("pause");
    system("cls");
}

void consult()//Checks on a specific sell
{
    system("cls");
    users archive;
    int size = sizeof(users);
    ifstream in, in2;
    in.open("sells.fac", ios::binary);
    in2.open("sells20.fac", ios::binary);
    if (in.fail() || in2.fail())
    {
        system("cls");
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    in.read((char*)&archive, size);
    cout << "Enter invoice code to check:" << endl;
    int cod;
    cin >> cod;
    int exist = 0;
    while (!in.eof())
    {
        if (cod == archive.numBill)
        {
            cout << "----------------------------------" << endl;
            cout << " Invoice   --> " << archive.numBill << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << " Product   --> " << archive.artCode << endl;
            cout << " Price     --> " << archive.imp << endl;
            cout << "----------------------------------" << endl;
            exist = 1;
        }
        in.read((char*)&archive, size);
    }
    in.close();//Closing of the first file, then proceeds to search in the second file
    if (exist == 0) 
    {
        in2.read((char*)&archive, size);
        while (!in2.eof())
        {
            if (cod == archive.numBill)
            {
                cout << "----------------------------------" << endl;
                cout << " Invoice   --> " << archive.numBill << endl;
                cout << " Name      --> " << archive.name << endl;
                cout << " Product   --> " << archive.artCode << endl;
                cout << " Price     --> " << archive.imp << endl;
                cout << "----------------------------------" << endl;
                exist = 1;
            }
            in2.read((char*)&archive, size);
        }
        in2.close();
    }
    
    if (exist == 0)
    {
        system("cls");
        cout << "There's not an invoice with that code" << endl;
        cout << endl;
    }
    
    system("pause");
    system("cls");
}
void mod()//Modifies a sell
{
    system("cls");
    fstream arch, arch2;
    int pos = 0;
    string c = "";
    arch.open("sells.fac", ios::in | ios::out | ios::binary);
    arch2.open("sells20.fac", ios::in | ios::out | ios::binary);
    if (arch.fail() || arch2.fail()) {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    cout << "Enter invoice code to modify:" << endl;
    int cod, exist = 0;
    cin >> cod;
    users archive;
    pos = sizeof(users);
    arch.read((char*)&archive, sizeof(users));

    while (!arch.eof()) {
        if (archive.numBill == cod)
        {
            cout << "----------------------------------" << endl;
            cout << " Invoice   --> " << archive.numBill << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << " Product   --> " << archive.artCode << endl;
            cout << " Price     --> " << archive.imp << endl;
            cout << "----------------------------------" << endl;
            cout << " Enter new price --> " << endl;
            cin >> archive.imp;
            pos = sizeof(users);
            arch.seekg(pos, ios::beg);
            arch.write((char*)&archive, sizeof(users));
            cout << endl;
            cout << "Price has been modified for this sell.";
            exist = 1;
        }
        cout << "Do you want to exit? ('Y' to exit)" << endl;
        getline(cin, c);
        if (c == "Y" && c == "y") 
        {
            arch.close();
            break;//Quits the whole process
        }
        arch.read((char*)&archive, sizeof(users));
    }
    arch.close();//COntinues to check into the other archive
    if (exist == 0) 
    {
        arch2.read((char*)&archive, sizeof(users));
        while (!arch2.eof()) {
            if (archive.numBill == cod)
            {
                cout << "----------------------------------" << endl;
                cout << " Factura   --> " << archive.numBill << endl;
                cout << " Nombre    --> " << archive.name << endl;
                cout << " Producto  --> " << archive.artCode << endl;
                cout << " Coste     --> " << archive.imp << endl;
                cout << "----------------------------------" << endl;
                cout << "Ingrese nuevo coste --> " << endl;
                cin >> archive.imp;
                pos = sizeof(users);
                arch.seekg(pos, ios::beg);
                arch.write((char*)&archive, sizeof(users));
                cout << endl;
                cout << "Se modifico el coste para dicha venta.";
                exist = 1;
            }
            if (c == "Y" && c == "y")
            {
                arch2.close();
                break;//Quits the whole process
            }
            arch2.read((char*)&archive, sizeof(users));
        }
        arch2.close();
    }
    
    if (exist == 0)
    {
        system("cls");
        cout << "There's not an invoice with that code" << endl;
        cout << endl;
    }
    system("pause");
    system("cls");
}

void del()//Deletes a sell
{
    system("cls");
    fstream arch, arch2; ofstream arch1; int pos = 0;
    arch.open("sells.fac", ios::in | ios::out | ios::binary);
    arch2.open("sells20.fac", ios::in | ios::out | ios::binary);
    if (arch.fail() || arch2.fail()) {
        cout << "ERROR: Non-existent or corrupt file" << endl;
        system("pause"); exit(1);
    }
    else {
        string c;
        cout << "Are you sure you want to delete this sell? (Press 'N' to cancel)" << endl;
        getline(cin, c);
        if (c != "N" && c != "n")
        {
            cout << "Do you want to delete a sell of >= 20 products? ('Y' to confirm)" << endl;
            getline(cin, c);
            if (c == "Y" && c == "y") 
            {
                system("cls");
                long size = sizeof(users); users archive; int pos = 0;
                arch1.open("sells2.fac", ios::app | ios::out | ios::binary);
                if (arch2.fail()) {
                    cout << "Error while opening temporary file" << endl;
                    system("pause");
                    arch2.close();
                }
                else {
                    while (1)
                    {
                        int x, i;
                        cout << "Enter invoice code: ";
                        cin >> x;
                        cin.ignore();
                        cout << "Enter products code to delete: ";
                        cin >> i;
                        cin.ignore();
                        arch.read((char*)&archive, sizeof(users));
                        while (!arch.eof()) {
                            if (archive.numBill != x || archive.artCode != i) {
                                arch1.write((char*)&archive, sizeof(users));
                            }
                            else {
                                cout << "You have deleted permanently the next sell." << endl;
                                cout << " " << archive.numBill << " " << archive.name << " " << archive.artCode << " " << archive.imp << endl;
                                system("pause");
                            }
                            system("cls");
                            arch.read((char*)&archive, sizeof(users));
                        }
                        cout << "Delete finished. Press 'Enter' to exit" << endl;
                        getline(cin, c);
                        if (c.empty()) {
                            arch2.close(); arch1.close();
                            remove("sells20.fac");
                            if (rename("sells2.fac", "sells20.fac"))
                            {
                                perror("ERROR");
                                system("pause");
                            }
                            break;
                        }
                    }
                }
            }
            else //Control whether delete >20 products sells or no
            {
                system("cls");
                long size = sizeof(users); users archive; int pos = 0;
                arch1.open("ventas2.fac", ios::app | ios::out | ios::binary);
                if (arch1.fail()) {
                    cout << "Error while opening temporary file" << endl;
                    system("pause");
                    arch.close();
                }
                else {
                    while (1)
                    {
                        int x, i;
                        cout << "Enter code of invoice: ";
                        cin >> x;
                        cin.ignore();
                        cout << "Enter code of product to delete: ";
                        cin >> i;
                        cin.ignore();
                        arch.read((char*)&archive, sizeof(users));
                        while (!arch.eof()) {
                            if (archive.numBill != x || archive.artCode != i) {
                                arch1.write((char*)&archive, sizeof(users));
                            }
                            else {
                                cout << "You have deleted permanently the next sell." << endl;
                                cout << " " << archive.numBill << " " << archive.name << " " << archive.artCode << " " << archive.imp << endl;
                                system("pause");
                            }
                            system("cls");
                            arch.read((char*)&archive, sizeof(users));
                        }
                        cout << "Delete finished. Press 'Enter' to exit" << endl;
                        getline(cin, c);
                        if (c.empty()) {
                            arch1.close(); arch.close();
                            remove("sells.fac");
                            if (rename("sells2.fac", "sells.fac"))
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
    }
    system("cls");
}

void cal()//calculate sells average
{
    system("cls");
    fstream arch, arch1;
    float i = 0, flag = 0;
    users archive;
    arch.open("sells.fac", ios::in | ios::out | ios::binary);
    arch1.open("sells20.fac", ios::in | ios::out | ios::binary);
    if (arch.fail() || arch1.fail())
    {
        cout << "Non-existent or corrupt file" << endl;
        system("pause");
        exit(1);
    }
    arch.read((char*)&archive, sizeof(users));
    while (!arch.eof())
    {
        i = i + archive.total;
        flag = flag + archive.flag;
        arch.read((char*)&archive, sizeof(users));
    }
    arch.close();
    arch1.read((char*)&archive, sizeof(users));
    while (!arch1.eof())
    {
        i = i + archive.total;
        flag = flag + archive.flag;
        arch1.read((char*)&archive, sizeof(users));
    }
    arch1.close();
    cout << "Total sells amount: " << i << endl;
    cout << "Total sells made: " << flag << endl;
    i = i / flag;
    cout << "Calculation finished!!! " << i << " Average of sells amount" << endl;
    system("pause");
    system("cls");
}

void seek()//Seek the cheapest invoice
{
    int i = 0, exist = 0;
    ifstream in, in2;
    system("cls");
    users archive;
    int size = sizeof(users);
    in.open("sells.fac", ios::in | ios::out | ios::binary);
    in2.open("sells20.fac", ios::in | ios::out | ios::binary);
    if (in.fail() || in2.fail()) 
    {
        system("cls");
        cout << "ERROR: Non-existent or corrupt file" << endl;
        cout << endl;
        system("pause");
        exit(1);
    }
    cout << "Enter invoice to check" << endl;
    cin >> i;
    in.read((char*)&archive, size);
    while (!in.eof())
    {
        if (i > archive.imp)
        {
            cout << " Invoice   --> " << archive.numBill << endl;
            cout << " Name      --> " << archive.name << endl;
            cout << " Product   --> " << archive.artCode << endl;
            cout << " Price     --> " << archive.imp << endl;
            cout << "----------------------------------" << endl;
            exist = 1;
        }
        in.read((char*)&archive, size);
    }
    in.close();
    if (exist == 0)
    {
        cout << "Sells of 20 or more products" << endl;
        in2.read((char*)&archive, size);
        while (!in2.eof())
        {
            if (i > archive.imp)
            {
                cout << " Invoice   --> " << archive.numBill << endl;
                cout << " Name      --> " << archive.name << endl;
                cout << " Product   --> " << archive.artCode << endl;
                cout << " Price     --> " << archive.imp << endl;
                cout << "----------------------------------" << endl;
            }
            in2.read((char*)&archive, size);
        }
        in2.close();
    }
    system("pause");
    system("cls");
}

int main()
{
    int size = sizeof(users);
    int input;
    do {
        cout << "----------------------------------------------" << endl;
        cout << "[1] - Create file" << endl;
        cout << "[2] - Load buy" << endl;
        cout << "[3] - Show list of data" << endl;
        cout << "[4] - Check a specific buy" << endl;
        cout << "[5] - Modify a buy" << endl;
        cout << "[6] - Delete a buy" << endl;
        cout << "[7] - Calculate the average of sells" << endl;
        cout << "[8] - Check type of acc" << endl;
        cout << "[9] - Exit program" << endl;
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
        case 9: cout << "Closing program" << endl;
            break;
        default: cout << "Not valid input" << endl; system("pause"); system("cls");
        }
    } while (input != 9);
    return 0;
}