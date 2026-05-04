#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};


class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing a circle" << endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing a square" << endl;
    }
};

class ShapeFactory {
public:
    static Shape* createShape(const string& type){
        if(type == "circle"){
            return new Circle();
        }
        else if(type == "square"){
            return new Square();
        }
        return nullptr;
    }
};

int main() {
    Shape* shape1 = ShapeFactory::createShape("circle");
    Shape* shape2 = ShapeFactory::createShape("square");

    shape1->draw();
    shape2->draw();

    delete shape1;
    delete shape2;

    return 0;
}