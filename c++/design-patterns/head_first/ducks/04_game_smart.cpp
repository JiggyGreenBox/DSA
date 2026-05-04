#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


class WeaponBehaviour{ // base
public:
    virtual void useWeapon() = 0;  // all weapons need to implement this
    virtual ~WeaponBehaviour() = default;    
};

class KnifeBehaviour : public WeaponBehaviour{
public:
    void useWeapon(){
        cout << "Knife damage" << endl;
    }
    ~KnifeBehaviour(){
        cout << "KnifeBehaviour destroyed" << endl;
    }
};

class BowAndArrowBehaviour : public WeaponBehaviour{
public:
    void useWeapon(){
        cout << "BowAndArrowBehaviour damage" << endl;
    }
    ~BowAndArrowBehaviour(){
        cout << "BowAndArrowBehaviour destroyed" << endl;
    }
};

class AxeBehaviour : public WeaponBehaviour{
public:
    void useWeapon(){
        cout << "AxeBehaviour damage" << endl;
    }
    ~AxeBehaviour(){
        cout << "AxeBehaviour destroyed" << endl;
    }
};

class SwordBehaviour : public WeaponBehaviour{
public:
    void useWeapon(){
        cout << "SwordBehaviour damage" << endl;
    }
    ~SwordBehaviour(){
        cout << "SwordBehaviour destroyed" << endl;
    }
};



class Character{ // base
public:   
    // WeaponBehaviour* wb;      
    // Character(WeaponBehaviour* wb){
    //     this->wb = wb;
    // }
    // // virtual ~Character() = default;
    // void setWeaponBehaviour(WeaponBehaviour* wb){
    //     this->wb = wb;
    // }
    // void fight(){
    //     this->wb->useWeapon();
    // }

    // virtual ~Character(){
    //     delete wb;
    // }


    unique_ptr<WeaponBehaviour> wb;
    Character(unique_ptr<WeaponBehaviour> new_wb) {
        this->wb = std::move(new_wb);
    }
    virtual ~Character() = default;
    void fight(){
        if(this->wb){
            this->wb->useWeapon();
        }
        else{
            cout << "No weapon found" << endl;
        }        
    }

    void setWeaponBehaviour(unique_ptr<WeaponBehaviour> new_wb) {
        this->wb = std::move(new_wb);
    }
};

class Knight : public Character {
public:
    // Knight() : Character(new SwordBehaviour()){}
    Knight() : Character(make_unique<SwordBehaviour>()){}
};

class King : public Character {
public:
    // King() : Character(new BowAndArrowBehaviour()){}
    King() : Character(make_unique<BowAndArrowBehaviour>()){}
};

class Queen : public Character {
public:    
    // Queen() : Character(new KnifeBehaviour()){}
    Queen() : Character(make_unique<KnifeBehaviour>()){}
};

class Troll : public Character {
public:    
    // Troll() : Character(new AxeBehaviour()){}
    Troll() : Character(make_unique<AxeBehaviour>()){}
};

int main(){

    Knight p1;
    p1.fight();

    Troll p2;
    p2.fight();
    p2.setWeaponBehaviour(make_unique<SwordBehaviour>());
    p2.fight();

    return 0;
}