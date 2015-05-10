//
// Created by bruno on 21/04/15.
//

#ifndef PRA_T01_TIMER_H
#define PRA_T01_TIMER_H


#include <time.h>

class Timer {
    private:
        clock_t t_start = 0;
        clock_t t_diff = 0;

    public:
        void start();
        void stop();
        void reset();
        long getSeconds();
};

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


#endif //PRA_T01_TIMER_H
