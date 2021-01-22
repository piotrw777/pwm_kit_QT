#ifndef LED_H
#define LED_H
#define COMMENTS_LED 0

#include "element.h"

class led : public element {
public:
    led(int pin_) : element(pin_) {
        #if(COMMENTS_LED == 1)
        cout << "Dziala konstruktor klasy led\n";
        #endif
        pinMode(pin_, OUTPUT);
    }
    led(int pin_, bool soft_pwm) {

    }
    void off() override {
        digitalWrite(pin, 0);
    }
    void on(int t = 0) override {
        digitalWrite(pin, 1);
        if (t == 0) return;
        delay(100 * t);
        this->off();
    }

    virtual ~led() {
        #if(COMMENTS_LED == 1)
        cout << "Dziala destruktor klasy led\n";
        #endif
        digitalWrite(pin, 0);
    }
};

#endif // LED.H