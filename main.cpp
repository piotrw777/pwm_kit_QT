#include <iostream>
#include <array>

using namespace std;

enum direction {left, right};

template <size_t K>
struct leds_state{
    array<int, K> power;
    direction dir;
    int M; //max power
    int peak;
    leds_state() {
        for(size_t i = 0; i < K; i++) {
            power[i] = static_cast<int>(i);
        }
        dir = direction::left;
        M = K-1;
        peak = K-1;
    }
    void print() {
        for (size_t i = 0; i < K; i++) {
            cout << power[i] << " ";
        }
        cout << endl;
    }
    void next_state() {
        for(size_t i = 0; i < K; i++) {
            power[i] = power[i] - (power[i] > 0);
        }
        if(peak == K-1) {
            dir = direction::left;
            power[K-2] = M;
            peak = K-2;
        }
        else if(peak == 0) {
            dir = direction::right;
            power[1] = M;
            peak = 1;
        }
        else if(dir == direction::right) {
            power[static_cast<size_t> (peak+1)] = M;
            peak++;
        }
        else if(dir == direction::left) {
            power[static_cast<size_t> (peak-1)] = M;
            peak--;
        }

    }
};

int main()
{
    const int N = 5; //number of leds
    leds_state<N> kit;
    for(int k = 0; k < 20; k++) {
        kit.print();
        kit.next_state();
    }
}
