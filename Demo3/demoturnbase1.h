#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
#include <thread>  // ใช้สำหรับ sleep_for
#include <chrono>  // ใช้สำหรับหน่วยเวลา
#include <vector>
#include<cstdlib>
#include<iomanip>

using namespace std;

void Page1();
char Page2();
void createwindowCom();
void createwindowPlayer();
void Page3(char ComOrPlayer);
void createpokemon();
/*
void takeNomalATK(double &HP, double DEF, double ATK);
void takeStrike(double &HP, double DEF, double ATK, double SPD1,double SPD2);
void defATK(double &HP, double DEF, double ATK);
int evade();
*/
int comChoice();
void turnbase(int p1, int p2);
void Pageturnbase(char who);
void showpokemon();
void delaySeconds(double seconds);
void selectpokemon(char who);
void win(int p);

//รายละเอียด pokemons
/*struct poke
{
	string name;
	double HP, DEF, ATK, SPD;
};

//ประกาศตัวแปร global
poke p[3] = {{"Jesus", 100, 20, 30, 30}, {"Budha", 200, 50, 10, 10}, {"Kungfu", 150, 40, 20, 20}};*/

string namepokemon[6] = {"Arthur Morgan", "Boudica", "Caesar", "Darius", "Edward the Black Prince", "Frederick the Great"};                //ชื่อ
double hppokemon[6] = {100.0, 100.0, 150.0, 150.0, 200.0, 200.0}; 
double hpmaxpokemon[6] = {100.0, 100.0, 150.0, 150.0, 200.0, 200.0};  //รอแก้ไขให้สมดุล
double defpokemon[6] = {20.0, 20.0, 40.0, 40.0, 70.0, 70.0};        //รอแก้ไขให้สมดุล
double atkpokemon[6] = {50.0, 50.0, 30.0, 30.0, 20.0, 20.0};        //รอแก้ไขให้สมดุล
double spdpokemon[6] = {20.0, 20.0, 5.0, 5.0, 1.0, 1.0};    
string elementpokemon[4] = {"Earth", "Water", "Wind", "Fire"}; 
int choices[4] = {1, 2, 3, 4}; //1 = ตีปกติ, 2 = strike, 3 = ป้องกัน, 4 = counter


class pokemon
{
    public:    
        string namepokemon;                //ชื่อ
        double hp;    //รอแก้ไขให้สมดุล
        double hpmax;
        double def;   //รอแก้ไขให้สมดุล
        double atk;  //รอแก้ไขให้สมดุล
        double spd;
        string element;
    
        friend class player;
};

class player
{
    string type;
    string name;
    vector<pokemon> myteam;
    
    public:
        string nameplayer;                //ชื่อ
        int playerAction;
        double takeNomalATK(int n, player &opp);
        double takeStrike(int n, player &opp);
        void def(int n);
        void undef(int n);
        int evade();
        void createplayer(const string &n);
        void choosepokemon(int n);
        void comchoosepokemon();
        bool isDead(int n);
        void showstat(int n, int who);
        double checkspd(int n);
};

double player::takeNomalATK(int n, player &opp){
    double damage = (myteam[n].atk*(1-(opp.myteam[n].def/100)));
    opp.myteam[n].hp -= damage;

    return damage;
}

double player::takeStrike(int n, player &opp){
    double skATK = myteam[n].atk + (abs(opp.myteam[n].spd - myteam[n].spd)*10);
	double damage = (skATK*(1-(opp.myteam[n].def/100)));
    opp.myteam[n].hp -= damage;
    return damage;
}

void player::def(int n){
    myteam[n].def *= 5;
}

void player::undef(int n){
    myteam[n].def /= 2;
}


void player::choosepokemon(int n){
    int input;
    cout << "Please select Player " << n << "'s Pokemon : ";
    cin >> input;
    pokemon unit;
    unit.namepokemon = namepokemon[input-1]; 
    unit.atk = atkpokemon[input-1];
    unit.hp = hppokemon[input-1];
    unit.hpmax = hpmaxpokemon[input-1];
    unit.def = defpokemon[input-1];
    unit.spd = spdpokemon[input-1];
    unit.element = elementpokemon[(rand() % 4 * 7) % 4];

    myteam.push_back(unit);
}

