//
// Created by jwc on 2/22/19.
//

#include "FpsMonitor.h"

FpsMonitor::FpsMonitor()
{
    head = tail = 0;
    count = 0;
}

void FpsMonitor::mark(double sampleTime)
{
    ween(sampleTime);

    samples[tail] = sampleTime;
    int newTail = (tail + 1) % FpsMonitor_bound;

    if (newTail == head)
    {
        head = (head + 1) % FpsMonitor_bound;
        count--;
    }

    tail = newTail;
    count++;

}

double FpsMonitor::fps()
{
    if (count == 0) return 0;
    return count / (double) (samples[(tail+FpsMonitor_bound-1)%FpsMonitor_bound] - samples[head]);
}

void FpsMonitor::ween(double time) {
    while (head != tail && time-samples[head] >= FpsMonitor_timeWindow)
    {
        head = (head + 1) % FpsMonitor_bound;
        count--;
    }
}