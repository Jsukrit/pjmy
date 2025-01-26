#include <iostream>
#include <ctime>

using namespace std;

string namepokemon[] = {"A", "B", "C", "D", "E"};
string elementpokemon[] = {"Earth", "Water", "Wind", "Fire"};

struct {                        //สร้างข้อมูลส่วนตัวของโปเกม่อน
    string name;                //ชื่อ
    double HP = 100.0;          //เลือด
    double mana = 100.0;        //มานา
    double armor = 100.0;       //เกราะ
    string element;             //ธาตุ
}pokemon[5];

int randomnumber(int n){        //ฟังชั่นสุ่ม
    return rand() % n;
}

void createpokemon(){
    srand(time(0));
    for(int i = 0; i < 5; i++){
        int randomelement = (randomnumber(4) * 7) % 4;
        pokemon[i].name = namepokemon[i];
        pokemon[i].element = elementpokemon[randomelement];
    }
}

int main(){
    createpokemon();
    
    for(int i = 0; i < 5; i++){
        cout << pokemon[i].name << " : " << pokemon[i].element << endl;
    }

    return 0;
}