#include <string>

class Card {
    public:
        Card(std::string name, int attack, int defence, int agility);
        std::string _name;
        int _attack;
        int _defence;
        int _agility;
};