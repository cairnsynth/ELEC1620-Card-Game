//Librarys used
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Card.h"
#include "json.hpp"
#include <fstream>
#include <ctime>
#include <cmath>

//Function prototypes
void clear_screen();
int user_input(int range);
void main_menu();
void game_setup();
void instructions();
void view_deck();
void playerTurn();
void cpuTurn();
void deal_hands(int handSize);
void game_loop();

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
        try {
            Card tempCard(cards[i]["Name"].dump(), stoi(cards[i]["Attack"].dump()), stoi(cards[i]["Defence"].dump()), stoi(cards[i]["Agility"].dump()));
            deck.push_back(tempCard);
        } catch(...) {
            std::cout << "ERROR READING Cards.json: INCORRECT FORMATTING" << std::endl;
            std::cout << "Ensure Cards.json follows the correct formatting:" << std::endl;
            std::cout << "{" << std::endl;
            std::cout << "  \"Name\":\"card_name\"," << std::endl;
            std::cout << "  \"Attack\":attack_value," << std::endl;
            std::cout << "  \"Defence\":defence_value," << std::endl;
            std::cout << "  \"Agility\":agility_value" << std::endl;
            std::cout << "}," << std::endl << std::endl;
            std::cout << "Exiting game";

            exit(1);
        }
    }

    main_menu();
}

void clear_screen(){
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
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
        if (range == -1) {
            if (int_input > 0) {
                return int_input;
            } else {
                std::cout << "INPUT MUST BE GREATER THAN 0" << std::endl;
            }
            
        } else {
            if (int_input <= range && int_input >= 1) {
                return int_input;
            }
            else {
                std::cout << "INPUT IS OUT OF RANGE!" << std::endl;
            }
        }
        
    }  
        
    
}

void main_menu() {
    clear_screen();

    std::cout << "---------->SPACE WARRIOR<----------" << std::endl << std::endl << std::endl << std::endl;
    std::cout << "            -Main Menu-            " << std::endl << std::endl;
    std::cout << "         1.  Play Game            " << std::endl;
    std::cout << "        2.  Instructions          " << std::endl;
    std::cout << "         3.  View Deck          " << std::endl;
    std::cout << "         4.  Exit Game            " << std::endl;

    int selection = user_input(4);

    switch (selection) {
    case 1:
        game_setup();
    
    case 2:
        instructions();

    case 3:
        view_deck();

    case 4:
        std::cout << "Exiting the game!";
        exit(0);
    }
}

void game_setup() {
    //resets player and CPU hands
    playerHand.clear();
    cpuHand.clear();

    clear_screen();

    std::cout << "           -Main Game-" << std::endl << std::endl << std::endl;
    std::cout << "Enter the size of deck you wish to play with" << std::endl;
    
    //Dealing player and CPU hands
    int handSize = user_input(-1);
    deal_hands(handSize);

    clear_screen();
    std::cout << "You have been delt the following cards, good luck!"<< std::endl << std::endl;

    for (Card c : playerHand) {
        c.print_card();
    }

    std::cout << "Enter 1 to begin game"<< std::endl;
    int selection = user_input(1);
    switch (selection)
    {
    case 1:
        game_loop();
    }
    
}

void instructions() {
    clear_screen();

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
    clear_screen();

    std::cout << "Your turn!" << std::endl << std::endl;
    std::cout << "Choose a card from your hand:" << std::endl;
    for (Card c : playerHand) {
        c.print_card();
    }
    int playerSelection = (user_input(playerHand.size()) - 1);
    Card playerCard = playerHand[playerSelection];

    int cpuSelection = rand() % cpuHand.size();
    Card cpuCard = cpuHand[cpuSelection];

    clear_screen();
    std::cout << "Choose a statistic to play from your chosen card!" << std::endl;

    playerCard.print_card();
    int playerStat = user_input(3);
    int playerValue;
    int cpuValue;

    if (playerStat == 1) {
        playerValue = playerCard.get_attack();
        cpuValue = cpuCard.get_attack();

        std::cout << "You chose the attack statistic, with a value of: " << playerValue << std::endl << std::endl;
    } else if (playerStat == 2) {
        playerValue = playerCard.get_defence();
        cpuValue = cpuCard.get_defence();

        std::cout << "You chose the defence statistic, with a value of: " << playerValue << std::endl << std::endl;
    } else {
        playerValue = playerCard.get_agility();
        cpuValue = cpuCard.get_agility();

        std::cout << "You chose the agility statistic, with a value of: " << playerValue << std::endl << std::endl;
    }
    
    std::cout<< "The computer has chosen to play: " << cpuCard.get_name() << std::endl;
    std::cout << "The computer's card has a statistic of: " << cpuValue << std::endl << std::endl;

    if (playerValue > cpuValue) {
        std::cout << "Your card wins! The computer's card has been removed from it's hand" << std::endl;
        cpuHand.erase(cpuHand.begin() + cpuSelection);
    } else if (playerValue < cpuValue) {
        std::cout << "The computer's card wins! Your card has been removed from your hand" << std::endl;
        playerHand.erase(playerHand.begin() + playerSelection);
    } else {
        std::cout << "Both cards have the same statistic, both players keep their cards!" << std::endl;
        
    }


}