void player::createplayer(const string &n) {
    cout << n << " : " << "PLEASE ENTER YOUR NAME : ";
    cin.ignore();
    getline(cin, name);
}


int player::evade(){
    int rate = rand()%100 + 1;
	return rate;
}

void player::comchoosepokemon(){
    int random = ((rand() % 100) * 77) % 6;
    pokemon unit;
    unit.namepokemon = namepokemon[random]; 
    unit.atk = atkpokemon[random];
    unit.hp = hppokemon[random];
    unit.hpmax = hpmaxpokemon[random];
    unit.def = defpokemon[random];
    unit.spd = spdpokemon[random];
    unit.element = elementpokemon[(rand() % 4 * 7) % 4];

    myteam.push_back(unit);
}

bool player::isDead(int n){
    if(myteam[n].hp <= 0) return true;
    else return false;
}

void player::showstat(int n, int who){
    if(who == 1){
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "Player 1's name : " << nameplayer << endl;
        cout << "Pokemon name : " << myteam[n].namepokemon << "\tElement : " << myteam[n].element << endl;
        cout << "HP: " << myteam[n].hp << "/" << myteam[n].hpmax << "\tATK: "<< myteam[n].atk << "\t\tDEF: "<< myteam[n].def << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
    }
    else{
        cout << "\t\t\t\t\t\t---------------------------------------------------------------------------------" << endl; 
		cout << "\t\t\t\t\t\tPlayer 2's name : " << nameplayer << endl; 
		cout << "\t\t\t\t\t\tPokemon name : " << myteam[n].namepokemon << "\tElement : " << myteam[n].element << endl;
        cout << "\t\t\t\t\t\tHP: " << myteam[n].hp << "/" << myteam[n].hpmax << "\tATK: "<< myteam[n].atk << "\t\tDEF: "<< myteam[n].def << endl;
		cout << "\t\t\t\t\t\t---------------------------------------------------------------------------------" << endl;
    }
}

double player::checkspd(int n){
    return myteam[n].spd;
}

void drawscene(int p1, player &p_1, int p2, player &p_2){
    bool checkdef1 = false;
    bool checkdef2 = false;

        if(p1 == 1){
            cout << "Player 1 Attack!!!!!";
            double damage = p_1.takeNomalATK(0, p_2);
            cout << "\t\t" << setw(2) << damage << " Damage";
        }
        if(p1 == 2){
            cout << "Player 1 Strike!!!!!";
            if(p2 != 4){
                double damage = p_1.takeStrike(0, p_2);
                cout << "\t\t" << setw(2) << damage << " Damage";
            }
        }
        if(p1 == 3){
            cout << "Player 1 Defend!!!!!";
            if(p2 != 2){
                p_1.def(0);
                checkdef1 = true;
            }
        }
        if(p1 == 4){
            cout << "Player 1 Counter!!!!!";
            if(p2 == 2){
                double damage = p_1.takeStrike(0, p_2);
                cout << "\t\t" << setw(2) << damage << " Damage";
            }
        }
        if(p2 == 1){
            cout << "\t\t\t\tPlayer 2 Attack!!!!!";
            double damage = p_2.takeNomalATK(0, p_1);
            cout << "\t\t" << setw(2) << damage << " Damage";
        }
        if(p2 == 2){
            cout << "\t\t\t\tPlayer 2 Strike!!!!!";
            if(p1 != 4){
                double damage = p_2.takeStrike(0, p_1);
                cout << "\t\t" << setw(2) << damage << " Damage";
            }
        
        }
        if(p2 == 3){
            cout << "\t\t\t\tPlayer 2 Defend!!!!!";
            if(p1 != 2){
                p_2.def(0);
                checkdef2 = true;
            }
        }
        if(p2 == 4){
            cout << "\t\t\t\tPlayer 2 Counter!!!!!";
            if(p1 == 2){
                double damage = p_2.takeStrike(0, p_1);
                cout << "\t\t" << setw(2) << damage << " Damage";
            }
        }
        if(checkdef1){
            p_1.undef(0);
        }
        if(checkdef2){
            p_2.undef(0);
        }
        cout << endl;

}

