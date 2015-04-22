//
// Created by bruno on 21/04/15.
//

#include "timer.h"

void Timer::start() {
    if (t_start != 0) {
        t_start = clock();
    }
}

void Timer::stop() {
    t_diff += (clock() - t_start);
    t_start = 0;
}

void Timer::reset() {
    t_diff = 0;
    t_start = 0;
}

long Timer::getSeconds() {
    return t_diff*1000/CLOCKS_PER_SEC;
}
