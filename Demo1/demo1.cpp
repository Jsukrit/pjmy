#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
#include <thread>  // ใช้สำหรับ sleep_for
#include <chrono>  // ใช้สำหรับหน่วยเวลา

using namespace std;

void Page1();
char Page2();
void createwindowCom();
void createwindowPlayer();
void Page3(char ComOrPlayer);
void createpokemon();
void takeNomalATK(double &HP, double DEF, double ATK);
void takeStrike(double &HP, double DEF, double ATK, double SPD1,double SPD2);
void defATK(double &HP, double DEF, double ATK);
int evade();
int comChoice();
void turnbase(int p1, int p2);
void Pageturnbase();
void showpokemon();
void delaySeconds(double seconds);
void selectpokemon(char who);

//รายละเอียด pokemons
/*struct poke
{
	string name;
	double HP, DEF, ATK, SPD;
};

//ประกาศตัวแปร global
poke p[3] = {{"Jesus", 100, 20, 30, 30}, {"Budha", 200, 50, 10, 10}, {"Kungfu", 150, 40, 20, 20}};*/

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

struct personalplayer{
    int pokeplayer;
    string nameplayer;
    int playerAction;
}player[2];

int choices[] = {1, 2, 3, 4};	//1 = ตีปกติ, 2 = strike, 3 = ป้องกัน, 4 = counter
bool sc;


int main()
{
	srand(time(0)); 
    //poke *pm1 = &p[rand() % 3], *pm2 = &p[rand() % 3];
    Page1();
    char who = Page2();
    Page3(who);

    createpokemon();
    showpokemon();

    selectpokemon(who);

    Pageturnbase();
    return 0;

}

void delaySeconds(double seconds) {
    clock_t start_time = clock();
    while ((clock() - start_time) / (double)CLOCKS_PER_SEC < seconds);
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
    getline(cin, player[0].nameplayer);
}

void createwindowPlayer(){
    cout << "PLEASE ENTER PLAYER 1 NAME : "; 
    getline(cin, player[0].nameplayer);
    cout << "PLEASE ENTER PLAYER 2 NAME : "; 
    getline(cin, player[1].nameplayer);

}

void Page3(char ComOrPlayer){
    if(ComOrPlayer == 'C'){
        createwindowCom();
    }
    else{
        createwindowPlayer();
    }
}

void Pageturnbase(){
    while(pokemon[player[0].pokeplayer].hp > 0 && pokemon[player[1].pokeplayer].hp > 0)
	{
        cout << "Player 1" << "\t\t" << "Player 2" << endl;
		cout << pokemon[player[0].pokeplayer].name << " HP: " << pokemon[player[0].pokeplayer].hp << "\t\t";
		cout << pokemon[player[1].pokeplayer].name << " HP: " << pokemon[player[0].pokeplayer].hp << "\n";
		cout << "Player'1 Choice : ";
		cin >> player[0].playerAction;
		player[1].playerAction = comChoice();
        delaySeconds(0.5);
		cout << "Player'2 Choice : " << player[1].playerAction << "\n";
		turnbase(player[0].playerAction, player[1].playerAction);
		cout << "-------------------------------------------------------------\n\n";
	}
	if(pokemon[player[0].pokeplayer].hp <= 0) cout << "Player'2 WIN\n";
	else cout << "Player'1 WIN\n";
}


int randomnumber(int n){        //ฟังชั่นสุ่ม
    return rand() % n;
}

