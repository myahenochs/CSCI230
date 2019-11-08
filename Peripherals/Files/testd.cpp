//Test driver for PlayerClass

#include "player3.h"

int main(){

    PlayerClass p1, p2;

    p1.SetPlayer("P4");
    p1.Write(cout); cout << endl;
    cout << "Dead: " << p1.IsDead() << endl;
    cout << "Active: " << p1.IsActive() << endl;
    cout << "Health: " << p1.Wounded(-9) << endl;
    
    cout << endl;

    return 0;
}
