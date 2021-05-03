//Including required libraries
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
void clear_screen(int amount);
int user_input(int range);
void main_menu();
void game_setup();
void instructions();
void view_deck();
void playerTurn();
void cpuTurn();
void deal_hands(int handSize);
void game_loop();

//Setting the namespace for the JSON library
using json = nlohmann::json;

//Variable declarations
json cards;                             //JSON variable for parsing the Cards.json file


std::vector<Card> deck;                 //Vector of Card objects to store all the cards in the current deck
std::vector<Card> playerHand;           //Vector of Card objects to store the player's hand
std::vector<Card> cpuHand;              //Vector of Card objects to store the CPU's hand

//Main function
int main() {

    //https://rachelnertia.github.io/programming/2016/07/03/json-hpp/
    //Handles "importing" the deck of cards from the JSON file into the cards JSON object
    std::ifstream cardsFile("Cards.json", std::ifstream::binary);
    cards = json::parse(cardsFile);
    cardsFile.close();

    for (int i = 0; i < cards.size(); i++){         //Loop for the number of items in the JSON array of cards

        try {       //Error handling to ensure the card dictionary is read properly
            Card tempCard(cards[i]["Name"].dump(), stoi(cards[i]["Attack"].dump()), stoi(cards[i]["Defence"].dump()), stoi(cards[i]["Agility"].dump()));        //Creates a temporary card object with relevant statistics
            deck.push_back(tempCard);                       //Adds the card to the deck vector
        } catch(...) {      //If the above code fails for any reason prints an error message with information on how to correctly format the Cards.json file
            std::cout << "ERROR READING Cards.json: INCORRECT FORMATTING" << std::endl;
            std::cout << "Ensure Cards.json follows the correct formatting:" << std::endl;
            std::cout << "{" << std::endl;
            std::cout << "  \"Name\":\"card_name\"," << std::endl;
            std::cout << "  \"Attack\":attack_value," << std::endl;
            std::cout << "  \"Defence\":defence_value," << std::endl;
            std::cout << "  \"Agility\":agility_value" << std::endl;
            std::cout << "}," << std::endl << std::endl;
            std::cout << "Exiting game";

            exit(1);                //Exits the game with errors
        }
    }

    main_menu();        // Once the deck array has been populated, calls main_menu()
}

//Function to make it easier to "clear" the screen; cpp has no inbuilt funciton to clear the screen
void clear_screen(int amount){          //Takes in the number of new lines needed

    for (int i = 0; i < amount; i++) {          //For each new line needed, print a new line
        std::cout << std::endl;
    }

}

//Function to handle user input, takes in the range of options allowes
int user_input(int range) {
    std::string input;          //String to contain the user input

    int int_input;              //Int to contain the converted input

    while (1) {                         //While loop to repeat until valid input is given
        std::cout << "USER INPUT:";
        std::cin >> input;              //Gets terminal input

        try {                               //Error handling to see if the input string can be converted to an integer
            int_input = stoi(input);
        } catch (std::invalid_argument) {               //If the above code fails, an error is output and input is requested again
            std::cout << "YOU MUST ENTER AN INTEGER!" << std::endl;
        }

        if (range == -1) {                  //if range == -1, there is no limit on the input, so it just returns the input integer
            if (int_input > 0) {            //the input must still be greater than 0
                return int_input;
            } else {                        //prints warning if input is <= 0
                std::cout << "INPUT MUST BE GREATER THAN 0" << std::endl;
            }
            
        } else {                            // if range != -1, the input must be between 0 and range
            if (int_input <= range && int_input >= 1) {             //checks input is between 0 and range
                return int_input;                                   //returns input
            }
            else {                          //If not, an error is printed
                std::cout << "INPUT IS OUT OF RANGE!" << std::endl;
            }
        }
        
    }  
        
    
}