void win(int p){
    cout << "===========================================================================" << endl;
    for(int i = 0; i < 3; i++) cout << endl;
    cout << "                                      Player" << p << "Win" << endl;
    for(int i = 0; i < 3; i++) cout << endl;
    cout << "===========================================================================" << endl;
}
/*
struct personalplayer{
    int pokeplayer;
    string nameplayer;
    int playerAction;
    personal pokemon[6];
}player[2];
*/

bool sc;


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
    }while(toupper(who) != 'C' && toupper(who) != 'P');

    if(toupper(who) == 'C'){
        cout << ">>> (1) Play with Computer (PVE) <<<" << endl;
    }    
    else{
        cout << ">>> (2)  Play with Player  (PVP) <<<" << endl;
    }

    cout << "----------------------------------------" << endl;

    cin.ignore();
    return who;
}

void Return2Menu() {
    string entertoreturn;
    cout << "----------------------------------" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "|         return to menu         |" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "----------------------------------" << endl;
    cout << "     Please press Enter to continue     " << endl;
    
    cin.sync();  
    cin.ignore(); 
    getline(cin, entertoreturn);
}


/*
void createwindowCom(){
    cout << "PLEASE ENTER YOUR NAME : ";
    getline(cin, player[0].nameplayer);
}
*/
/*
void createwindowPlayer(){
    cout << "PLEASE ENTER PLAYER 1 NAME : "; 
    getline(cin, player[0].nameplayer);
    cout << "PLEASE ENTER PLAYER 2 NAME : "; 
    getline(cin, player[1].nameplayer);

}
*/
/*
void Page3(char ComOrPlayer){
    p1.createplayer();
    p1.choosepokemon(1);
    if(ComOrPlayer == 'C'){
        p2.comchoosepokemon();
    }
    else{
        p2.createplayer();
        p2.choosepokemon(2);
    }
}
*/
/*
void Pageturnbase(char who){
    
    if(who == 'C'){
        while(player[0].pokemon[player[0].pokeplayer].hp > 0 && player[1].pokemon[player[1].pokeplayer].hp > 0)
        {
            cout << "Player 1" << "\t\t" << "Player 2" << endl;
            cout << player[0].pokemon[player[0].pokeplayer].name << " HP: " << player[0].pokemon[player[0].pokeplayer].hp << "\t\t";
            cout << player[1].pokemon[player[1].pokeplayer].name << " HP: " << player[1].pokemon[player[1].pokeplayer].hp << "\n";
            cout << "Player'1 Choice : ";
            cin >> player[0].playerAction;
            player[1].playerAction = comChoice();
            delaySeconds(0.5);
            cout << "Player'2 Choice : " << player[1].playerAction << "\n";
            turnbase(player[0].playerAction, player[1].playerAction);
            cout << "-------------------------------------------------------------\n\n";
        }
        
    }
    else{
        while(player[0].pokemon[player[0].pokeplayer].hp > 0 && player[1].pokemon[player[1].pokeplayer].hp > 0)
        {
            cout << "Player 1" << "\t\t\t" << "Player 2" << endl;
            cout << player[0].pokemon[player[0].pokeplayer].name << " HP: " << player[0].pokemon[player[0].pokeplayer].hp << "\t\t";
            cout << player[1].pokemon[player[1].pokeplayer].name << " HP: " << player[1].pokemon[player[1].pokeplayer].hp << "\n";
            cout << "Player'1 Choice : ";
            cin >> player[0].playerAction;
            delaySeconds(0.5);
            cout << "Player'2 Choice : " ;
            cin >> player[1].playerAction;
            turnbase(player[0].playerAction, player[1].playerAction);
            cout << "-------------------------------------------------------------\n\n";
        }
    }
	if(player[0].pokemon[player[0].pokeplayer].hp <= 0) cout << "Player'2 WIN\n";
	else cout << "Player'1 WIN\n";
}
*/

int randomnumber(int n){        //ฟังชั่นสุ่ม
    return ((rand() % 100) * 77) % n;
}

