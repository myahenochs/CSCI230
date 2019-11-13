//Myah Enochs
//CSCI230
//Fall 2019
//Program 3 Class Declaration
//This class is a player that includes weapons and armor.

//To-do:
    //Rename pClass to something more intuitive
    //Get rid of extra out statements

#ifndef _PLAYERCLASSH
#define _PLAYERCLASSH

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "list.h"

using namespace std;

class PlayerClass{

    //USER-DEFINED DATA TYPES --------------------------------

        enum PlayerType {PROTECTOR, CANNIBAL, CRAZY};
        enum ArmorType {NONE, BREASTPLATE, CHAINMAIL, LEATHER, TACTICALVEST};
        enum CampaignType {GATHER, SPY, TRAVELER, WARRIOR};
        enum StatType {HEALTH, DEX, INT, BRAWN};

        struct DateRec{
            int day, month, year;
        };
        struct WpnRec{
            string name;
            int damage;
            bool set;
        };
        struct ArmorRec{
            ArmorType name;
            int dav;
            bool set;
        };
        struct HumanRec{
            CampaignType campaign;
        };
        struct ZombieRec{
            DateRec iDate;
        };
        struct TypeRec{
            HumanRec human;
            ZombieRec zombie;
        };
        struct InputRec{
            string name;
            string wpn;
            string armor;
        };

    public:

    //CONSTRUCTORS AND DESTRUCTORS ---------------------------

        PlayerClass();

    //PUBLIC METHODS ------------------------------------------

    //Observers

        //Getters

        string Name() const;
        int GetBrawn() const;
        int GetDex() const;
        int GetIntel() const;
        int GetHealth() const;
        void GetStats(int stats[]) const;
        
        bool PlayerSet() const;
        bool IsDead() const;
        bool IsActive() const;
        bool IsProtector() const;
        bool IsCannibal() const;
        bool IsCrazy() const;

        bool HasWeapon() const;
        bool KnowWeapon(string weapon) const;
        string WeaponName() const;
        int WeaponDamage() const;

        bool HasArmor() const;
        string ArmorName() const;
        int ArmorDAV() const;
        

        int Damage() const;
        //Narrative: Calculates the player's damage value.
        //Post-Condition: Returns the damage if the player is set, 0 otherwise.

        int Defense() const;
        //Narrative: Calculates the player's defense value.
        //Post-Condition: Returns the defense if the player is set, 0 otherwise.

        void Write(ostream & out) const;
        //Narrative: Writes the player to the out parameter in the correct format.
        //Pre-Condition: An existing ostream must be input.
        //Post-Condition: The player is output and the function exits.

        void WriteWeaponHistory(ostream &out);
        //
        //
        //

        char PlayerTypeChar(PlayerType playerType) const;
        //Narrative: Converts a PlayerType into the corrosponding uppercase character.
        //Pre-Condition: A PlayerType is input.
        //Post-Condition: The PlayerType is converted and a character is returned.

    //Transformers

        bool SetPlayer(string newName);
        //Narrative: Sets the player fields based on the new player name, if it is valid.
        //Pre-Condition: A valid string must be input.
        //Post-Condition: Returns true and sets the player information if newName is valid,
            //false and makes no change otherwise.

        bool SetWeapon(string newWeapon);
        //Narrative: Sets the weapon fields based on the new weapon name, if it is valid.
        //Pre-Condition: A valid string must be input.
        //Post-Condition: Returns true and sets the weapon information if newWeapon is valid,
            //false and makes no change otherwise.

        bool SetArmor(string newArmor);
         //Narrative: Sets the armor values based on the passed string.
        //Pre-Condition: A valid string must be input.
        //Post-Condition: Returns true and sets the armor name and DAV if valid, false otherwise.

        void LoseArmor();
        //Narrative: Makes the player lose their armor.
        //Pre-Condition: None.
        //Post-Condition: Sets armor.set to false and returns.

        void LoseWeapon();
        //Narrative: Makes the player lose their weapon.
        //Pre-Condition: None.
        //Post-Condition: Sets currentWeapon.set to false and returns.

