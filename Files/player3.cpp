//Myah Enochs
//CSCI230
//Fall 2019
//Program 3 Class Definitions

#include "player3.h"

//CONSTANTS ----------------------------------------------------------

const string PlayerClass::WPN_FILE = "weapons.in";     
const string PlayerClass::HUMANS_FILE = "humans.in";   
const string PlayerClass::ZOMBIES_FILE = "zombies.in"; 

const char PlayerClass::DEL = '#';            
const char PlayerClass::DATE_SEP = '/';     
const int PlayerClass::END = '\n';           
const string PlayerClass::NO_INPUT = "NONE";  


//CONSTRUCTORS AND DESTRUCTORS ----------------------------------------

PlayerClass::PlayerClass(){
    set = currentWeapon.set = armor.set = active = false;
}


//PUBLIC OBSERVERS ---------------------------------------------------

string PlayerClass::Name() const{
    if(PlayerSet()){
        return name;
    }
    else{
        return "";
    }
}

int PlayerClass::GetBrawn() const{
    if(PlayerSet()){
        return brawn;
    }
    else{
        return 0;
    }
}

int PlayerClass::GetDex() const{
    if(PlayerSet()){
        return dexterity;
    }
    else{
        return 0;
    }
}

int PlayerClass::GetIntel() const{
    if(PlayerSet()){
        return intelligence;
    }
    else{
        return 0;
    }
}

int PlayerClass::GetHealth() const{
    if(PlayerSet()){
        return health;
    }
    else{
        return 0;
    }
    
}


bool PlayerClass::IsDead() const{
    bool dead = false;
    if(PlayerSet()){
        if(IsZombie() || health == 0){
            dead = true;
        }
    }

    return dead;
}

bool PlayerClass::IsActive() const{
    return active;
}

bool PlayerClass::IsProtector() const{
    bool prot = false;
    if(PlayerSet()){
        if (pClass == PROTECTOR){
            prot = true;
        }
    }
    return prot;
}

bool PlayerClass::IsCannibal() const{
    bool cann = false;
    if(PlayerSet()){
        if (pClass == CANNIBAL){
            cann = true;
        }
    }
    return cann;
}

bool PlayerClass::IsCrazy() const{
    bool craz = false;
    if(PlayerSet()){
        if (pClass == CRAZY){
            craz = true;
        }
    }
    return craz;
}


bool PlayerClass::HasWeapon() const{
    return currentWeapon.set;
}

bool PlayerClass::KnowWeapon(string weapon) const{
    return weaponList.IsPresent(weapon);
}

string PlayerClass::WeaponName() const{
    if(PlayerSet()){
        return currentWeapon.name;
    }
    else{
        return "";
    }
}

int PlayerClass::WeaponDamage() const{
    if(PlayerSet()){
        return currentWeapon.damage;
    }
    else{
        return 0;
    }
    
}


bool PlayerClass::HasArmor() const{
    return armor.set;
}

string PlayerClass::ArmorName() const{
    return ArmorTypeToString(armor.name);
}

int PlayerClass::ArmorDAV() const{
    if(PlayerSet()){
        return armor.dav;
    }
    else{
        return 0;
    }
}


int PlayerClass::Damage() const{
    int damage = 0;

    if(PlayerSet()){
        int diceMult = ((rand()%6)+1);

        if(HasWeapon()){
            damage = WeaponDamage()*diceMult + GetBrawn()/2;
        }
        else{
            damage = GetBrawn()*diceMult;
        }
    }

    return damage;
}

int PlayerClass::Defense() const{
    int defense = 0;

    if(PlayerSet()){
        int diceMult = ((rand()%6)+1);

        if(HasArmor()){
            defense = ArmorDAV()*diceMult*2 + 10;
        }
        else{
            defense = diceMult*2 + 10;
        }
    }

    return defense;
}

void PlayerClass::Write(ostream & out) const{
    if(PlayerSet()){
        if(IsHuman()){ //line#name#campaign#brawn#dex#intell#
            WriteHuman(out);
        }
        else{ //line#name#type#mm/dd/yy#brawn#dex#intell#
            WriteZombie(out);
        }

        if(HasWeapon()){
            WriteWeapon(out);
        }

        if(HasArmor()){
            WriteArmor(out);
        }
        out << endl;
    }
    return;
}