/*
void createpokemon(){           //สร้างโปเกม่อน
    srand(time(0));
    double hp[] = {100.0, 100.0, 150.0, 150.0, 200.0, 200.0};   //รอแก้ไขให้สมดุล
    double def[] = {20.0, 20.0, 40.0, 40.0, 70.0, 70.0};        //รอแก้ไขให้สมดุล
    double atk[] = {50.0, 50.0, 30.0, 30.0, 20.0, 20.0};        //รอแก้ไขให้สมดุล
    double spd[] = {20.0, 20.0, 5.0, 5.0, 1.0, 1.0};            //รอแก้ไขให้สมดุล

    for(int i = 0; i < 6; i++){
        int randomelement = (randomnumber(4) * 7) % 4;
        player[0].pokemon[i].name = namepokemon[i];
        player[0].pokemon[i].element = elementpokemon[randomelement];
        player[0].pokemon[i].hp = hp[i];
        player[0].pokemon[i].def = def[i];
        player[0].pokemon[i].atk = atk[i];
        player[0].pokemon[i].spd = spd[i];

        player[1].pokemon[i].name = namepokemon[i];
        player[1].pokemon[i].element = elementpokemon[randomelement];
        player[1].pokemon[i].hp = hp[i];
        player[1].pokemon[i].def = def[i];
        player[1].pokemon[i].atk = atk[i];
        player[1].pokemon[i].spd = spd[i];
    }
}
*/

//โจมตีปกติ
/*
void takeNomalATK(double &HP, double DEF, double ATK)
{
	HP = HP - (ATK*(1-(DEF/100)));
}
*/

//โจมตีแบบ strike
/*
void takeStrike(double &HP, double DEF, double ATK, double SPD1,double SPD2)
{
	double skATK = ATK + (abs(SPD1 - SPD2)*10);
	takeNomalATK(HP, DEF, skATK);
}
*/
//กดป้องกัน
/*
void defATK(double &HP, double DEF, double ATK)
{
	DEF *= 2;
	takeNomalATK(HP, DEF, ATK);
}
*/
//กลไกรการหลบหลีก incomplete
/*
int evade()
{
	int rate = rand()%100 + 1;
	return rate;
}
*/

//computer choices
int comChoice()
{
	int choices[] = {1, 2, 3, 4};
	return choices[rand()%4];
}