void cpuTurn() {
    clear_screen();

    std::cout << "It's the computer's turn now!" << std::endl;

    int cpuSelection = rand() % cpuHand.size();
    Card cpuCard = cpuHand[cpuSelection];

    std::cout << "The computer has chosen to play this card: " << cpuCard.get_name() << std::endl;

    int cpuStat = rand() % 3;
    int cpuValue;

    if (cpuStat == 0) {
        cpuValue = cpuCard.get_attack();

        std::cout << "The computer has chosen the attack statistic, with a value of: " << cpuValue << std::endl;
    } else if (cpuStat == 1) {
        cpuValue = cpuCard.get_defence();

        std::cout << "The computer has chosen the defence statistic, with a value of: " << cpuValue << std::endl;
    } else {
        cpuValue = cpuCard.get_agility();

        std::cout << "The computer has chosen the agility statistic, with a value of: " << cpuValue << std::endl;
    }

    std::cout << "Choose a card to counter the computer's attack!" << std::endl;
    
    for (Card c : playerHand) {
        c.print_card();
    }
    int playerSelection = (user_input(playerHand.size()) - 1);
    Card playerCard = playerHand[playerSelection];

    int playerValue;

    if (cpuStat == 0) {
        playerValue = playerCard.get_attack();
    } else if (cpuStat == 1) {
        playerValue = playerCard.get_defence();
    } else {
        playerValue = playerCard.get_agility();
    }

    std::cout << "Your card has a statistic of: " << playerValue << std::endl;
    
    if (playerValue > cpuValue) {
        std::cout << "Your card wins! The computer's card has been removed from it's hand" << std::endl;
        cpuHand.erase(cpuHand.begin() + cpuSelection);
    } else if (playerValue < cpuValue) {
        std::cout << "The computer's card wins! Your card has been removed from your hand" << std::endl;
        playerHand.erase(playerHand.begin() + playerSelection);
    } else {
        std::cout << "Both cards have the same statistic, both players keep their cards!" << std::endl;
        
    }
}

//Function to handle the dealing of hands
void deal_hands(int handSize) {

    //Loop with length equal to the chosen hand size
    for (int i = 0; i < handSize; i++) {
        //Random int to select random card from deck and assign it to players hand
        int pRnd = rand() % deck.size();
        playerHand.push_back(deck[pRnd]);

        //Random int to select random card from deck and assign it to cpu hand
        int cRnd = rand() % deck.size();
        cpuHand.push_back(deck[cRnd]);
    }
}

//Function to display all cards currently loaded into the deck
void view_deck() {
    clear_screen();

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

void game_loop() {
    while (true) {
        if (playerHand.size() > 0 && cpuHand.size() > 0) {
            playerTurn();
        } else {
            break;
        }

        if (playerHand.size() > 0 && cpuHand.size() > 0) {
            cpuTurn();
        } else {
            break;
        }
    } 
    
    clear_screen();

    if (playerHand.size() == 0) {
        std::cout << "            -Game Over-" << std::endl;
        std::cout << "Your army has been defeated!" << std::endl << std::endl;
    } else {
        std::cout << "            -Victory!-" << std::endl;
        std::cout << "You have defeated the enemy army!" << std::endl << std::endl;
    }

    std::cout << "Enter 1 to return to the main menu" << std::endl;
    int selection = user_input(1);
    switch (selection)
    {
    case 1:
        main_menu();
    
    }
}