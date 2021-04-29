#include <string>
#include <iostream>

class Card {
    public:
        Card(std::string name, int attack, int defence, int agility);
        
        void set_name(std::string name){
            name_ = name;
        }

        std::string get_name() {
            return name_;
        }

        void set_attack(int attack){
            attack_ = attack;
        }

        int get_attack() {
            return attack_;
        }

        void set_defence(int defence){
            attack_ = defence;
        }

        int get_defence(){
            return defence_;
        }

        void set_agility(int agility){
            agility_ = agility;
        }

        int get_agility(){
            return agility_;
        }   

        void print_card();

    private:
        std::string name_ = "blankCard";
        int attack_ = 0;
        int defence_ = 0;
        int agility_ = 0;
};