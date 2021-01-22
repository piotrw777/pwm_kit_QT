#include <iostream>

using namespace std;

class element {
protected:
    int pin;
    static int liczba_elementow;
    element(int pin_): pin(pin_){
        cout << "Dziala konstruktor klasy element\n";
        if(liczba_elementow == 0) {
            if(wiringPiSetupGpio() != 0){
                cout << "Error wiringPiSetupGpio\n";
                exit(1);
            }
            else  {
                cout << "GPIO OK\n";
            }
        }
        liczba_elementow++;
    };
public:
    static int nr_elements()  { return liczba_elementow;}
    virtual void on(int t = 0) {};
    virtual void off() {};
    virtual ~element(){ cout << "Dziala destruktor klasy element\n"; };
};

int element::liczba_elementow = 0;

class led : public element {
public:
    led(int pin_) : element(pin_) {
        cout << "Dziala konstruktor klasy led\n";
        pinMode(pin_, OUTPUT);
    }
    void off() override{
        digitalWrite(pin, 0);
    }
    void on(int t = 0) override{
        digitalWrite(pin, 1);
        if(t == 0) return;
        delay(100*t);
        this->off();
    }

    virtual ~led() {
        cout << "Dziala destruktor klasy led\n";
        digitalWrite(pin, 0);
    }
};