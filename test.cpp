#include<iostream>
#include<string>
#include<cmath>
#include<ctime>

double HP[] = {100, 150, 200};
double DEF[] = {20, 40, 70};
double ATK[] = {50, 30, 20};
double SPD[] = {20, 5, 1};
bool sc;

void takeNomalATK(double &HP, double DEF, double ATK)
{
	HP = HP - (ATK*(1-(DEF/100)));
}

void takeStrike(double &HP, double DEF, double ATK, double SPD1,double SPD2)
{
	double skATK = ATK + (abs(SPD1 - SPD2)*10);
	takeNomalATK(HP, DEF, skATK);
}

void defATF(double &HP, double DEF, double ATK)
{
	DEF *= 2;
	takeNomalATK(HP, DEF, ATK);
}

void evade(double SPD, bool &sc)
{
	sc = false;
	srand(time(0));
	int numb = rand()%100+1;
	std::cout<<numb;
	if(SPD>numb) sc = true;
	else sc = false;
}

int main()
{
	bool sc;
	evade(SPD[0], sc);
}