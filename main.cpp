//Librarys used
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Card.h"

//Function prototypes
int user_input(int range);
void main_menu();
void main_game();
void instructions();

//Variable declarations
Card testCard("name", 1, 1, 1);

int main() {
    main_menu();
}

int user_input(int range) {
    std::string input;

    int int_input;

    while (1) {
        std::cout << "USER INPUT:";
        std::cin >> input;

        try {
            int_input = stoi(input);
        } catch (std::invalid_argument) {
            std::cout << "YOU MUST ENTER AN INTEGER!" << std::endl;
        }
        if (int_input <= range && int_input >= 1) {
            return int_input;
        }
        else {
            std::cout << "INPUT IS OUT OF RANGE!" << std::endl;
        }
    }  
        
    
}

void main_menu() {
    std::cout << "---------->SPACE WARRIOR<----------" << std::endl << std::endl << std::endl << std::endl;
    std::cout << "            -Main Menu-            " << std::endl;
    std::cout << "         1.  Play Game            " << std::endl;
    std::cout << "        2.  Instructions          " << std::endl;
    std::cout << "         3.  Exit Game            " << std::endl;

    int selection = user_input(3);

    if (selection == 1) {
        main_game();
    }
    else if (selection == 2) {
        instructions();
    } else {
        std::cout << "Exiting Game!";
        exit(0);
    }
}

void main_game() {
    std::cout << "Main Game" << std::endl;
    std::cout << testCard.get_name() << std::endl;
    std::cout << testCard.get_attack() << std::endl;
    std::cout << testCard.get_defence() << std::endl;
    std::cout << testCard.get_agility() << std::endl;
}

void instructions() {
    std::cout << "           -Instructions-" << std::endl << std::endl;

    //instructions go here

    std::cout << "Enter 1 to return to the Main Menu" << std::endl;
    int selection = user_input(1);

    if (selection == 1) {
        main_menu();
    }
}