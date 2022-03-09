#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

using namespace std;
int count = 0;

struct dataDe
{
	int points = 0;
	char name[30];
};
void load()//Points and player data load
{
	system("cls");
	dataDe archive;
	int size = sizeof(dataDe);
	string input;
	ofstream f;
	f.open("points.dat", ios::out | ios::app | ios::binary);
	if (f.fail())
	{
		cout << "ERROR File couldn't be created " << endl;
		system("pause");
		exit(1);
	}

	cout << "Data load (press 'Enter' to exit, any key to continue) \n\n";
	getline(cin, input);

	while (!cin.eof())
	{
		int pointsSum, contP, D = 0;
		if (input.empty()) {
			break;
		}
		else 
		{
			pointsSum = 0;
			archive.points = 0;
			contP = 0;
		}
		cout << "Program's code: 0-1 = Centre / 2-5 = Middle / 6-10 = Extreme / +10 = Failed" << endl;//Points value according to target
		cout << endl;
		cout << "Enter player's name: ";
		cin >> archive.name;
		do 
		{		
			cout << "Enter points (one per shot): ";
			cin >> D;
			if (D <= 1) 
			{
				archive.points = archive.points + 100;
			}
			if (D > 1 && D <= 5) 
			{
				archive.points = archive.points + 50;
			}
			if (D > 5 && D <= 10) 
			{
				archive.points = archive.points + 10;
			}
			contP++;
		} while (contP < 20);
		
		f.write((char*)&archive, size);
		cin.ignore();

		cout << "Do you wish to exit? (Press enter)" << endl;
		getline(cin, input);

		system("cls");
	}
	cin.clear();
	f.close();
	system("cls");
}
void show()//Shows player data and points
{
	system("cls");
	dataDe archive1;
	int size = sizeof(dataDe);
	ifstream in;

	in.open("points.dat", ios::binary);
	if (in.fail())
	{
		cout << "ERROR while reading the file " << endl;
		system("pause");
		exit(1);
	}
	in.read((char*)&archive1, size);
	cout << endl;

	while (!in.eof())
	{
		cout << "Name: " << archive1.name << endl;
		cout << "Points: " << archive1.points << endl;
		cout << endl;
		count++;
		in.read((char*)&archive1, size);
	}
	in.close();
	if (count < 100)//Checks the amount of registers
	{
		cout << "The amount of registers is " << count << " less than 100 " << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}
int main()//Menu
{
	int input;
	do {
		cout << "-------------------------------------------------------" << endl;
		cout << "[1] Add new data" << endl;
		cout << "[2] Show saved data" << endl;
		cout << "[3] Quit the program" << endl;
		cout << "-------------------------------------------------------" << endl;
		cin >> input;
		cin.ignore();

		switch (input) {
		case 1:
			load();
			break;
		case 2:
			show();
			break;
		case 3:
			cout << "Closing the program" << endl;
			break;
		default:
			cout << "Entered value not valid, try again" << endl;
			break;
		}
	} while (input != 3);
	return 0;
}