        bool SwapWeapon(string weapon);
        //
        //
        //

        bool LearnedWeapon(string weapon);
        //
        //
        //

        void Amnesia();
        //
        //
        //

        int Wounded(int damage);
        //Narrative: Wounds the player by an amount of damage defined as the parameter.
        //Pre-Condition: An integer must be passed in.
        //Post-Condition: If the player is active, set, and has a health above zero, the amount of damage is subtracted
            //from the existing health. If the player has negative health, sets active to false and health to 0. 
            //Returns player health after all calculations are finished.

        void MakeInActive();
        //Narrative: Makes the player inactive.
        //Pre-Condition: None.
        //Post-Condition: Sets active to false and returns.


    private:

    //PRIVATE CONSTANTS -----------------------------------------

    static const string WPN_FILE;      //File containing weapon information.
    static const string HUMANS_FILE;   //File containing human player information.
    static const string ZOMBIES_FILE;  //File containing zombie player information.

    static const char DEL;             //Delimiter used for separating values in file input and output.
    static const char DATE_SEP;        //Delimiter used for separating the numbers in dates.
    static const int END;              //End line character.
    static const string NO_INPUT;      //String that represents no input data for the field.

    #define STAT_AMNT 4


    //PRIVATE DATA --------------------------------------------

        string name;
        PlayerType pClass;
        TypeRec type;
        int stats[STAT_AMNT];
        int brawn, dexterity, intelligence, health;
        ArmorRec armor;
        WpnRec currentWeapon;
        List weaponList;
        bool active;
        bool set;

    //PRIVATE METHODS ------------------------------------------

    //Observers


        bool ValidatePlayer(string newName) const;
        //Narrative: Checks if the player name exists.
        //Pre-Condition: A string that can contain spaces is input.
        //Post-Condition: Returns true if the player exists in either the humans file or the zombies file.
            //False otherwise.

        bool NameExists(string newName, string inFile) const;
        //Narrative: Finds the name inside of the passed file name.
        //Pre-condition: A valid string must be input.
        //Post-condition: Returns true if the player exists, false otherwise.

        bool WeaponExists(string newWeapon) const;
        //Narrative: Finds the user-input weapon inside of the weapons file.
        //Pre-condition: A valid string must be input.
        //Post-condition: Returns true if the weapon exists, false otherwise.

        string FileWeaponName(string newWeapon) const;
        //
        //
        //

        bool ArmorExists(string newArmor) const;
        //Narrative: Checks if the armor is one of the ArmorTypes other than NONE.
        //Pre-condition: A valid string is input.
        //Post-Condition: Returns true if it is a valid ArmorType, false otherwise.

        PlayerType GetType() const;
        //Narrative: Returns the PlayerType pClass.

        void WriteHuman(ostream& out) const;
        //Narrative: Prints the human data in the correct format to the ostream.
        //Pre-Condition: A valid ostream must be passed in.
        //Post-Condition: None.

        void WriteZombie(ostream& out) const;
        //Narrative: Prints the zombie data in the correct format to the ostream.
        //Pre-Condition: A valid ostream must be passed in.
        //Post-Condition: None.

        void WriteWeapon(ostream& out) const;
        //Narrative: Prints the weapon data in the correct format to the ostream.
        //Pre-Condition: A valid ostream must be passed in.
        //Post-Condition: None. 

        void WriteArmor(ostream& out) const;
        //Narrative: Prints the armor data in the correct format to the ostream.
        //Pre-Condition: A valid ostream must be passed in.
        //Post-Condition: None.


    //Transformers

        void SetValidPlayer(string newName);
        //Narrative: Sets the fields of a validated player from the respective file.
        //Pre-Condition: A player name that exists in either the humans or zombies file is passed in.
        //Post-Condition: All fields relevant to the type of player are set to what is in the file.

        void SetHuman(string newName);
        //Narrative: Sets a human player from the humans file.
        //Pre-Condition:  The player name must exist inside the humans file.
        //Post-Condition: All fields relevant to a human player are set to what is in the file.