void createpokemon(){           //สร้างโปเกม่อน
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

//โจมตีปกติ
void takeNomalATK(double &HP, double DEF, double ATK)
{
	HP = HP - (ATK*(1-(DEF/100)));
}

//โจมตีแบบ strike
void takeStrike(double &HP, double DEF, double ATK, double SPD1,double SPD2)
{
	double skATK = ATK + (abs(SPD1 - SPD2)*10);
	takeNomalATK(HP, DEF, skATK);
}

//กดป้องกัน
void defATK(double &HP, double DEF, double ATK)
{
	DEF *= 2;
	takeNomalATK(HP, DEF, ATK);
}

//กลไกรการหลบหลีก incomplete
int evade()
{
	int rate = rand()%100 + 1;
	return rate;
}

//computer choices
int comChoice()
{
	int choices[] = {1, 2, 3, 4};
	return choices[rand()%4];
}

//turn base system
void turnbase(int p1, int p2)
{
	int gameState = (p1 << 8) | p2;
		switch (gameState)
		{
			case(1 << 8) | 1:
				if(pokemon[player[0].pokeplayer].spd > pokemon[player[1].pokeplayer].spd)
				{
					if(pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
					if(pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack

				}else
				{
					if(pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack
					if(pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
				}
				break;

			case(1 << 8) | 2:
				if(pokemon[player[0].pokeplayer].spd > pokemon[player[1].pokeplayer].spd)
				{
					if(pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
					if(pokemon[player[0].pokeplayer].spd < evade()) takeStrike(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 2 strike
				}else
				{
					if(pokemon[player[0].pokeplayer].spd < evade()) takeStrike(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk      
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 2 strike
					if(pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
				}
				break;

			case(1 << 8) | 3:
				if(pokemon[player[1].pokeplayer].spd < evade()) defATK(pokemon[player[1].pokeplayer].hp
                , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk);        //player 1 nomal attack player 2 defend
				break;

			case(1 << 8) | 4:
				if(pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[1].pokeplayer].hp
                , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk);        //player 1 nomal attack
				break;

			case(2 << 8) | 1:
				if(pokemon[player[0].pokeplayer].spd > pokemon[player[1].pokeplayer].spd)
				{
					if(pokemon[player[1].pokeplayer].spd < evade()) takeStrike(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 1 strike
					if(pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack
				}else
				{
					if(pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack
					if(pokemon[player[1].pokeplayer].spd < evade()) takeStrike(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 1 strike
				}
				break;

			case(2 << 8) | 2:
				if(pokemon[player[0].pokeplayer].spd > pokemon[player[1].pokeplayer].spd)
				{
					if(pokemon[player[1].pokeplayer].spd < evade()) takeStrike(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 1 strike
					if(pokemon[player[0].pokeplayer].spd < evade()) takeStrike(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 2 strike
				}else
				{
					if(pokemon[player[0].pokeplayer].spd < evade()) takeStrike(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 2 strike
					if(pokemon[player[1].pokeplayer].spd < evade()) takeStrike(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 1 strike
				}

			case(2 << 8) | 3:
				if(pokemon[player[1].pokeplayer].spd < evade()) takeStrike(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 1 strike
				break;

			case(2 << 8) | 4:
				if(pokemon[player[0].pokeplayer].spd < evade()) takeStrike(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 2 strike
				break;
			
			case(3 << 8) | 1:
				if(pokemon[player[0].pokeplayer].spd < evade()) defATK(pokemon[player[0].pokeplayer].hp
                , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk);        //player 2 nomal attack plyer 1 defend
				break;
			
			case(3 << 8) | 2:
				if(pokemon[player[0].pokeplayer].spd < evade()) takeStrike(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 2 strike
				break;
			
			case(3 << 8) | 3:
				break;
			
			case(3 << 8) | 4:
				break;

			case(4 << 8) | 1:
				if(pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(pokemon[player[0].pokeplayer].hp
                    , pokemon[player[0].pokeplayer].def, pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack
				break;
			
			case(4 << 8) | 2:
				if(pokemon[player[1].pokeplayer].spd < evade()) takeStrike(pokemon[player[1].pokeplayer].hp
                    , pokemon[player[1].pokeplayer].def, pokemon[player[0].pokeplayer].atk
                    , pokemon[player[0].pokeplayer].spd, pokemon[player[1].pokeplayer].spd);    //player 1 strike
				break;

			case(4 << 8) | 3:
				break;

			case(4 << 8) | 4:
				break;

			default:
				cout << "Invalid input!" << "\n";
		}
	
}

void showpokemon(){
    string input;
    for(int i = 0; i < 6; i++){
        cout << "-------------------------" << endl;
        cout << "Name [" << i+1 << "] : " << pokemon[i].name << endl; 
        cout << "HP : " << pokemon[i].hp << endl;
        cout << "DEF : " << pokemon[i].def << endl;
        cout << "ATK : " << pokemon[i].atk << endl;
        cout << "SPD : " << pokemon[i].spd << endl;
        cout << "-------------------------" << endl;
        delaySeconds(0.5);
        if(i != 5){
            cout << ">>> Please Enter to see more <<<" << endl;
            getline(cin, input);
        }
    }
}

void selectpokemon(char who){
    cout << "Please select Player 1's Pokemon : ";
    cin >> player[0].pokeplayer;
    cout << "Player 1's Pokemon : " << pokemon[--player[0].pokeplayer].name << endl;
    cout << "--------------------------------------------------" << endl;
    if(who == 'P'){
        cout << "Please select Player 2's Pokemon : ";
        cin >> player[1].pokeplayer;
        cout << "Player 2's Pokemon : " << pokemon[--player[1].pokeplayer].name << endl;
    }
    else{
        player[1].pokeplayer = (randomnumber(6) * 7) % 6;
        cout << "Computer's Pokemon : " << pokemon[player[1].pokeplayer].name << endl;
    }
    cout << "--------------------------------------------------" << endl;
    
}
