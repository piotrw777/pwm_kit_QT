#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

#include "element.h"
#include "led.h"
#include "leds_state.h"
#include "templates.h"

using namespace std;

void del_sec(double t) {
    delay(1000*t);
}

template <size_t N>
void start_blink(const array<led, N> &leds, leds_state<N> &kit, double (*scale_function)(double k), int delay_time) {
    while(true) {
        for(size_t k = 0; k < N; k++) {
            softPwmWrite(leds[k].pin, scale_function( kit.Power(k)));
        }
        kit.next_state();
        delay(delay_time);
    }
}
int main()
{
    const int N = 7;
    const double delay_time = 0.2;

    array<led, N> leds  = {16,20,21, 23, 24, 25, 15};
    leds_state<7> kit;

    for(auto &i : leds) {
        i.off();
    }
    cout << "Test diod\n";
    for(const auto &i : leds) {
        i.on();
        del_sec(delay_time);
    }
    for(int k = N - 1; k >= 0; k--) {
        leds[k].off();
        del_sec(delay_time);
    }

    //inicjalizacja soft pwm
    for(int k = 0; k < N; k++) {
        leds[k].prepare_soft_pwm();
    }
    cout << "Kit effect start\n";
    start_blink(leds, kit);

}
