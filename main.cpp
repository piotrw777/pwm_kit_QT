#include <iostream>
#include <array>
#include <algorithm>
#include "wiringPi.h"
#include "softPwm.h"
#include <unistd.h>

#include "element.h"
#include "led.h"
#include "leds_state.h"

using namespace std;

constexpr int operator"" _ms_to_sec ( long double t ) {
    int time = static_cast<int>( t * 1000 );
    return time;
}

//void del_sec(double t) {
//    delay(static_cast<unsigned int>(1000*t));
//}

//funkcja odwzorująca przedział [0,100] -> [0,100]
double scale_0(double k) {
    return k;
}

double scale_1(double k) {
    return k*k/100;
}

void del_sec(double t) {
    delay(1000*t);
}
void blink(int pin, int delayTime = 10, double (*scale_function)(double k) = scale_1) {
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, scale_function(k));
        delay(delayTime);
    }
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, scale_function(100-k));
        delay(delayTime);
    }
}
template <size_t N>
void start_blink(const array<led, N> &leds, leds_state<N> &kit, double (*scale_function)(double k), int delay_time) {
    for(size_t k = 0; k < N; k++) {
        softPwmWrite(leds[k].pin, scale_function( kit.Power(k)));
    }
    kit.next_state();
    delay(delay_time);
}
int main()
{
    const int N = 7;
    const double delay_time = 0.2;
    int pins[N]         = {16,20,21, 23, 24, 25, 15};
    array<led, N> leds  = {16,20,21, 23, 24, 25, 15};
    leds_state<7> kit;

    for(auto &i : leds) {
        i.off();
    }

    for(const auto &i : leds) {
        i.on();
        del_sec(delay_time);
        //delay(1_ms_to_s);
    }
    for(int k = N - 1; k >= 0; k--) {
        leds[k].off();
        del_sec(delay_time);
    }

    //inicjalizacja soft pwm
    for(int k = 0; k < N; k++) {
        leds[k].prepare_soft_pwm();
    }
    for(int k = 0 ; k < 10; k++) {
        blink(16, 5);
    }
    start_blink(leds, kit, scale_1, 10);
}
