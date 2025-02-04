#include <iostream>
#include <ctime>

using namespace std;

string namepokemon[] = {"Arthur Morgan", "Boudica", "Caesar", "Darius", "Edward the Black Prince", "Frederick the Great"};
string elementpokemon[] = {"Earth", "Water", "Wind", "Fire"};

struct personal{                //สร้างข้อมูลส่วนตัวของโปเกม่อน
    string name;                //ชื่อ
    double HP = 100.0;          //เลือด
    double mana = 100.0;        //มานา
    double def = 100.0;         //เกราะ
    string element;             //ธาตุ
}pokemon[6];

int randomnumber(int n){        //ฟังชั่นสุ่ม
    return rand() % n;
}

void createpokemon(){
    srand(time(0));
    for(int i = 0; i < 6; i++){
        int randomelement = (randomnumber(4) * 7) % 4;
        pokemon[i].name = namepokemon[i];
        pokemon[i].element = elementpokemon[randomelement];
    }
}

int main(){
    createpokemon();
    
    for(int i = 0; i < 6; i++){
        cout << pokemon[i].name << " : " << pokemon[i].element << endl;
        cout << "HP : " << pokemon[i].HP << endl;
        cout << "Mana : " << pokemon[i].mana << endl;
        cout << "DEF : " << pokemon[i].def << endl;
        cout << "-------------------------" << endl;
    }

    return 0;
}