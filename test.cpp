#include<iostream>
#include<string>
#include<cmath>
#include<ctime>

using namespace std;

double HP[] = {100, 150, 200};
double DEF[] = {20, 40, 70};
double ATK[] = {50, 30, 20};
double SPD[] = {20, 5, 1};
bool sc;

void NomalATK(double &HP, double DEF, double ATK)	// โจมตีธรรมดา (1)
{														//
	HP = HP - (ATK*(1-(DEF/100)));
}

void Nomaldef() // skipturn

void Nomalstrike() // active skill ติดตัว

void takeStrike(double &HP, double DEF, double ATK, double SPD1,double SPD2)	// strike vs ป้องกัน
{																				// count vs strike
	double skATK = ATK + (abs(SPD1 - SPD2)*10);
	NomalATK(HP, DEF, skATK);
}

void defATF(double &HP, double DEF, double ATK)	// ป้องกัน vs โจมตี
{
	DEF *= 2;
	takeNomalATK(HP, DEF, ATK);
}



void evade(double SPD, bool &sc) // โอกาสหลบหลีก
{
	sc = false;
	srand(time(0));
	int numb = rand()%100+1;
	cout<<numb;
	if(SPD>numb) sc = true;	// ถ้าสุ่มได้ < spd จะหลบได้
	else sc = false;		
}

int main()
{

	bool sc;
	evade(SPD[0], sc);
}