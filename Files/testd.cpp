//Test driver for PlayerClass

#include "player3.h"

int main(){

    PlayerClass p1, p2;

    p1.SetPlayer("P4");
    p1.SetWeapon("Dagger");
    p1.LearnedWeapon("Baretta");
    p1.LearnedWeapon("baton");

    p1.WriteWeaponHistory(cout);

    return 0;
}
