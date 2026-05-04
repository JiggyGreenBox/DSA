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
    static std::unique_ptr<Shape> createShape(const string& type){
        if(type == "circle"){
            return std::make_unique<Circle>();
        }
        else if(type == "square"){
            return std::make_unique<Square>();
        }
        return nullptr;
    }
};

int main() {
    std::unique_ptr<Shape> shape1 = ShapeFactory::createShape("circle");
    std::unique_ptr<Shape> shape2 = ShapeFactory::createShape("square");

    shape1->draw();
    shape2->draw();
    
    return 0;
}