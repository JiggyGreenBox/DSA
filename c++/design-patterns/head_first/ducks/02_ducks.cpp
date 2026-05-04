#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// 2 interfaces for our algorithms
class IFlyBehaviour{
public:
    virtual void fly() = 0;    
    virtual ~IFlyBehaviour() = default;
};

class NoFly: public IFlyBehaviour{
public:
    void fly(){
        cout << "I can't fly" << endl;
    }

    ~NoFly(){
        cout << "NoFly destroyed" << endl;
    }
};

class FlyWithWings: public IFlyBehaviour{
public:
    void fly(){
        cout << "I CAN fly" << endl;
    }

    ~FlyWithWings(){
        cout << "FlyWithWings destroyed" << endl;
    }
};

class FlyWithRocker: public IFlyBehaviour{
public:
    void fly(){
        cout << "I CAN fly with ROCKETS" << endl;
    }

    ~FlyWithRocker(){
        cout << "FlyWithRocker destroyed" << endl;
    }
};

class IQuackBehaviour{
public:
    virtual void quack() = 0;    
    virtual ~IQuackBehaviour() = default;
};
class Quack: public IQuackBehaviour{
public:
    void quack(){
        cout << "I CAN quack" << endl;
    }

    ~Quack(){
        cout << "Quack destroyed" << endl;
    }
};
class Sweak: public IQuackBehaviour{
public:
    void quack(){
        cout << "I CAN sweak" << endl;
    }

    ~Sweak(){
        cout << "Sweak destroyed" << endl;
    }
};

class MuteQuack: public IQuackBehaviour{
public:
    void quack(){
        cout << "I am mute" << endl;
    }

    ~MuteQuack(){
        cout << "MuteQuack destroyed" << endl;
    }
};

class Duck{ // base
public:
    string name;
    Duck(string n) :name(n){}    
    // Need a virtual destructor for safe deletion through a base pointer
    virtual ~Duck() = default;
    unique_ptr<IQuackBehaviour> qb;
    // IQuackBehaviour* qb;
    // IFlyBehaviour* fb;
    unique_ptr<IFlyBehaviour> fb;

    // void setQuackBehaviour(IQuackBehaviour* qb){
    void setQuackBehaviour(unique_ptr<IQuackBehaviour> qb){
        // this->qb = qb;
        this->qb = std::move(qb);
    }

    // void setFlyBehaviour(IFlyBehaviour* fb){
    void setFlyBehaviour(unique_ptr<IFlyBehaviour> fb){
        // this->fb = fb;
        this->fb = std::move(fb);
    }

    void performFly(){
        this->fb->fly();
    }

    void performQuack(){
        this->qb->quack();
    }
};


class MallardDuck : public Duck{
public:
    MallardDuck() : Duck("Mallard"){}    

    ~MallardDuck(){
        cout << this->name << " destroyed" << endl;
    }
};





int main(){
    MallardDuck d;
    // d.setFlyBehaviour(new FlyWithWings());
    // d.setQuackBehaviour(new Quack());
    d.setFlyBehaviour(make_unique<FlyWithWings>());
    d.setQuackBehaviour(make_unique<Quack>());
    d.performFly();
    d.performQuack();

    d.setFlyBehaviour(make_unique<NoFly>());
    d.performFly();

    d.setQuackBehaviour(make_unique<MuteQuack>());
    d.performQuack();
    return 0;
}