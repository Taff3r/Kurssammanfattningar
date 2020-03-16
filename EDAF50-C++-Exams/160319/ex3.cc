/**
 * Virtuellt arv innebär att klasser som ärver av denna klass med virtuella funktioner har MÖJLIGHETEN att överlagra funktionerna.
 * En funktion vara helt virtuell dvs. endast specificera att det ska finnas en funktion med det signaturen men inte hur den ska bete sig.
 *
 * Med virtuellt arv kan man uppnå polymorfiskt beteende genom att använda nyckelordet virtual
 *
 * Ex.
 */
#include <string>
#include <iostream>
struct PeopleBehaviour {
    virtual void introduce() const = 0;
};


struct Gamer : public PeopleBehaviour {
    std::string name;
    int age; 
    std::string favGame;
    Gamer(std::string name, int age, std::string favGame) : name{name}, age{age}, favGame{favGame} {}
    void introduce() const override {
        std::cout << "My name is "<< name << " and I am "  << age << " years old. My favourite game is " << favGame << std::endl;
    }
};


int main() {
   // PeopleBehaviour* a = new PeopleBehaviour(); // Cant init abstract type

    PeopleBehaviour* b = new Gamer("Simon Tenggren", 22 , "DOOM");
    b->introduce();
}
