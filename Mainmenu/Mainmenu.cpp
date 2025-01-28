#include <iostream>
#include <string>

using namespace std;

string nameplayers[2];

void Page1();
char Page2();
void createwindowCom();
void createwindowPlayer();
void Page3(char ComOrPlayer);



int main(){
    Page1();
    char who = Page2();
    Page3(who);
    return 0;
}

void Page1(){
    string entertocontinue;
    cout << "----------------------------------" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "|          pokemonkings          |" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "----------------------------------" << endl;
    cout << "     Please Enter to continue     " << endl;
    getline(cin, entertocontinue);
}

char Page2(){
    char who;

        cout << "----------------------------------------" << endl;
        cout << "(1) Play with Computer (PVE) : Type (C)" << endl;
        cout << "(2) Play with Player   (PVP) : Type (P)" << endl;
    
    do{
        cout << "Enter your answer : ";
        cin >> who;
    }while(who != 'C' && who != 'P');

    if(who == 'C'){
        cout << ">>> (1) Play with Computer (PVE) <<<" << endl;
    }    
    else{
        cout << ">>> (2)  Play with Player  (PVP) <<<" << endl;
    }

    cout << "----------------------------------------" << endl;

    cin.ignore();
    return who;
}

void createwindowCom(){
    cout << "PLEASE ENTER YOUR NAME : ";
    getline(cin, nameplayers[0]);
}

void createwindowPlayer(){
    cout << "PLEASE ENTER PLAYER 1 NAME : "; 
    getline(cin, nameplayers[0]);
    cout << "PLEASE ENTER PLAYER 2 NAME : "; 
    getline(cin, nameplayers[1]);

}

void Page3(char ComOrPlayer){
    if(ComOrPlayer == 'C'){
        createwindowCom();
    }
    else{
        createwindowPlayer();
    }
}