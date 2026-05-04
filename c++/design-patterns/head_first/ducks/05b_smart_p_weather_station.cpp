#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class Observer{
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer(){}
};

class Subject{
public:
    virtual void registerObserver(shared_ptr<Observer> Observer) = 0;
    virtual void removeObserver(shared_ptr<Observer> Observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject(){}
};


class WeatherStation: public Subject{
private:
    vector<shared_ptr<Observer>> observers;
    float temperature, humidity, pressure;
public:
    // void registerObserver (shared_ptr<Observer> observer) override {
    //     observers.push_back(observer);
    // }
    // void removeObserver(shared_ptr<Observer> observer) override {
    //     observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    // }

    void registerObserver (const shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer> observer) override {
        // Correct way: Use std::remove_if with a lambda to compare raw pointers
        observers.erase(
            std::remove_if(observers.begin(), observers.end(), 
                        [&observer](const std::shared_ptr<Observer>& p) {
                            // Compares the address of the managed object
                            return p.get() == observer.get();
                        }),
            observers.end()
        );
    }


    void notifyObservers() override {
        for(auto observer : observers){
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

class Display: public Observer{
private:
    float temperature, humidity, pressure;
public:
    void update(float temp, float hum, float pres) override {
        this->temperature = temp;
        this->humidity = hum;
        this->pressure = pres;

        cout << "Display Temperature: " << temperature
             << "C, Humidity: " << humidity
             << "%, pressure: " << pressure << endl;
    }
};

int main(){
    WeatherStation station;
    
    shared_ptr<Display> d1 = make_shared<Display>();
    shared_ptr<Display> d2 = make_shared<Display>();

    station.registerObserver(d1);
    station.registerObserver(d2);

    // First update
    station.setMeasurements(25.5, 60.0, 1013.2);

    station.removeObserver(d1);

    // Second update
    station.setMeasurements(24.8, 58.0, 1014.5);

    return 0;
}