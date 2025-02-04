#include <iostream>
using namespace std;

int GetUserSelection(){
    int choice;
    cout << "PROGRAM MENU" << endl;
    cout << "1. Price an option" << endl;
    cout << "2. Evaluate  the Greeks" << endl;
    cout << "Please input your choice";
    cin >> choice;
    cout << "\n";
    return choice;
}
