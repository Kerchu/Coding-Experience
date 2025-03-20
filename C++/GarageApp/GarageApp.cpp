#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct clientTemplate
{
	char name[50], address[100];
	unsigned long int dni, phone;		
}; clientTemplate* client = new clientTemplate[200];
struct vehicleTemplate
{
	char model[100], patent[10];
	int dni;
}; vehicleTemplate* vehicle = new vehicleTemplate[200];

void writeclient(); void writevehicle(); void arrangeID(); void read(); void countclient(); void countcars(); void arrangename(); void delet(); void mod(); void search(); void optionsMenu();
fstream archive, archive2; int  help = 0, help2 = 0;

int main() {
	archive.open("ClientData.dat", ios::out | ios::app | ios::binary); 
	archive.close(); 
	archive2.open("VehicleData.dat", ios::out | ios::app | ios::binary); 
	archive2.close();
	countclient(); optionsMenu();
	return 0;
}
void optionsMenu() {
	system("cls");
	int option, selection;
	cout << "____________________\n";
	cout << "|    APP GARAGE     |\n";
	cout << "|     MAIN MENU     |\n";
	cout << "|___________________|\n\n";
	cout << "1) Load data" << endl;
	cout << "2) Check loaded data" << endl;
	cout << "3) Modify data" << endl;
	cout << "4) Delete data" << endl;
	cout << "5) About the program" << endl << endl;
	cout << "0) Exit" << endl;
	cin >> option;
	switch (option) {
	case 1:
		system("cls");
		cout << "____________________\n";
		cout << "|     DATA LOAD     |\n";
		cout << "|___________________|\n\n";
		cout << "1) Client input" << endl;
		cout << "2) Vehicle input" << endl << endl;
		cout << "0) Back" << endl;
		cin >> selection;
		while (selection != 1 && selection != 2 && selection != 0)
		{
			system("cls");
			cout << "Not valid Input, try again" << endl;
			cout << "1) Client input" << endl;
			cout << "2) Vehicle input" << endl << endl;
			cout << "0) Back" << endl;
			cin >> selection; cin >> selection;
		}
		if (selection == 1)
		{
			countclient(); writeclient();
		}
		if (selection == 2)
		{
			countcars(); writevehicle();
		}
		if (selection == 0) {
			optionsMenu();
		}
		break;
	case 2:
		system("cls");
		cout << "____________________\n";
		cout << "|    CHECK DATA     |\n";
		cout << "|___________________|\n\n";
		cout << "1) Consult specific data" << endl;
		cout << "2) Consult data of ALL CLIENTS sorted by NAME" << endl;
		cout << "3) Consult data of ALL CLIENTS sorted by ID" << endl;
		cout << "0) Back" << endl;
		cin >> selection;
		countclient(); countcars();
		while (selection != 1 && selection != 2 && selection != 3 && selection != 0)
		{
			cout << "Not valid Input, try again" << endl;
			cin >> selection;
		}
		if (selection == 1)
		{
			search();
		}
		if (selection == 2)
		{
			arrangename(); read();
		}
		if (selection == 3)
		{
			arrangeID(); read();
		}
		if (selection == 0) {
			optionsMenu();
		} break;
	case 3:
		system("cls"); 
		mod();
		break;
	case 4:
		system("cls");
		countcars(); delet();
		break;
	case 5:
		system("cls");
		cout << " _______________________________________\n";
		cout << "|            GARAGE PROGRAM            |\n";
		cout << "|            ''Uncle's Tom''           |\n";
		cout << "|______________________________________|\n\n";
		cout << " Developer: \n" << endl;
		cout << " Rodriguez Moyano, Franco Agustin" << endl;
		cout << " Date: 05/12/2021" << endl << endl;
		cout << "Press a key to return to the Main Menu\n";
		system("pause");
		optionsMenu();
		break;
	case 0:
		system("cls");
		cout << "Closing program, thank you for using ''Uncle's Tom'' GARAGE PROGRAM!! \n";
		break;
	default:
		optionsMenu(); break;
	}
}
void writeclient() {
	int i = 0, cant = 0;
	cout << "Enter amount of clients " << endl;
	cin >> cant;
	archive.open("ClientData.dat", ios::out | ios::app | ios::binary);
	if (archive.fail()) {
		cout << "ERROR! Non-existent or corrupt file" << endl; exit(1);
	}
	i = help;
	do {
		cout << "Enter client's ID: " << endl;
		cin >> client[i].dni;
		for (int j = 0; j < i; j++) {
			if (client[i].dni == client[j].dni) {
				while (client[i].dni == client[j].dni) {
					cout << "Add other number: " << endl;
					cin >> client[i].dni;
					j = 0;
				}
			}
		}
		cout << "Enter client's name: " << endl;
		cin.ignore(); cin.getline(client[i].name, 50);
		cout << "Enter client's phone number: " << endl;
		cin >> client[i].phone;
		for (int j = 0; j < i; j++) {
			if (client[i].phone == client[j].phone) {
				while (client[i].phone == client[j].phone) {
					cout << "Add other number: " << endl;
					cin >> client[i].phone;
					j = 0;
				}
			}
		}
		cout << "Enter client's address: " << endl;
		cin.ignore(); cin.getline(client[i].address, 100);
		archive.write((char*)&client[i], sizeof(clientTemplate));
		i++; cant--;
	} while (cant > 0);
	archive.close(); 
	system("pause"); 
	optionsMenu();
}
void writevehicle() {
	int i = 0, cant=0;
	cout << "Enter amount of cars: " << endl;
	cin >> cant;
	archive2.open("VehicleData.dat", ios::out | ios::app | ios::binary);
	if (archive2.fail()) {
		cout << "ERROR! Non-existent or corrupt file" << endl;
		exit(1);
	}
	i = help2;
	do {
		cout << "Enter owner's ID: " << endl;
		cin >> vehicle[i].dni;
		cout << "Enter patent: " << endl;
		cin.ignore(); cin.getline(vehicle[i].patent, 10);
		cout << "Enter vehicle's model: " << endl;
		cin.getline(vehicle[i].model, 100);
		archive2.write((char*)&vehicle[i], sizeof(vehicleTemplate));
		i++; cant--;
	} while (cant > 0);
	archive2.close(); 
	system("pause"); 
	optionsMenu();
}
void countclient() {
	int i = 0; help = 0;
	archive.open("ClientData.dat", ios::in | ios::binary); archive.read((char*)&client[i], sizeof(clientTemplate));
	while (!archive.eof()) {
		i++;
		archive.read((char*)&client[i], sizeof(clientTemplate));
	}
	help = i;
	archive.close();
}
void countcars() {
	int j = 0; help2 = 0;
	archive2.open("VehicleData.dat", ios::in | ios::binary); archive2.read((char*)&vehicle[j], sizeof(vehicleTemplate));
	while (!archive2.eof()) {
		j++;
		archive2.read((char*)&vehicle[j], sizeof(vehicleTemplate));
	}
	help2 = j;
	archive2.close();
}
void read() {
	int i = 0, countClientCar = 0;
	archive.open("ClientData.dat", ios::in | ios::binary); archive2.open("VehicleData.dat", ios::in | ios::binary);
	archive.read((char*)&client[i], sizeof(clientTemplate));
	while (!archive.eof()) {
		cout << "- ID: " << client[i].dni << endl;
		cout << "- Name: " << client[i].name << endl;
		cout << "- Phone: " << client[i].phone << endl;
		cout << "- Address: " << client[i].address << endl;
		for (int j = 0; j <= help2; j++) {
				if (client[i].dni == vehicle[j].dni) {
				countClientCar++;
			    }
		}
		if(countClientCar !=0){
			cout << "- Vehicles ("<< countClientCar << "): \n";
		}
		for (int j = 0; j <= help2; j++) {
			if (client[i].dni == vehicle[j].dni) {
				cout << "   - Model: " << vehicle[j].model << endl;
				cout << "   - Patent: " << vehicle[j].patent << endl << endl;
			}
		}cout << "--------------------------------------------" << endl;
		i++; countClientCar = 0;
		archive.read((char*)&client[i], sizeof(clientTemplate));
	}
	archive.close(); archive2.close(); system("pause"); optionsMenu();
}
void arrangeID() {
	archive.open("ClientData.dat", ios::out | ios::binary);
	for (int i = 0; i < help;i++)
	{
		for (int j = i + 1; j < help; j++)
		{
			if (client[i].dni > client[j].dni)
			{
				int aux = client[i].dni;
				client[i].dni = client[j].dni;
				client[j].dni = aux;
				int aux2 = client[i].phone;
				client[i].phone = client[j].phone;
				client[j].phone = aux2;
				char aux3[50];
				memcpy(aux3, client[i].name, 50);
				memcpy(client[i].name, client[j].name, 50);
				memcpy(client[j].name, aux3, 50);
				char aux4[100];
				memcpy(aux4, client[i].address, 100);
				memcpy(client[i].address, client[j].address, 100);
				memcpy(client[j].address, aux4, 100);
			}
		}
	}
	for (int i = 0; i < help;i++) {
		archive.write((char*)&client[i], sizeof(clientTemplate));
	} archive.close();
}
void arrangename() {
	archive.open("ClientData.dat", ios::out | ios::binary);
	for (int i = 0; i < help;i++)
	{
		for (int j = i + 1; j < help; j++)
		{
			if (strcmp(client[i].name, client[j].name) > 0)
			{
				char aux3[50];
				memcpy(aux3, client[i].name, 50);
				memcpy(client[i].name, client[j].name, 50);
				memcpy(client[j].name, aux3, 50);
				int aux = client[i].dni;
				client[i].dni = client[j].dni;
				client[j].dni = aux;
				int aux2 = client[i].phone;
				client[i].phone = client[j].phone;
				client[j].phone = aux2;
				char aux4[100];
				memcpy(aux4, client[i].address, 100);
				memcpy(client[i].address, client[j].address, 100);
				memcpy(client[j].address, aux4, 100);
			}
		}
	}
	for (int i = 0; i < help;i++) {
		archive.write((char*)&client[i], sizeof(clientTemplate));
	} archive.close();
}
void delet(){
	int c, g, countFoundClients = 0;
	fstream archive3; system("cls");
	cout << "___________________\n";
	cout << "|   DATA DELETE   |\n";
	cout << "|_________________|\n\n";
	cout << "Do you want to delete a client or a vehicle? \n 1) Client \n 2) Vehicle" << endl;
	cin >> g;
	while (g != 1 && g != 2)
	{
		system("cls");
		cout << "Input not valid \n Do you want to delete a client or a vehicle? \n 1) Client \n 2) Vehicle" << endl;
		cin >> g;
	}
    if (g == 1){
    	int num;
    	archive.open("ClientData.dat", ios::in | ios::binary); archive3.open("Auxiliar.dat", ios::out | ios::app | ios::binary);
    	if (archive3.fail()) {
			cout << "Error while opening temporary file" << endl;
			system("pause"); archive3.close();
        }
		while (1) {
			int i = 0;
			cout << "Enter ID to delete: ";
			cin >> num;
			archive.read((char*)&client[i], sizeof(clientTemplate));
			while (!archive.eof()) {
				if (client[i].dni != num) {
					archive3.write((char*)&client[i], sizeof(clientTemplate));
				}
				else {
					countFoundClients++;
				} i++;
				archive.read((char*)&client[i], sizeof(clientTemplate));
			}
			archive.close(); archive3.close(); remove("ClientData.dat");
			if (rename("Auxiliar.dat", "ClientData.dat"))
			{
				perror("ERROR"); system("pause");
			} break;
		}
        if (countFoundClients == 0) {
			cout << "The entered ID hasn't been found: " << num << endl; 
			system("pause");
		}
		else{
			cout << "ID deleted succesfully: " << num << endl; 
			system("pause");
		}           
	}
	if (g == 2){
    	char com[10];
    	archive2.open("VehicleData.dat", ios::in | ios::binary); archive3.open("Auxiliar.dat", ios::out | ios::app | ios::binary);
    	if (archive3.fail()) {
            cout << "ERROR! Non-existent or corrupt file" << endl;
            system("pause"); archive3.close();
            }
        while(1){
        	char var[10];
			int i=0;
        	cout << "Enter patent to delete: ";
        	cin.ignore(); cin.getline(com, 10);            
        	archive2.read((char*)&vehicle[i], sizeof(vehicleTemplate));
			while (!archive2.eof()) {
				if (strcmp(vehicle[i].patent, com) == 0) {
					cout << vehicle[i].patent << endl;
					for (int j = i; j <= help2; j++) {
						memcpy(vehicle[j].patent, vehicle[j + 1].patent, 10);
						memcpy(vehicle[j].model, vehicle[j + 1].model, 100);
						vehicle[j].dni = vehicle[j + 1].dni;
					}
					for (int j = 0; j <= help2; j++) {
						archive3.write((char*)&vehicle[j], sizeof(vehicleTemplate));
					} i--; countFoundClients++;
				} i++; 
				archive2.read((char*)&vehicle[i], sizeof(vehicleTemplate));
			}
			archive2.close(); archive3.close(); remove("VehicleData.dat");
			if (rename("Auxiliar.dat", "VehicleData.dat"))
			{
				system("pause");
			} break;
        }
        if (countFoundClients == 0) {
			cout << "Patent hasn't been found: " << com << endl; system("pause");
		}else{
			cout << "Patent deleted succesfully: " << com << endl; system("pause");
		}
	} optionsMenu();
}
void mod()
{
	int gar = 0, countFoundClient = 0;
	fstream archive3; 
	system("cls");
	cout << "________________________\n";
	cout << "|   DATA MODIFICATION   | \n";
	cout << "|_______________________|\n\n";
	cout << "Do you want to modify a vehicle or a client? \n 1) Client \n 2) Vehicle" << endl;
	cin >> gar;
	while (gar != 1 && gar != 2)
	{
		system("cls");
		cout << "Input not valid \n Do you want to modify a vehicle or a client? \n 1) Client \n 2) Vehicle" << endl;
		cin >> gar;
	}
	if (gar == 1) {
		archive.open("ClientData.dat", ios::in | ios::binary); archive3.open("Auxiliarmod.dat", ios::out | ios::app | ios::binary); system("cls");
		int i = 0, cod = 0;
		cout << "Enter ID to modify:\n";
		cin >> cod;
		while (1) {
			archive.read((char*)&client[i], sizeof(clientTemplate));
			while (!archive.eof()) {
				if (client[i].dni != cod) {
					archive3.write((char*)&client[i], sizeof(clientTemplate));
				}
				else {
					cout << "Data found: " << client[i].dni << endl;
					cout << "- ID: " << client[i].dni << endl;
					cout << "- Name: " << client[i].name << endl;
					cout << "- Phone: " << client[i].phone << endl;
					cout << "- Address: " << client[i].address << endl << endl;
					cout << "New data: " << client[i].dni << endl;
					cout << "New name: " << endl;
					cin.ignore(); cin.getline(client[i].name, 50);
					cout << "New phone: " << endl;
					cin >> client[i].phone;
					cout << "New address: " << endl;
					cin.ignore(); cin.getline(client[i].address, 100);
					archive3.write((char*)&client[i], sizeof(clientTemplate));
					system("pause"); countFoundClient++;
				} i++;
				archive.read((char*)&client[i], sizeof(clientTemplate));
			}
			if (countFoundClient == 0) {
				cout << "ID hasn't been found: " << cod << endl; system("pause");
			}
			archive.close(); archive3.close();
			remove("ClientData.dat");
			if (rename("Auxiliarmod.dat", "ClientData.dat"))
			{
				perror("ERROR"); system("pause");
			} break;
		}
	}
	if (gar == 2) {
		archive.open("VehicleData.dat", ios::in | ios::binary); archive3.open("Auxiliarmod.dat", ios::out | ios::app | ios::binary); system("cls");
		int i = 0; char cod[10];
		cout << "Enter patent to modify:\n";
		cin.ignore(); cin.getline(cod, 10);
		while (1) {
			archive.read((char*)&vehicle[i], sizeof(vehicleTemplate));
			while (!archive.eof()) {
				if (strcmp(vehicle[i].patent, cod) == 0) {
					countFoundClient++;
					cout << "Enter new patent" << endl;
					cin.getline(vehicle[i].patent, 10);
					cout << "Enter new model" << endl;
					cin.getline(vehicle[i].model, 100);
					archive3.write((char*)&vehicle[i], sizeof(vehicleTemplate));
				}
				else {
					archive3.write((char*)&vehicle[i], sizeof(vehicleTemplate));
				} i++;
				archive.read((char*)&vehicle[i], sizeof(vehicleTemplate));
			}
			if (countFoundClient == 0) {
				cout << "Patent hasn't been found: " << cod << endl; system("pause");
			}
			archive.close(); archive3.close();
			remove("VehiculoDatos.dat");
			if (rename("Auxiliarmod.dat", "VehiculoDatos.dat"))
			{
				perror("ERROR"); system("pause");
			} break;
		}
	} optionsMenu();
}
void search() {
	system("cls");
	int gar = 0, countFoundClient = 0;
	cout << "Do you want to search a vehicle or a client? \n 1) Client \n 2) Vehicle" << endl;
	cin >> gar;
	while (gar != 1 && gar != 2)
	{
		system("cls");
		cout << "Input not valid \n Do you want to search a vehicle or a client? \n 1) Client \n 2) Vehicle" << endl;
		cin >> gar;
	}
	if (gar == 1) {
		system("cls");
		archive.open("ClientData.dat", ios::in | ios::binary);
		int i = 0, cod = 0;
		cout << "Enter ID to search:\n";
		cin >> cod;
		archive.read((char*)&client[i], sizeof(clientTemplate));
		while (!archive.eof()) {
			if (cod == client[i].dni) {
				cout << "The client is: " << endl;
				cout << "- ID: " << client[i].dni << endl;
				cout << "- Name: " << client[i].name << endl;
				cout << "- Phone: " << client[i].phone << endl;
				cout << "- Address: " << client[i].address << endl;
				system("pause"); countFoundClient++;
			} i++;
			archive.read((char*)&client[i], sizeof(clientTemplate));
		} archive.close();
		if (countFoundClient == 0) {
			cout << "ID hasn't been found: " << cod << endl; system("pause");
		}
	}
	if (gar == 2) {
		system("cls");
		archive.open("VehicleData.dat", ios::in | ios::binary);
		int i = 0; char cod[10];
		cout << "Enter patent to search:\n";
		cin.ignore(); cin.getline(cod, 10);
		archive.read((char*)&vehicle[i], sizeof(vehicleTemplate));
		while (!archive.eof()) {
			if (strcmp(vehicle[i].patent, cod) == 0) {
				cout << "The vehicle is: " << endl;
				cout << "- Patent: " << vehicle[i].patent << endl;
				cout << "- Client's ID: " << vehicle[i].dni << endl;
				cout << "- Model: " << vehicle[i].model << endl;
				system("pause"); countFoundClient++;
			} i++;
			archive.read((char*)&vehicle[i], sizeof(vehicleTemplate));
		} archive.close();
		if (countFoundClient == 0) {
			cout << "Patent hasn't been found: " << cod << endl; system("pause");
		}
	} optionsMenu();
}
