//Librarys used
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Card.h"
#include "json.hpp"
#include <fstream>

//Function prototypes
int user_input(int range);
void main_menu();
void main_game();
void instructions();
void view_deck();
void playerTurn();
void cpuTurn();
void deal_hands();

using json = nlohmann::json;

//Variable declarations

json cards;


std::vector<Card> deck;
std::vector<Card> playerHand;
std::vector<Card> cpuHand;

int main() {

    //https://rachelnertia.github.io/programming/2016/07/03/json-hpp/
    std::ifstream cardsFile("Cards.json", std::ifstream::binary);
    cards = json::parse(cardsFile);
    cardsFile.close();

    for (int i = 0; i < cards.size(); i++){
        Card tempCard(cards[i]["Name"].dump(), stoi(cards[i]["Attack"].dump()), stoi(cards[i]["Defence"].dump()), stoi(cards[i]["Agility"].dump()));
        deck.push_back(tempCard);
    }

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
    std::cout << "            -Main Menu-            " << std::endl << std::endl;
    std::cout << "         1.  Play Game            " << std::endl;
    std::cout << "        2.  Instructions          " << std::endl;
    std::cout << "         3.  View Deck          " << std::endl;
    std::cout << "         4.  Exit Game            " << std::endl;

    int selection = user_input(4);

    switch (selection) {
    case 1:
        main_game();
    
    case 2:
        instructions();

    case 3:
        view_deck();

    case 4:
        std::cout << "Exiting the game!";
        exit(0);
    }
}

void main_game() {
    std::cout << "Main Game" << std::endl;
}

void instructions() {
    std::cout << "           -Instructions-" << std::endl << std::endl;

    //instructions go here

    std::cout << "Enter 1 to return to the Main Menu" << std::endl;
    int selection = user_input(1);
    switch (selection) {
        case 1:
            main_menu();
    }
}

void playerTurn(){
    std::cout << "Your turn!" << std::endl;
    std::cout << "Choose a card from your deck:" << std::endl;
}

void deal_hands() {

}

void view_deck() {
    std::cout << "            -Current Deck-            " << std::endl << std::endl << std::endl;

    for (int i = 0; i < deck.size(); i++) {
        deck[i].print_card();
    }

    std::cout << "Enter 1 to return to  the Main Menu" << std::endl;
    int selection = user_input(1);
    switch (selection) {
    case 1:
        main_menu();
    }
}