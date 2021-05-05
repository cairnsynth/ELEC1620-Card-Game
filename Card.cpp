//Card class file
#include "Card.h"           //Include the Card header file

#define CARD_WIDTH 31       //Constant variable for the width of each card

Card::Card(std::string name, int attack, int defence, int agility){         //Card class constructor

    set_name(name);                 //card variables for each statistic
    set_attack(attack);
    set_defence(defence);
    set_agility(agility);

}

void Card::print_card(){        //Method that handles printing the card in a more interesting format than just the statistics

    int nameSpacing_ = int((CARD_WIDTH - (5 + name_.length())) / 2);        // Calculating the number of spaces needed either side of the name to centre it on the card

    std::cout << " _____________________________ " << std::endl;            //printing the top of the card
    std::cout << "/                             \\ " << std::endl;
    std::cout << "  ---------------------------  " << std::endl;

    for (int i = 0; i < nameSpacing_; i++) {        //For each space needed, print a space
        std::cout << " ";
    }
    
    std::cout << "Name:" << name_;                  //print the name

    for (int i = 0; i < nameSpacing_; i++) {        //For each space needed, print a space
        std::cout << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "        Attack : " << attack_ << std::endl;           //Print each card statistic on a new line
    std::cout << "       Defence : " << defence_ << std::endl;
    std::cout << "       Agility : " << agility_ << std::endl;
    std::cout << "  ---------------------------  " << std::endl;        //Print the bottom of the card
    std::cout << "\\_____________________________/" << std::endl;
}

