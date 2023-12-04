#ifndef INTERVAL_H
#define INTERVAL_H

#include "math3d.h"
#include "Defs.h"

class Interval {
  public:
    number min, max;

    Interval() : min(+INF), max(-INF) {} // Default interval is empty

    Interval(number _min, number _max) : min(_min), max(_max) {}

    bool contains(number x) const {
        return min <= x && x <= max;
    }

    bool surrounds(number x) const {
        return min < x && x < max;
    }

    static const Interval empty, universe;
};

const static Interval empty   (+INF, -INF);
const static Interval universe(-INF, +INF);

#endif