        void SetZombie(string newName);
        //Narrative: Sets a zombie player from the zombies file.
        //Pre-Condition:  The player name must exist inside the zombies file.
        //Post-Condition: All fields relevant to a zombie player are set to what is in the file.

        void SetValidWeapon(string newWeapon);
        //Narrative: Sets a weapon from the weapons file.
        //Pre-Condition: The weapon name must exist inside the weapons file.
        //Post-Condition: All fields relevant to the weapon are set to what is in the file.

        void SetValidArmor(string newArmor);
        //Narrative: Sets the armor fields respectively to the input.
        //Pre-Condition: A string that is validated to be an ArmorType must be passed in.
        //Post-Condition: The string is converted to an ArmorType and set as the armor name.
            //The name is then converted to the DAV and set to the armor DAV.


    //UTILITY METHODS ------------------------------------------


        PlayerType CharToPlayerType(char character) const;
        //Narrative: Converts a character into the corrosponding PlayerType.
        //Pre-Condition: A character is input.
        //Post-Condition: The character is converted and the PlayerType is returned.

        char ArmorTypeToChar(ArmorType armorType) const;
        //Narrative: Converts an ArmorType into the corrosponding uppercase character.
        //Pre-Condition: An ArmorType is input.
        //Post-Condition: The PlayerType is converted and a character is returned.

        ArmorType CharToArmorType(char character) const;
        //Narrative: Converts a character into the corrosponding ArmorType.
        //Pre-Condition: A character is input.
        //Post-Condition: The character is converted and the ArmorType is returned.

        char CampaignTypeToChar(CampaignType cType) const;
        //Narrative: Converts a CompaignType into the corrosponding uppercase character.
        //Pre-Condition: A CapmaignType is input.
        //Post-Condition: The PlayerType is converted and a character is returned.

        CampaignType CharToCampaignType(char character) const;
        //Narrative: Converts a character into the corrosponding CampaignType.
        //Pre-Condition: A character is input.
        //Post-Condition: The character is converted and the CampaignType is returned.

        ArmorType StringToArmorType(string str) const;
        //Narrative: Converts a string to the corrosponding ArmorType.
        //Pre-Condition: A string is input.
        //Post-Condition: The string is converted and an ArmorType is returned.

        string ArmorTypeToString(ArmorType armor) const;
        //
        //
        //

        int ArmorTypeToDAV(ArmorType aType) const;
        //Narrative: Converts the ArmorType into its corrosponding Defensive Armor Value (DAV).
        //Pre-Condition: An ArmorType is input.
        //Post-Condition: The ArmorType is converted and an integer is returned.

        bool IsHuman() const;
        //Narrative: Determines if the player is human.
        //Pre-Condition: A valid PlayerRec is input.
        //Post-Condition: Returns true if the player is human (PROTECTOR), false otherwise.

        bool IsZombie() const;
        //Narrative: Determines if the player is a zombie.
        //Pre-Condition: A valid PlayerRec is input.
        //Post-Condition: Returns true if the player is a zombie (CANNIBAL or CRAZY), false otherwise.

        InputRec ClearInput() const;
        //Narrative: Sets all values inside of an InputRec to their defaults (empty strings).
        //Pre-Condition: An InputRec is set equal to the return value of this function.
        //Post-Condition: An InputRec with all values set is returned.

        string Ucase(string str) const;
        //Narrative: Gets a string input and converts all characters in the string to uppercase
        //Pre-condition: A string is sent to the function.
        //Post-condition: the uppercased string is returned.

};

//TOP-LEVEL FUNCTIONS ------------------------------------------

void Fight(PlayerClass attacker, PlayerClass &target);
//Narrative: The two input PlayerClasses "fight" using their brawn stat, weapon, and armor (if applicable).
//Pre-Condition: Two PlayerClasses are passed in.
//Post-Condition: If the damage of the attacker is greater than the defense of the target, 
    //the target is Wounded. If the damage is enough to kill the target, the target is no longer
    //active and its health is set to 0.

#endif