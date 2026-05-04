#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Duck{ // base
public:
    string name;
    Duck(string n) :name(n){}
    virtual bool canFly() {return false;}
    virtual bool canQuack() {return false;}
    virtual bool canSwim() {return false;}
    // Need a virtual destructor for safe deletion through a base pointer
    virtual ~Duck() = default;
};

class IFlyable{ // this duck flies
public:
    virtual void fly() = 0;    
    virtual ~IFlyable() = default;
};

class IQuackable{ // this duck flies
public:
    virtual void quack() = 0;
    virtual ~IQuackable() = default;
};

class ISwimmable{ // this duck flies
public:
    virtual void swim() = 0;
    virtual ~ISwimmable() = default;
};

class MallardDuck : public Duck, public IFlyable, public IQuackable, public ISwimmable{
public:
    MallardDuck() : Duck("Mallard"){}
    void fly(){
        cout << this->name << " can fly" << endl;
    }
    void quack(){
        cout << this->name << " can quack" << endl;
    }
    void swim(){
        cout << this->name << " can swim" << endl;
    }

    bool canFly(){return true;}
    bool canSwim(){return true;}
    bool canQuack(){return true;}

    ~MallardDuck(){
        cout << this->name << " destroyed" << endl;
    }
};

class WoodenDuck : public Duck{
public:
    WoodenDuck(): Duck("wooden duck"){}
    ~WoodenDuck(){
        cout << this->name << " destroyed" << endl;
    }
};

int main(){
    // vector<Duck*> ducks = {new MallardDuck(), new WoodenDuck()};
    vector<unique_ptr<Duck>> ducks;
    ducks.push_back(make_unique<MallardDuck>());
    ducks.push_back(make_unique<WoodenDuck>());

    for(const auto &duck : ducks){
        // IFlyable* flyableDuck = dynamic_cast<IFlyable*>(duck);
        IFlyable* flyableDuck = dynamic_cast<IFlyable*>(duck.get()); // dynamic cast returns a safe pointer
        if(flyableDuck){
            flyableDuck->fly();
        }
    }    
    return 0;
}