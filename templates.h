#ifndef TEMPLATES
#define TEMPLATES
#include <iostream>
#include <array>
using namespace std;

class led;

template <size_t K>
class leds_state;

class led;

template <size_t N>
void start_blink(const array<led, N> &led, leds_state<N> &kit, double (*f)(double ), int );

#endif // TEMPLATES
