#include "Card.h"
#include <string>

//Card class constructor
Card::Card(std::string name, int attack, int defence, int agility){
    //card variables
    name_ = name;
    attack_ = attack;
    defence_ = defence;
    agility_ = agility;

}

void Card::print_card(){
    std::cout << "_________________________" << std::endl;
    std::cout << "       Name : " << name_ << std::endl;
    std::cout << "     Attack : " << attack_ << std::endl;
    std::cout << "    Defence : " << defence_ << std::endl;
    std::cout << "    Agility : " << agility_ << std::endl;
    std::cout << "_________________________" << std::endl;
}

