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

constexpr int operator"" _ms_to_sec ( double t ) {
    int time = static_cast<int>( t * 1000 );
    return time;
}

//void del_sec(double t) {
//    delay(static_cast<unsigned int>(1000*t));
//}

//funkcja odwzorująca przedział [0,100] -> [0,100]
double scale_1(int k) {
    return k*k/100;
}

void blink(int pin, int delayTime = 10, double (*scale_function)(int k) = scale_1) {
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, scale_function(k));
        delay(delayTime);
    }
    for (int k = 0; k < 100; k++) {
        softPwmWrite(pin, scale_function(100-k));
        delay(delayTime);
    }
}

int main()
{
    const int N = 7;
    const double delay_time = 0.2;
    int pins[N]         = {16,20,21, 23, 24, 25, 15};
    array<led, N> leds  = {16,20,21, 23, 24, 25, 15};
    for(auto &i : leds) {
        i.off();
    }

    for(const auto &i : leds) {
        i.on();
        //del_sec(delay_time);
        delay(1_ms_to_s);
    }
    for(int k = N - 1; k >= 0; k--) {
        leds[k].off();
        //del_sec(delay_time);
    }

    //inicjalizacja soft pwm
    for(int k = 0; k < N; k++) {
        leds[k].prepare_soft_pwm();
    }
    for(int k = 0 ; k < 10; k++) {
        blink(16, 5);
    }
}