void PlayerClass::WriteWeaponHistory(ostream &out){
    if(!weaponList.IsEmpty()){
        out << name << DEL;
        out << PlayerTypeChar << DEL;
        weaponList.Reset();
        for(int i = 0; i < weaponList.Length(); i++){
            //Ask how the fuck to do this on Friday (or look it up?)
        }
    }
}


//PUBLIC TRANSFORMERS ----------------------------------------------

bool PlayerClass::SetPlayer(string newName){
    bool valid = false;
    if (ValidatePlayer(newName)){
        valid = true;
        set = true;
        active = true;
        armor.set = false;
        currentWeapon.set = false;
        SetValidPlayer(newName);
    }

    return valid;
}

bool PlayerClass::SetWeapon(string newWeapon){
    bool valid = false;
    if(PlayerSet() && WeaponExists(newWeapon)){
        valid = currentWeapon.set = true;
        SetValidWeapon(newWeapon);

        if (!weaponList.IsPresent(currentWeapon.name)){
            weaponList.Insert(currentWeapon.name);
        }
    }
    return valid;
}

bool PlayerClass::SetArmor(string newArmor){
    bool valid = false;
    if(PlayerSet() && ArmorExists(newArmor)){
        SetValidArmor(newArmor);
        valid = true;
    }

    return valid;
}

void PlayerClass::LoseArmor(){
    if (PlayerSet()){
        armor.set = false;
    }

    return;
}

void PlayerClass::LoseWeapon(){
    if (PlayerSet()){
        weaponList.Delete(currentWeapon.name);
        currentWeapon.set = false;
    }
    return;
}

bool PlayerClass::SwapWeapon(string weapon){
    bool swap = weaponList.IsPresent(weapon);
    if(swap){
        SetWeapon(weapon);
    }
    return swap;
}

bool PlayerClass::LearnedWeapon(string weapon){
    bool learn = PlayerSet() && WeaponExists(weapon);
    if(learn){
        weaponList.Insert(weapon);
    }
    return learn;
}

void PlayerClass::Amnesia(){
    LoseWeapon();
    weaponList.MakeEmpty();
}

int PlayerClass::Wounded(int damage){
    if(PlayerSet() && IsActive() && damage > 0){
        health = health - damage;
        if (health <= 0){
            health = 0;
            MakeInActive();
        }
    }
    return health;
}

void PlayerClass::MakeInActive(){
    active = false;
}

//PRIVATE OBSERVERS -----------------------------------------------

bool PlayerClass::PlayerSet() const{
    return set;
}

bool PlayerClass::ValidatePlayer(string newName) const{
    bool valid = false;

    if(NameExists(newName, HUMANS_FILE) != NameExists(newName, ZOMBIES_FILE)){
        valid = true;
    }

    return valid;
}

bool PlayerClass::NameExists(string newName, string inFile) const{
    bool valid = false;
    ifstream fin;
    string fName, uName = Ucase(newName);

    fin.open(inFile.c_str());
    do{
        getline(fin, fName, DEL);
        if (Ucase(fName) != uName){
            fin.ignore(255, END);
        }
    } while (Ucase(fName) != uName && !fin.eof());
    fin.close();

    if(Ucase(fName) == uName){
        valid = true;
    }

    return valid;
}

bool PlayerClass::WeaponExists(string newWeapon) const{
    bool valid = false;
    ifstream fin;
    string fWpn, uWpn = Ucase(newWeapon);

    fin.open(WPN_FILE.c_str());
    do{
        getline(fin, fWpn, DEL);
        if (Ucase(fWpn) != uWpn){
            fin.ignore(255, END);
        }
    } while (Ucase(fWpn) != uWpn && !fin.eof());
    fin.close();

    if(Ucase(fWpn) == uWpn){
        valid = true;
    }

    return valid;
}

bool PlayerClass::ArmorExists(string newArmor) const{
    bool valid = (Ucase(newArmor) == NO_INPUT);
    //Checks for NONE seperately because StringToArmorType returns NONE as default.
    if(!valid){
        switch (StringToArmorType(newArmor)){
            case BREASTPLATE:
            case CHAINMAIL:
            case LEATHER:
            case TACTICALVEST:
                valid = true;
        }
    }
    return valid;
}

