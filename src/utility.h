#pragma once

// int crop(int min, int max, int value) {
//     return (value <= min) ? min : ((value >= max) ? max : value);
// }
//
// long long crop(long long min, long long max, long long value) {
//     return (value <= min) ? min : ((value >= max) ? max : value);
// }

namespace utility {

    double crop(double min, double max, double value);

    double wheel(double min, double max, double value);

    double absolute(double value);

}