#include <iostream>
#include <ctime>

using namespace std;

string namepokemon[] = {"Arthur Morgan", "Boudica", "Caesar", "Darius", "Edward the Black Prince", "Frederick the Great"};
string elementpokemon[] = {"Earth", "Water", "Wind", "Fire"};

struct personal{                //สร้างข้อมูลส่วนตัวของโปเกม่อน
    string name;                //ชื่อ
    double hp;                  //เลือด
    double def;                  //เกราะ
    double atk;
    double spd; 
    string element;             //ธาตุ
}pokemon[6];

int randomnumber(int n){        //ฟังชั่นสุ่ม
    return rand() % n;
}

void createpokemon(){
    srand(time(0));
    double hp[] = {100.0, 100.0, 150.0, 150.0, 200.0, 200.0};   //รอแก้ไขให้สมดุล
    double def[] = {20.0, 20.0, 40.0, 40.0, 70.0, 70.0};        //รอแก้ไขให้สมดุล
    double atk[] = {50.0, 50.0, 30.0, 30.0, 20.0, 20.0};        //รอแก้ไขให้สมดุล
    double spd[] = {20.0, 20.0, 5.0, 5.0, 1.0, 1.0};            //รอแก้ไขให้สมดุล

    for(int i = 0; i < 6; i++){
        int randomelement = (randomnumber(4) * 7) % 4;
        pokemon[i].name = namepokemon[i];
        pokemon[i].element = elementpokemon[randomelement];
        pokemon[i].hp = hp[i];
        pokemon[i].def = def[i];
        pokemon[i].atk = atk[i];
        pokemon[i].spd = spd[i];
    }
}

int main(){
    createpokemon();
    
    for(int i = 0; i < 6; i++){
        cout << pokemon[i].name << " : " << pokemon[i].element << endl;
        cout << "HP : " << pokemon[i].hp << endl;
        cout << "DEF : " << pokemon[i].def << endl;
        cout << "ATK : " << pokemon[i].atk << endl;
        cout << "SPD : " << pokemon[i].spd << endl;
        cout << "-------------------------" << endl;
    }

    return 0;
}