PlayerClass::PlayerType PlayerClass::GetType() const{
    return pClass;
}

void PlayerClass::WriteHuman(ostream& out) const{
    out << Name() << DEL;
    out << CampaignTypeToChar(type.human.campaign) << DEL;
    out << GetBrawn() << DEL;
    out << GetDex() << DEL;
    out << GetIntel() << DEL;
    out << GetHealth() << DEL;
}

void PlayerClass::WriteZombie(ostream& out) const{
    out << Name() << DEL;
    out << PlayerTypeChar(pClass) << DEL; 
    if (type.zombie.iDate.month < 10) {out << 0;};
    out << type.zombie.iDate.month << DATE_SEP;
    if (type.zombie.iDate.day < 10) {out << 0;};
    out << type.zombie.iDate.day << DATE_SEP;
    out << type.zombie.iDate.year << DEL;
    out << GetBrawn() << DEL;
    out << GetDex() << DEL;
    out << GetIntel() << DEL;
    out << GetHealth() << DEL;
}

void PlayerClass::WriteWeapon(ostream& out) const{
    out << WeaponName() << DEL;
    out << WeaponDamage() << DEL;
}

void PlayerClass::WriteArmor(ostream& out) const{
    out << ArmorTypeToChar(armor.name) << DEL;
    out << ArmorDAV() << DEL;
}


//PRIVATE TRANSFORMERS -----------------------------------------

void PlayerClass::SetValidPlayer(string newName){
    if(NameExists(newName, HUMANS_FILE)){
        SetHuman(newName);
    }
    else if (NameExists(newName, ZOMBIES_FILE)){
        SetZombie(newName);
    }
}

void PlayerClass::SetHuman(string newName){
    ifstream fin;
    string fName;
    newName = Ucase(newName);

    fin.open(HUMANS_FILE.c_str());
    do{ //Tries to find a match for the name
        getline(fin, fName, DEL);
        if (Ucase(fName) != newName){
            fin.ignore(255, END);
        }
    }while (Ucase(fName) != newName && !fin.eof());

    if(Ucase(fName) == newName){ //If found, gets the rest of the info on the line
        char tempChar;

        name = fName;
        pClass = PROTECTOR; //Human player is always PROTECTOR

        fin >> tempChar;
        fin.ignore(1, DEL);
        type.human.campaign = CharToCampaignType(tempChar);

        fin >> brawn;
        fin.ignore(1, DEL);

        fin >> dexterity;
        fin.ignore(1, DEL);

        fin >> intelligence;
        fin.ignore(1, DEL);

        fin >> health;
    }
    fin.close();
}

void PlayerClass::SetZombie(string newName){
    ifstream fin;
    string fName;

    newName = Ucase(newName);

    fin.open(HUMANS_FILE.c_str());
    do{ //Tries to find a match for the name
        getline(fin, fName, DEL);
        if (Ucase(fName) != newName){
            fin.ignore(255, END);
        }
    }while (Ucase(fName) != newName && !fin.eof());

    if(Ucase(fName) == newName){ //If found, gets the rest of the info on the line
        char tempChar;

        name = fName;

        fin >> tempChar;
        fin.ignore(1, DEL);
        pClass = CharToPlayerType(tempChar);

        fin >> type.zombie.iDate.month;
        fin.ignore(1, DATE_SEP);

        fin >> type.zombie.iDate.day;
        fin.ignore(1, DATE_SEP);
        
        fin >> type.zombie.iDate.year;
        fin.ignore(1, DEL);

        fin >> brawn;
        fin.ignore(1, DEL);

        fin >> dexterity;
        fin.ignore(1, DEL);

        fin >> intelligence;
        fin.ignore(1, DEL);

        fin >> health;
    }
    fin.close();
}

void PlayerClass::SetValidWeapon(string newWeapon){
    ifstream fin;
    string fWpn;
    newWeapon = Ucase(newWeapon);

    fin.open(WPN_FILE.c_str());
    do{ //Tries to find the weapon name
        getline(fin, fWpn, DEL);
        if (Ucase(fWpn) != newWeapon){ //Ignores the rest of the line if not found
            fin.ignore(255, END);
        }
    }while (Ucase(fWpn) != newWeapon && !fin.eof());

    if (Ucase(fWpn) == newWeapon){ //If found, gets the rest of the line
        currentWeapon.name = fWpn;
        fin >> currentWeapon.damage;
    }
}