//turn base system
/*
void turnbase(int p1, int p2)
{
	int gameState = (p1 << 8) | p2;
		switch (gameState)
		{
			case(1 << 8) | 1:
				if(player[0].pokemon[player[0].pokeplayer].spd > player[1].pokemon[player[1].pokeplayer].spd)
				{
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(player[0].pokemon[player[0].pokeplayer].hp
                    , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack

				}else
				{
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(player[0].pokemon[player[0].pokeplayer].hp
                    , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
				}
				break;

			case(1 << 8) | 2:
				if(player[0].pokemon[player[0].pokeplayer].spd > player[1].pokemon[player[1].pokeplayer].spd)
				{
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk);    //player 1 nomal attack
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeStrike(player[0].pokemon[player[0].pokeplayer].hp
                    , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk
                    , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);    //player 2 strike
				}else
				{
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeStrike(player[0].pokemon[player[0].pokeplayer].hp
                        , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk
                        , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);     //player 2 strike
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(player[1].pokemon[player[1].pokeplayer].hp
                        , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk);     //player 1 nomal attack
				}
				break;

			case(1 << 8) | 3:
				if(player[1].pokemon[player[1].pokeplayer].spd < evade()) defATK(player[1].pokemon[player[1].pokeplayer].hp
                , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk);        //player 1 nomal attack player 2 defend
				break;

			case(1 << 8) | 4:
				if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeNomalATK(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk);         //player 1 nomal attack
				break;

			case(2 << 8) | 1:
				if(player[0].pokemon[player[0].pokeplayer].spd > player[1].pokemon[player[1].pokeplayer].spd)
				{
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeStrike(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk
                    , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);    //player 1 strike
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(player[0].pokemon[player[0].pokeplayer].hp
                        , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk);    //player 2 nomal attack    //player 2 nomal attack
				}else
				{
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeNomalATK(player[0].pokemon[player[0].pokeplayer].hp
                        , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk);   //player 2 nomal attack
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeStrike(player[1].pokemon[player[1].pokeplayer].hp
                        , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk
                        , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);   //player 1 strike
				}
				break;

			case(2 << 8) | 2:
				if(player[0].pokemon[player[0].pokeplayer].spd > player[1].pokemon[player[1].pokeplayer].spd)
				{
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeStrike(player[1].pokemon[player[1].pokeplayer].hp
                        , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk
                        , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);    //player 1 strike
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeStrike(player[0].pokemon[player[0].pokeplayer].hp
                        , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk
                        , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);     //player 2 strike
				}else
				{
					if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeStrike(player[0].pokemon[player[0].pokeplayer].hp
                        , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk
                        , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);    //player 2 strike
					if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeStrike(player[1].pokemon[player[1].pokeplayer].hp
                        , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk
                        , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);     //player 1 strike
				}

			case(2 << 8) | 3:
				if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeStrike(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk
                    , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);    //player 1 strike
				break;

			case(2 << 8) | 4:
				if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeStrike(player[0].pokemon[player[0].pokeplayer].hp
                    , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk
                    , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);      //player 2 strike
				break;
			
			case(3 << 8) | 1:
				if(player[0].pokemon[player[0].pokeplayer].spd < evade()) defATK(player[0].pokemon[player[0].pokeplayer].hp
                , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk);        //player 2 nomal attack plyer 1 defend
				break;
			
			case(3 << 8) | 2:
				if(player[0].pokemon[player[0].pokeplayer].spd < evade()) takeStrike(player[0].pokemon[player[0].pokeplayer].hp
                    , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk
                    , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);     //player 2 strike
				break;
			
			case(3 << 8) | 3:
				break;
			
			case(3 << 8) | 4:
				break;

			case(4 << 8) | 1:
				if(player[0].pokemon[player[0].pokeplayer].spd < evade()) defATK(player[0].pokemon[player[0].pokeplayer].hp
                    , player[0].pokemon[player[0].pokeplayer].def, player[1].pokemon[player[1].pokeplayer].atk);     //player 2 nomal attack
				break;
			
			case(4 << 8) | 2:
				if(player[1].pokemon[player[1].pokeplayer].spd < evade()) takeStrike(player[1].pokemon[player[1].pokeplayer].hp
                    , player[1].pokemon[player[1].pokeplayer].def, player[0].pokemon[player[0].pokeplayer].atk
                    , player[0].pokemon[player[0].pokeplayer].spd, player[1].pokemon[player[1].pokeplayer].spd);    //player 1 strike
				break;

			case(4 << 8) | 3:
				break;

			case(4 << 8) | 4:
				break;

			default:
				cout << "Invalid input!" << "\n";
		}
	
}
*/


void showpokemon(){
    string input;
    for(int i = 0; i < 6; i++){
        cout << "-------------------------" << endl;
        cout << "Name [" << i+1 << "] : " << namepokemon[i] << endl; 
        cout << "HP : " << hppokemon[i] << endl;
        cout << "DEF : " << defpokemon[i] << endl;
        cout << "ATK : " << atkpokemon[i] << endl;
        cout << "SPD : " << spdpokemon[i] << endl;
        cout << "-------------------------" << endl;
        delaySeconds(0.5);
        if(i != 5){
            cout << ">>> Please Enter to see more <<<" << endl;
            getline(cin, input);
        }
    }
}
/*
void selectpokemon(char who){
    cout << "Please select Player 1's Pokemon : ";
    cin >> player[0].pokeplayer;
    cout << "--------------------------------------------------" << endl;
    cout << "Player 1's Pokemon : " << player[0].pokemon[--player[0].pokeplayer].name << endl;
    cout << "--------------------------------------------------" << endl;
    if(who == 'P'){
        cout << "Please select Player 2's Pokemon : ";
        cin >> player[1].pokeplayer;
        cout << "Player 2's Pokemon : " << player[1].pokemon[--player[1].pokeplayer].name << endl;
    }
    else{
        player[1].pokeplayer = (randomnumber(6) * 7) % 6;
        cout << "Computer's Pokemon : " << player[1].pokemon[player[1].pokeplayer].name << endl;
    }
    cout << "--------------------------------------------------" << endl;
    
}*/
