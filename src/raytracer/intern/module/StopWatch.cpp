#include "module/StopWatch.h"

StopWatch::StopWatch() {
    reset();
}

void StopWatch::reset() {
    started = false;
    stopped = false;
    startTime = 0;
    stopTime = 0;
    duration = 0;
}

void StopWatch::start() {
    reset();
    startTime = time(NULL);
    started = true;
}

void StopWatch::cont() {
    if (started) {
        startTime += difftime(time(NULL), stopTime);
    }
    else {
        start();
    }
}

time_t StopWatch::curr() {
    return difftime(time(NULL), startTime);
}

time_t StopWatch::stop() {
    if (!stopped) {
        stopTime = time(NULL);
        duration = difftime(stopTime, startTime);
        stopped = true;
    }
    return duration;
}
