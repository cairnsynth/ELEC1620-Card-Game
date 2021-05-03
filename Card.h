//Card class header file

#include <string>       //including required libraries
#include <iostream>

class Card {

    //Public components
    public:
        Card(std::string name, int attack, int defence, int agility);
        
        void set_name(std::string name){        //Setter for the card name
            name_ = name;
        }

        std::string get_name() {        //Getter for the card name
            return name_;
        }

        void set_attack(int attack){        //Setter for the card Attack
            attack_ = attack;
        }

        int get_attack() {        //Getter for the card Attack
            return attack_;
        }

        void set_defence(int defence){        //Setter for the card Defence
            attack_ = defence;
        }

        int get_defence(){        //Getter for the card Defence
            return defence_;
        }

        void set_agility(int agility){        //Setter for the card Agility
            agility_ = agility;
        }

        int get_agility(){        //Getter for the card Agility
            return agility_;
        }   

        void print_card();          //Prototype for the print_card method

    //Private components
    private:
        std::string name_ = "blankCard";    //Setting default values for each parameter
        int attack_ = 0;
        int defence_ = 0;
        int agility_ = 0;
};