//Main menu function handles the printing of the main menu, and selection of menu options
void main_menu() {
    clear_screen(100);                  //inserts 100 blank lines to "clear" the screen

    std::cout << "---------> SPACE WARRIOR <---------" << std::endl << std::endl << std::endl << std::endl;         //printing the main menu
    std::cout << "            -Main Menu-            " << std::endl << std::endl;
    std::cout << "         1.  Play Game            " << std::endl;
    std::cout << "        2.  Instructions          " << std::endl;
    std::cout << "         3.  View Deck          " << std::endl;
    std::cout << "         4.  Exit Game            " << std::endl;

    int selection = user_input(4);          //gets input with range = 4 (the number of menu items)

    switch (selection) {                    // selects code block to be executed based on the value of the user input
    case 1:                                 // if 1, sruns game_setup()
        game_setup();
    
    case 2:                                 //if 2, runs instructions()
        instructions();

    case 3:                                 //if 3, runs view_deck()
        view_deck();

    case 4:                                 //if 4, exits game
        std::cout << "Exiting the game!";
        exit(0);                            //exits program with no errors
    }
}

//Function to handle the setup of the game
void game_setup() {

    playerHand.clear();                     //resets player and CPU hands
    cpuHand.clear();

    clear_screen(100);                      //"Clears" screen

    std::cout << "           -Main Game-" << std::endl << std::endl << std::endl;           //printing page header
    std::cout << "Enter the size of deck you wish to play with" << std::endl;
    
    int handSize = user_input(-1);          //Gets input for hand size, range == -1 so there is no limit on the size of hand playable
    deal_hands(handSize);                   //calls deal_hands with the size of hands

    clear_screen(100);                      //Clears screen
    std::cout << "You have been delt the following cards, good luck!"<< std::endl << std::endl;

    for (Card c : playerHand) {                 //For each card in the players hand, prints the card, showing the player their whole hand
        c.print_card();
    }

    std::cout << "Enter 1 to begin game"<< std::endl;           //Gets input to move on to the next stage
    int selection = user_input(1);
    switch (selection)
    {
    case 1:                                                     //if input ==1, calls game_loop()
        game_loop();
    }
    
}


//Function to handle printing of the game instructions
void instructions() {
    clear_screen(100);

    std::cout << "           -Instructions-" << std::endl << std::endl;

    //instructions go here

    std::cout << "Enter 1 to return to the Main Menu" << std::endl;
    int selection = user_input(1);
    switch (selection) {
        case 1:
            main_menu();
    }
}