void PlayerClass::SetValidArmor(string newArmor){
    armor.name = StringToArmorType(newArmor);
    armor.dav = ArmorTypeToDAV(StringToArmorType(ArmorName()));
    armor.set = (armor.name == NONE);
}


//UTILITY METHODS ---------------------------------------

char PlayerClass::PlayerTypeChar(PlayerType playerType) const{
    switch(playerType){
        case PROTECTOR: return 'P';
        case CANNIBAL:  return 'C';
        case CRAZY:     return 'R';
        default: return 'P';
    }
}

PlayerClass::PlayerType PlayerClass::CharToPlayerType(char character) const{
    switch(character){
        case 'P':
        case 'p': return PROTECTOR;
        case 'C':
        case 'c': return CANNIBAL;
        case 'R':
        case 'r': return CRAZY;
        default:  return PROTECTOR;
    }
}

char PlayerClass::ArmorTypeToChar(ArmorType armorType) const{
    switch(armorType){
        case NONE: return 'N';
        case BREASTPLATE: return 'B';
        case CHAINMAIL: return 'C';
        case LEATHER: return 'L';
        case TACTICALVEST: return 'T';
        default: return 'N';
    }
}

PlayerClass::ArmorType PlayerClass::CharToArmorType(char character) const{
    switch(toupper(character)){
        case 'N': return NONE;
        case 'B': return BREASTPLATE;
        case 'C': return CHAINMAIL;
        case 'L': return LEATHER;
        case 'T': return TACTICALVEST;
        default: return NONE;
    }
}

char PlayerClass::CampaignTypeToChar(CampaignType cType) const{
    switch(cType){
        case GATHER: return 'G';
        case SPY: return 'S';
        case TRAVELER: return 'T';
        case WARRIOR: return 'W';
        default: return 'G';
    }
}

PlayerClass::CampaignType PlayerClass::CharToCampaignType(char character) const{
    switch(toupper(character)){
        case 'G': return GATHER;
        case 'S': return SPY;
        case 'T': return TRAVELER;
        case 'W': return WARRIOR;
        default: return GATHER;
    }
}

PlayerClass::ArmorType PlayerClass::StringToArmorType(string str) const{
    str = Ucase(str);

    if (str == NO_INPUT) {return NONE;}
    else if (str == "BREASTPLATE") {return BREASTPLATE;}
    else if (str == "CHAINMAIL") {return CHAINMAIL;}
    else if (str == "LEATHER") {return LEATHER;}
    else if (str == "TACTICALVEST" || str == "TACTICAL VEST") {return TACTICALVEST;}
    else {return NONE;}
}

string PlayerClass::ArmorTypeToString(ArmorType armor) const{
    switch(armor){
        case NONE: return "None";
        case BREASTPLATE: return "Breastplate";
        case CHAINMAIL: return "Chainmail";
        case LEATHER: return "Leather";
        case TACTICALVEST: return "Tactical Vest";
        default: return "None";
    }
}

int PlayerClass::ArmorTypeToDAV(ArmorType aType) const{
    switch(aType){
        case NONE: return 0;
        case BREASTPLATE: return 4;
        case CHAINMAIL: return 5;
        case LEATHER: return 2;
        case TACTICALVEST: return 6;
        default: return 0;
    }
}

bool PlayerClass::IsHuman() const{
    return IsProtector();
}

bool PlayerClass::IsZombie() const{
    return (IsCannibal() || IsCrazy());
}

string PlayerClass::Ucase(string str) const{
    for (int i = 0; i < str.length(); i++){
        str[i] = toupper(str[i]);
    }
    return str;
}


//TOP-LEVEL FUNCTIONS

void Fight(PlayerClass attacker, PlayerClass &target){
    if(attacker.IsActive() && target.IsActive()){
        int damage = attacker.Damage();
        int defense = target.Defense();
        if(damage - defense > 0){
            target.Wounded(damage);
        }
    }
    return;
}