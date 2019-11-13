//Test driver for PlayerClass

#include "player3.h"

int main(){

    PlayerClass p1, p2;

    p1.SetPlayer("c1");
    p1.LearnedWeapon("dAgGer");
    p1.LearnedWeapon("gas bomb");
    p1.WriteWeaponHistory(cout);

    return 0;
}
