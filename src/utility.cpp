#include "utility.h"


double utility::crop(double min, double max, double value) {
    return (value <= min) ? min : ((value >= max) ? max : value);
}

void utility::wheel(float min, float max, float& value) {
    float distance;

    float return_value;

    if (value > max) {
        distance = value - max;
        return_value = min + distance;
    }
    else if (value < min) {
        distance = min - value;
        return_value = max - distance;
    }
    else {
        return_value = value;
    }

    if (return_value < min || return_value > max) {
        utility::wheel(min, max, return_value);
    }

    value = return_value;
}

double utility::absolute(double value) {
    return (value < 0) ? -value : value;
}