//Function to handle a player's turn
void playerTurn(){
    clear_screen(20);                       //clears screen

    std::cout << "Your turn!" << std::endl << std::endl;                //printing page header
    std::cout << "Choose a card from your hand:" << std::endl;
    for (Card c : playerHand) {                                         //shows player their hand
        c.print_card();
    }
    int playerSelection = (user_input(playerHand.size()) - 1);          //gets input for the card the player wants to play
    Card playerCard = playerHand[playerSelection];                      //Card object storing the selected card

    int cpuSelection = rand() % cpuHand.size();                         //CPU choses random card to play
    Card cpuCard = cpuHand[cpuSelection];                               //Card object to store the CPU selected card

    clear_screen(20);                                                   //clear screen
    std::cout << "Choose a statistic to play from your chosen card! (1 = Attack, 2 = Defence, 3 = Agility)" << std::endl;       //"Choose stat to play"

    playerCard.print_card();                                            //prints selected card again
    int playerStat = user_input(3);                                     //gets input with option for each stat

    int playerValue;                                                    //integers to store value of chosen statistic for both player and CPU
    int cpuValue;

    if (playerStat == 1) {                                              //If player chose attack stat

        playerValue = playerCard.get_attack();                          //playerValue = attack value of chosen card
        cpuValue = cpuCard.get_attack();                                //cpuValue = attack value of chosen card

        std::cout << "You chose the attack statistic, with a value of: " << playerValue << std::endl << std::endl;      //prints chosen statistic

    } 
    else if (playerStat == 2) {                                         //If player chose defence stat

        playerValue = playerCard.get_defence();                         //playerValue = defence value of chosen card
        cpuValue = cpuCard.get_defence();                               //cpuValue = defence value of chosen card

        std::cout << "You chose the defence statistic, with a value of: " << playerValue << std::endl << std::endl;      //prints chosen statistic

    } 
    else {                                                              //If player chose agility stat

        playerValue = playerCard.get_agility();                         //playerValue = agility value of chosen card
        cpuValue = cpuCard.get_agility();                               //cpuValue = agility value of chosen card

        std::cout << "You chose the agility statistic, with a value of: " << playerValue << std::endl << std::endl;      //prints chosen statistic

    }
    
    std::cout<< "The computer has chosen to play: " << cpuCard.get_name() << std::endl;                     //prints CPU's chosen card
    std::cout << "The computer's card has a statistic of: " << cpuValue << std::endl << std::endl;          //prints CPU's relevant statistic

    if (playerValue > cpuValue) {                                       //If player's statistic is better

        std::cout << "Your card wins! The computer's card has been removed from it's hand" << std::endl;    //Prints winning message
        cpuHand.erase(cpuHand.begin() + cpuSelection);                  //removes the card from the CPU's hand vector

    } else if (playerValue < cpuValue) {                                //If CPU's statistic is better

        std::cout << "The computer's card wins! Your card has been removed from your hand" << std::endl;    //Prints losing message
        playerHand.erase(playerHand.begin() + playerSelection);         //removes the card from the players's hand vector

    } else {                                                            //If it's a drawer

        std::cout << "Both cards have the same statistic, both players keep their cards!" << std::endl;     //prints drawer message
        
    }

    std::cout << "Enter 1 to continue to the next turn" << std::endl;   //Gets user input to continue to the next turn
    int selection = user_input(1);
    switch (selection) {
        case 1:                                                         //If input == 1, breaks out of player_turn() function
            break;
    }
}

//Function handling CPU's turn
void cpuTurn() {
    clear_screen(20);                       //clear screen

    std::cout << "It's the computer's turn now!" << std::endl << std::endl;         //Printing page header

    int cpuSelection = rand() % cpuHand.size();             //CPU selects a random card from their hand
    Card cpuCard = cpuHand[cpuSelection];                   //Card object to store selected card

    std::cout << "The computer has chosen to play this card: " << cpuCard.get_name() << std::endl;          //Prints selected card so player can see the statistics

    int cpuStat = rand() % 3;                               //CPU selects random statistic
    int cpuValue;                                           //Variable to store the value of chosen statistic

    if (cpuStat == 0) {                                     //If CPU chooses the attack statistic

        cpuValue = cpuCard.get_attack();                    //Gets value of attack statistic
        std::cout << "The computer has chosen the attack statistic, with a value of: " << cpuValue << std::endl;            //Prints the value of the attack statistic

    } 
    else if (cpuStat == 1) {                                //If the CPU chooses the defence statistic

        cpuValue = cpuCard.get_defence();                   //Gets value of defence statistic
        std::cout << "The computer has chosen the defence statistic, with a value of: " << cpuValue << std::endl;           //Prints the value of the defence statistic

    } 
    else {                                                  //If the CPU chooses the agility statistic

        cpuValue = cpuCard.get_agility();                   //Gets value of the agility statistic
        std::cout << "The computer has chosen the agility statistic, with a value of: " << cpuValue << std::endl;           //Prints the value of the agility statistic

    }

    std::cout << "Choose a card to counter the computer's attack!" << std::endl;
    
    for (Card c : playerHand) {                             //Prints out players hand
        c.print_card();
    }

    int playerSelection = (user_input(playerHand.size()) - 1);      //Gets user input for card selection, range = length of playerHand vector, -1
    Card playerCard = playerHand[playerSelection];                  //Card object to store selected card

    int playerValue;                                        //Variable to store statistic value

    if (cpuStat == 0) {                                     //If CPU selected attack

        playerValue = playerCard.get_attack();              //Player value = selected card's attack stat

    } else if (cpuStat == 1) {                              //If CPU selected defence

        playerValue = playerCard.get_defence();             //Player value = selected card's defence stat

    } else {                                                //If CPU selected agility

        playerValue = playerCard.get_agility();             //Player value = selected card's agility stat

    }

    std::cout << "Your card has a statistic of: " << playerValue << std::endl;      //prints player's card statistic
    
    if (playerValue > cpuValue) {                           //If player's stat is better

        std::cout << "Your card wins! The computer's card has been removed from it's hand" << std::endl;        //Prints winning message
        cpuHand.erase(cpuHand.begin() + cpuSelection);      //Removes CPU's card

    } else if (playerValue < cpuValue) {                    //If CPU's card is better

        std::cout << "The computer's card wins! Your card has been removed from your hand" << std::endl;        //Prints losing message
        playerHand.erase(playerHand.begin() + playerSelection);     //Removes player's card

    } else {                                                //If its a drawer

        std::cout << "Both cards have the same statistic, both players keep their cards!" << std::endl;         //Prints drawer message
        
    }

    std::cout << "Enter 1 to continue to the next turn" << std::endl;       //Prompts user input to move on to the next turn
    int selection = user_input(1);
    switch (selection) {                                    //If input is 1, breaks out of cpu_turn() funnction;
        case 1:
            break
            ;
    }
}

