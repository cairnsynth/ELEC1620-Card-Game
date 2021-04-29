#include <string>
#include <iostream>

class Card {
    public:
        Card(std::string name, int attack, int defence, int agility);
        
        std::string get_name() {
            return name_;
        }

        int get_attack() {
            return attack_;
        }

        int get_defence(){
            return defence_;
        }

        int get_agility(){
            return agility_;
        }   

    private:
        std::string name_;
        int attack_;
        int defence_;
        int agility_;
};