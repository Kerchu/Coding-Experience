#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;

int counter = 0;
struct pics {//Declaration og the structure of "pics"

    string name;
    int widthPix;
    int heightPix;
    double size;
};
pics* data = new pics[700];

void read()//Load of new files
{
    system("cls");
    cout << "Enter file's name (Add '_' in case of composed): " << endl;
    for (int i = counter; i < counter + 1; i++)
    {
        cout << "(" << i << "): ";
        cin >> data[i].name;
    }
    cout << "Enter width (on pixels): " << endl;
    for (int i = counter; i < counter + 1; i++)
    {
        cout << "(" << i << "): ";
        cin >> data[i].widthPix;
    }
    cout << "Enter height (on pixels): " << endl;
    for (int i = counter; i < counter + 1; i++)
    {
        cout << "(" << i << "): ";
        cin >> data[i].heightPix;
    }
    cout << "Enter size (on KB): " << endl;
    for (int i = counter; i < counter + 1; i++)
    {
        cout << "(" << i << "): ";
        cin >> data[i].size;
    }
    counter++;
    if (counter == 700) {
        cout << "Insufficient storage space!!" << endl;
    }
}

void search() //Search for a specific file
{
    system("cls");
    int cont = 0;
    string srch;
    cout << endl;
    cout << "Enter file's name: " << endl;
    cin >> srch;
    cout << endl;
    for (int i = 0; i < 100; i++) {

        if (srch == data[i].name) {
            cout << "---------------------------------------------------" << endl;
			cout << "Name: " << data[i].name << endl;
			cout << "Width: " << data[i].widthPix << " Pixels" << endl;
			cout << "Height: " << data[i].heightPix << " Pixels" << endl;
			cout << "Size: " << data[i].size << " Kb" << endl;
			cout << "---------------------------------------------------" << endl;
            cont++;
        }
    }

    if (cont == 0) {
        cout << "Solicited file hasn't been found" << endl;
    }
}

void show()//Show all saved files
{
    system("cls");
    for (int i = 0; i < counter; i++)
    {
        cout << "---------------------------------------------------" << endl;
		cout << "File: " << data[i].name << endl;
        cout << "---------------------------------------------------" << endl;
    }
}

int main()//Menu
{
    int input;
    do {

        cout << "---------------------------------------------------" << endl;
		cout << "(1) Add a new file" << endl;
		cout << "(2) Check saved files" << endl;
		cout << "(3) Seek for a file" << endl;
		cout << "(4) Close the program" << endl;
		cout << "---------------------------------------------------" << endl;
        cin >> input;

        switch (input) {

        case 1:
            read();
            break;

        case 2:
            show();
            break;

        case 3:

            search();
            break;

        case 4:

            cout << "Closing the program" << endl;
            break;

        default:

            cout << "Input not valid, try again" << endl;
            break;

        }

    } while (input != 4);

    return 0;
}
