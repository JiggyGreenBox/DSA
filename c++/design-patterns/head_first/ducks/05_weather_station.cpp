#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class Observer{
public:
    virtual void update(float temperature, float humididty, float pressure) = 0;
    virtual ~Observer() = default;
};

class Subject{
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

class WeatherStation : public Subject {
private:
    vector<Observer*> observers;
    float temperature, humidity, pressure;
public:
    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer) override {
        observers.erase(remove(observers.begin(),observers.end(), observer), observers.end());
    }
    void notifyObservers() override {
        for(Observer* observer : observers){
            observer->update(temperature, humidity, pressure);
        }
    }

    void setMeasurements(float temp, float hum, float pres) {
        temperature = temp;
        humidity = hum;
        pressure = pres;
        notifyObservers(); // new data should be pushed to everyone
    }
};

class Display : public Observer {
public:
    void update(float temperature, float humididty, float pressure) {
        cout << "Display Temperature: " << temperature
             << "C, Humidity: " << humididty
             << "%, pressure: " << pressure << endl;
    }
};

int main() {
    WeatherStation station;
    
    Display display1;
    Display display2;

    station.registerObserver(&display1);
    station.registerObserver(&display2);

    // First update
    station.setMeasurements(25.5, 60.0, 1013.2);

    // Second update
    station.setMeasurements(24.8, 58.0, 1014.5);

    return 0;
}