//Function to handle the dealing of hands
void deal_hands(int handSize) {

    
    for (int i = 0; i < handSize; i++) {                    //Loop with length equal to the chosen hand size
        
        int pRnd = rand() % deck.size();                    //Selects random int between 0 and the size of the deck
        playerHand.push_back(deck[pRnd]);                   //Adds the card at that index in the deck vector to the players hand

        int cRnd = rand() % deck.size();                    //Selects random int between 0 and the size of the deck
        cpuHand.push_back(deck[cRnd]);                      //Adds card at that index in the deck vector to the CPU's hand
    }
}

//Function to display all cards currently loaded into the deck
void view_deck() {
    clear_screen(100);                                                  //Clears screen

    std::cout << "            -Current Deck-" << std::endl << std::endl << std::endl;           //Page header

    for (Card c : deck) {               //For each card in the deck vector  
        c.print_card();                 //Prints that card
    }

    std::cout << "Enter 1 to return to  the Main Menu" << std::endl;                //Prompts user input to return to the menu
    int selection = user_input(1);
    switch (selection) {                                  //If input is 1, calls main_menu()
    case 1:
        main_menu();
    }
}


//Function that handles calling the turn functions and ending the game
void game_loop() {

    while (true) {                              //Infinite loop

        if (playerHand.size() > 0 && cpuHand.size() > 0) {      //If both the player and CPU still have cards

            playerTurn();                       //Calls player_turn()

        } else {                                //If either the player or CPU has no cards    

            break;                              //Exits infinite loop

        }

        if (playerHand.size() > 0 && cpuHand.size() > 0) {      //If both the player and CPU still have cards

            cpuTurn();                          //Calls cpu_turn()

        } else {                                //If either the player or CPU has no cards

            break;                              //Exits infinite loop

        }

    } 
    
    clear_screen(20);                           //clears screen

    if (playerHand.size() == 0) {               //If the player has lost

        std::cout << "            -Game Over-" << std::endl;                        //Prints losing message
        std::cout << "Your army has been defeated!" << std::endl << std::endl;

    } else {                                    //If the player has won

        std::cout << "            -Victory!-" << std::endl;                         //Prints winning message
        std::cout << "You have defeated the enemy army!" << std::endl << std::endl;

    }

    std::cout << "Enter 1 to return to the main menu" << std::endl;                 //Prompts user for input to exit game
    int selection = user_input(1);

    switch (selection)                          //If input is 1, exits to the main menu
    {
    case 1:
        main_menu();
    
    }
}