#include "demoturnbase1.h"

int main()
{
	srand(time(0)); 
    Page1();
    char who = Page2();
    //Page3(who);

    player p1, p2;
    //createpokemon();
    //showpokemon();

    p1.createplayer();
    showpokemon();

    p1.choosepokemon(1);
    if(who == 'C'){
        p2.comchoosepokemon();
    }
    else{
        p2.createplayer();
        showpokemon();
        p2.choosepokemon(2);
    }

    if(who == 'C'){
        while(true)
        {
            /*cout << "Player 1" << "\t\t" << "Player 2" << endl;
            cout << p1 << " HP: " << player[0].pokemon[player[0].pokeplayer].hp << "\t\t";
            cout << player[1].pokemon[player[1].pokeplayer].name << " HP: " << player[1].pokemon[player[1].pokeplayer].hp << "\n";*/
            delaySeconds(1);
            p1.showstat(0, 1);
            p2.showstat(0, 2);

            cout << "[1] Attack [2] Strike [3] Defend [4] counter" << endl;
            cout << "Player'1 Choice : ";
            cin >> p1.playerAction;
            int action1 = p1.playerAction;
            delaySeconds(0.5);
            p2.playerAction = randomnumber(4) + 1;
            cout << "Player'2 Choice : " << p2.playerAction << endl;
            int action2 = p2.playerAction;
            
            cout << "===========================================================================================================" << endl;
            drawscene(action1, p1, action2, p2);
            cout << "===========================================================================================================" << endl;
            cout << endl;
            delaySeconds(1);
            if(p1.isDead(0) && p2.isDead(0)){
                if(p1.checkspd(0) < p2.checkspd(0)){
                    win(2);
                    break;
                }
            }
            else if(p2.isDead(0)){
                win(1);
                break;
            }
            else if(p1.isDead(0)){
                win(2);
                break;
            }
        }
        
    }

    /*selectpokemon(who);
    cout << player[0].pokeplayer << " " << player[1].pokeplayer << endl;
    Pageturnbase(who);*/
    return 0;

}