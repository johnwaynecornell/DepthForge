//
// Created by jwc on 2/22/19.
//

#ifndef DEPTHFORGE_FPSMONITOR_H
#define DEPTHFORGE_FPSMONITOR_H


const int FpsMonitor_bound = 1024;
const double FpsMonitor_timeWindow = 2.0;

class FpsMonitor {
public:
    double samples[FpsMonitor_bound];

    int head;
    int tail;

    int count;

    FpsMonitor();

    void mark(double sampleTime);
    double fps();

private:
    void ween(double time);
};


#endif //DEPTHFORGE_FPSMONITOR_H
