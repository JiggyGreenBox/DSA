#include <iostream>
#include "bike.hpp"
#include "car.hpp"
using namespace std;

class VehicleFactory{
    static Vehicle* getVehicle(string type){
        Vehicle* vehicle;
        if(type == "car") {
            vehicle =  new Car();
        }
        else{
            vehicle = new Bike();
        }
        return vehicle;
    }
};