#include <iostream>

using namespace std;

void Menu(){
    char who;

    do{
        cout << "-------------------" << endl;
        cout << "Play with Computer : Type (C)" << endl;
        cout << "Play with Player : Type (P)" << endl;
        cout << "Enter your answer : ";
        cin >> who;
        cout << "-------------------" << endl;
    }while(who != 'C' && who != 'P');
}

int main(){
    
    Menu();
    return 0;
}