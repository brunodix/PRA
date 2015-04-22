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


#endif //PRA_T01_TIMER_H
