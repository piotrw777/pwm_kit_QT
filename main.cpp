#include <iostream>
#include <array>
#include <algorithm>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>
#include "element.h"
#include "led.h"
#include "leds_state.h"
using namespace std;


void del_sec(double t) {
    delay(static_cast<int>(1000*t));
}
void prepare_soft_pwm(int pin) {
    static const int PWM_Range = 100;
    int soft_pwm;
    soft_pwm = softPwmCreate(pin, 0, PWM_Range);
    if (soft_pwm != 0) {
        cout << "Soft PWM Error";
        exit(1);
    }
}
void blink(int pin) {
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, k);
        delay(10);
    }
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, 100-k);
        delay(10);
    }
}
int main()
{
    const int N = 7;
    const double delay_time = 0.5;
    int pins[N]         = {16,20,21, 23, 24, 25, 15};
    array<led, N> leds  = {16,20,21, 23, 24, 25, 15};
    for(auto &i : leds) {
        i.off();
    }
    

    for(auto &i : leds) {
        i.on();
        del_sec(delay_time);
    }
    for(int k = N - 1; k >= 0; k--) {
        leds[k].off();
        del_sec(delay_time);
    }
    //inicjalizacja soft pwm
    for(int k = 0; k < N; k++) {
        prepare_soft_pwm(pins[k]);
    }
    for(int k = 0; k < 100; k++) {
        softPwmWrite(pins[0], k % 100);
        softPwmWrite(pins[1], (k+20) % 100);
        softPwmWrite(pins[2], (k+40) % 100);
        delay(10);

    }
 
}
