#include<iostream>
#include<string>
#include<cmath>
#include<ctime>

//รายละเอียด pokemons
struct poke
{
	std::string name;
	double HP, DEF, ATK, SPD;
};

//ประกาศตัวแปร global
poke p[3] = {{"Jesus", 100, 20, 30, 30}, {"Budha", 200, 50, 10, 10}, {"Kungfu", 150, 40, 20, 20}};
int choices[] = {1, 2, 3, 4};	//1 = ตีปกติ, 2 = strike, 3 = ป้องกัน, 4 = counter
bool sc;

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
void turnbase(int p1, int p2, poke &pm1, poke &pm2)
{
	int gameState = (p1 << 8) | p2;
		switch (gameState)
		{
			case(1 << 8) | 1:
				if(pm1.SPD > pm2.SPD)
				{
					if(pm2.SPD < evade()) takeNomalATK(pm2.HP, pm2.DEF, pm1.ATK);
					if(pm1.SPD < evade()) takeNomalATK(pm1.HP, pm1.DEF, pm2.ATK);

				}else
				{
					if(pm1.SPD < evade()) takeNomalATK(pm1.HP, pm1.DEF, pm2.ATK);
					if(pm2.SPD < evade()) takeNomalATK(pm2.HP, pm2.DEF, pm1.ATK);
				}
				break;

			case(1 << 8) | 2:
				if(pm1.SPD > pm2.SPD)
				{
					if(pm2.SPD < evade()) takeNomalATK(pm2.HP, pm2.DEF, pm1.ATK);
					if(pm1.SPD < evade()) takeStrike(pm1.HP, pm1.DEF, pm2.ATK, pm1.SPD, pm2.SPD);
				}else
				{
					if(pm1.SPD < evade()) takeStrike(pm1.HP, pm1.DEF, pm2.ATK, pm1.SPD, pm2.SPD);
					if(pm2.SPD < evade()) takeNomalATK(pm2.HP, pm2.DEF, pm1.ATK);
				}
				break;

			case(1 << 8) | 3:
				if(pm2.SPD < evade()) defATK(pm2.HP, pm2.DEF, pm1.ATK);
				break;

			case(1 << 8) | 4:
				if(pm2.SPD < evade()) takeNomalATK(pm2.HP, pm2.DEF, pm1.ATK);
				break;

			case(2 << 8) | 1:
				if(pm1.SPD > pm2.SPD)
				{
					if(pm2.SPD < evade()) takeStrike(pm2.HP, pm2.DEF, pm1.ATK, pm1.SPD, pm2.SPD);
					if(pm1.SPD < evade()) takeNomalATK(pm1.HP, pm1.DEF, pm2.ATK);
				}else
				{
					if(pm1.SPD < evade()) takeNomalATK(pm1.HP, pm1.DEF, pm2.ATK);
					if(pm2.SPD < evade()) takeStrike(pm2.HP, pm2.DEF, pm1.ATK, pm1.SPD, pm2.SPD);
				}
				break;

			case(2 << 8) | 2:
				if(pm1.SPD > pm2.SPD)
				{
					if(pm2.SPD < evade()) takeStrike(pm2.HP, pm2.DEF, pm1.ATK, pm1.SPD, pm2.SPD);
					if(pm1.SPD < evade()) takeStrike(pm1.HP, pm1.DEF, pm2.ATK, pm1.SPD, pm2.SPD);
				}else
				{
					if(pm1.SPD < evade()) takeStrike(pm1.HP, pm1.DEF, pm2.ATK, pm1.SPD, pm2.SPD);
					if(pm2.SPD < evade()) takeStrike(pm2.HP, pm2.DEF, pm1.ATK, pm1.SPD, pm2.SPD);
				}

			case(2 << 8) | 3:
				if(pm2.SPD < evade()) takeStrike(pm2.HP, pm2.DEF, pm1.ATK, pm1.SPD, pm2.SPD);
				break;

			case(2 << 8) | 4:
				if(pm1.SPD < evade()) takeStrike(pm1.HP, pm1.DEF, pm2.ATK, pm1.SPD, pm2.SPD);
				break;
			
			case(3 << 8) | 1:
				if(pm1.SPD < evade()) defATK(pm1.HP, pm1.DEF, pm2.ATK);
				break;
			
			case(3 << 8) | 2:
				if(pm1.SPD < evade()) takeStrike(pm1.HP, pm1.DEF, pm2.ATK, pm1.SPD, pm2.SPD);
				break;
			
			case(3 << 8) | 3:
				break;
			
			case(3 << 8) | 4:
				break;

			case(4 << 8) | 1:
				if(pm1.SPD < evade()) takeNomalATK(pm1.HP, pm1.DEF, pm2.ATK);
				break;
			
			case(4 << 8) | 2:
				if(pm2.SPD < evade()) takeStrike(pm2.HP, pm2.DEF, pm1.ATK, pm1.SPD, pm2.SPD);
				break;

			case(4 << 8) | 3:
				break;

			case(4 << 8) | 4:
				break;

			default:
				std::cout << "Invalid input!" << "\n";
		}
	
}

int main()
{
	srand(time(0)); 
    poke *pm1 = &p[rand() % 3], *pm2 = &p[rand() % 3];
    int p1, p2;
	while(pm1->HP > 0 && pm2->HP > 0)
	{
		std::cout << pm1->name << " HP: " << pm1->HP << "\n";
		std::cout<<"Player'1 Choice : ";
		std::cin>>p1;
		std::cout << pm2->name << " HP: " << pm2->HP << "\n";
		p2 = comChoice();
		std::cout<<"Player'2 Choice : "<<p2<<"\n";
		turnbase(p1, p2, *pm1, *pm2);
		std::cout<<"-------------------------------------------------------------\n\n";
	}
	if(pm1->HP<=0) std::cout<<"Player'2 WIN\n";
	else std::cout<<"Player'1 WIN\n";
}