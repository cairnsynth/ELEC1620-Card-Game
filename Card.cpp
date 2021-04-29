#include "Card.h"
#include <string>

//Card class constructor
Card::Card(std::string name, int attack, int defence, int agility){
    //card variables
    _name = name;
    _attack = attack;
    _defence = defence;
    _agility = agility;

}

