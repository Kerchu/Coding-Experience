#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>

using namespace std;

struct users
{
    int numUser;
    char name [20];
    char address [20];
    float balance;
    int accType;
};

void create() //Creation of the archive
{
	system("cls");
    ofstream f;
    f.open("users.dat", ios::out | ios::app | ios::binary);
    if (f.fail()) //Check for troubles while opening
    {
        cout << "ERROR: Non-existent or corrupt archive" << endl;
        system("pause");
        exit(1);
    }
    f.close();
    system("pause");
    system("cls");
}

void load(users archive, int size)//Load of data into the register
{
	system("cls");
    string c;
    ofstream f;
    f.open("users.dat", ios::out | ios::app | ios::binary);
    if (f.fail())
    {
        cout << "ERROR: Non-existent or corrupt archive" << endl;
        system("pause");
        exit(1);
    }
    while (1)
	{
        cout << "Enter user code:" << endl;
        cin >> archive.numUser;
        cin.ignore();
        cout << "Enter user name:" << endl;
        gets(archive.name);
        cin.ignore();
        cout << "Enter user address:" << endl;
        cin >> archive.address;
        cin.ignore();
        cout << "Enter account type:" << endl;
        cin >> archive.accType;
        cin.ignore();
        cout << "Enter balance:" << endl;
        cin >> archive.balance;
        cin.ignore();
        if (archive.balance > 2000 && archive.accType == 0 || archive.balance > 1500 && archive.accType == 1 || archive.balance > 1200 && archive.accType == 2 || archive.balance > 1000 && archive.accType == 3) //Checks for the account type and value entered
        {
            cout << "WARNING!! Superior balance according to account's type. Try again" << endl;
            system("pause");
            system("cls");
            break;
        }
        f.write((char*)&archive, size);
        f.close();
        cout << "Do you want to exit? (Press 'Enter' to exit)" << endl;
        getline(cin, c);
        if (c.empty()){
        	break;
		}
		system("cls");
    }
}

void list(users archive, int size)//Makes a list of every user loaded in the archive
{
	system("cls");
    ifstream in;
    in.open("users.dat", ios::binary);
    if (in.fail())
    {
        cout << "ERROR: Non-existent or corrupt archive" << endl;
        system("pause");
        exit(1);
    }
    in.read((char*)&archive, size);
    while (!in.eof())//Cycle while the file is open
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

void consult(users archive, int size)//Consults a specific user inside the archive
{
	system("cls");
    ifstream in;
    in.open("users.dat", ios::binary);
    if (in.fail())
    {
        cout << "ERROR: Non-existent or corrupt archive" << endl;
        system("pause");
        exit(1);
    }
    in.read((char*)&archive, size);
    printf("Enter user code:");
    int cod;
    cin >> cod;
    int exist = 0;
    while (!in.eof())//Searchs for the code of the user doing comparisons
    {
        if (cod == archive.numUser)
        {
            printf("%i %s %0.2f\n", archive.numUser, archive.name, archive.address, archive.balance, archive.accType);
            exist = 1;
            break;
        }
        in.read((char*)&archive, size);
    }
    if (exist == 0)//User not found
    cout << "There's no user with that code" << endl;
    in.close();
    system("pause");
    system("cls");
}
void mod()//Modifies the salary of a user
{
	system("cls");
    fstream arch;
    int pos = 0;
    arch.open("users.dat", ios::in | ios::out | ios::binary);
    if (arch.fail()) {
        cout << "ERROR: Non-existent or corrupt archive" << endl;
        system("pause");
        exit(1);
    }
    cout << "Enter user's code:" << endl;
    int cod, exist = 0;
    cin >> cod;
    users archive;
    pos = arch.tellg() - sizeof(users);
    arch.read((char*)&archive, sizeof(users));

    while (!arch.eof()) {
        if (archive.numUser == cod)//Finds the user and gives an input to enter the new value
        {
            cout << "User          --> " << archive.numUser << endl;
            cout << "Name          --> " << archive.name << endl;
            cout << "Address       --> " << archive.address << endl;
            cout << "Balance       --> " << archive.balance << endl;
            cout << "Account       --> " << archive.accType << endl;
            cout << "------------------- " << endl;
            cout << "Enter new balance --> " << endl;
            cin >> archive.balance;
            pos = arch.tellg() - sizeof(users);
            arch.seekg(pos, ios::beg);
            arch.write((char*)&archive, sizeof(users));
            cout << "Modified balance for the indicated user.\n";
            exist = 1;
            break;
        }
        arch.read((char*)&archive, sizeof(users));
    }
    if (exist == 0)//User not found
    cout << "There's no user with that code" << endl;
    arch.close();
    system("pause");
    system("cls");
}

void del()//Deletes an user doing a physical delete
{
	system("cls");
    fstream arch; ofstream arch1; int pos = 0;
    arch.open("users.dat", ios::in | ios::out | ios::binary);
    if (arch.fail()) {
        cout << "ERROR: Non-existent or corrupt archive" << endl;
        system("pause"); exit(1);
    }
    else {
        long size = sizeof(users); users product; int pos = 0;
        arch1.open("usersB.dat", ios::app | ios::out | ios::binary); //	 abre el archivo secundario...
        if (arch1.fail()) {
            cout << "Error during opening of temporary archive"; cout << "Press a key... ";
            _getch(); arch.close(); exit(1);
        }
        else {
            int x;
            string c;
            cout << "Enter user to delete: "; cin >> x;
            cout << "Are you sure you want to delete this user? (Press 'N' to cancel)" << endl;
            cin >> c;
            if (c == "N" || c == "n")
			{
				//return 0;
			}
            arch.read((char*)&product, sizeof(users)); // comienza el proceso de baja física...// lee un registro del archivo principal...
            while (!arch.eof()) {
                if (product.numUser != x) {
                    arch1.write((char*)&product, sizeof(users));// si x no coincide con legajo, graba en secundario...
                }
                else {
                    cout << "You have deleted the selected user." << endl;
                    cout << " " << product.numUser << " " << product.name << " " << product.address << " " << product.balance << " " << product.accType;
                    cout << "Press a key... "; _getch();
                }
                arch.read((char*)&product, sizeof(users)); // lee otro registro del principal, y vuelve al ciclo...
            }
            arch.close(); arch1.close();
            remove("users.dat"); rename("usersB.dat", "users.dat");
            cout << "Delete complete..." << endl << endl;
        }
    }
    system("pause");
    system("cls");
}

int main()//Menu
{
    users archive;
    int size = sizeof(users); // Size of the register
    int op;
    int input;
    do {
        cout << "----------------------------------------" << endl;
        cout << "[1] - Create the archive" << endl;
        cout << "[2] - Load users on the archive" << endl;
        cout << "[3] - Show list of registered users" << endl;
        cout << "[4] - Check for a specific user" << endl;
        cout << "[5] - Modify a user" << endl;
        cout << "[6] - Delete a user" << endl;
        cout << "[7] - Quit the program" << endl;
        cout << "----------------------------------------" << endl;
        cin >> input;
        cin.ignore();
        switch (input) {
        case 1:create();
            break;
        case 2:load(archive, size);
            break;
        case 3:list(archive, size);
            break;
        case 4:consult(archive, size);
            break;
        case 5:mod();
            break;
        case 6:del();
            break;
        }
    } while (input != 7);
    return 0;
}
