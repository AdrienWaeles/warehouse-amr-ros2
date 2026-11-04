#include "amr_core/angle.hpp"

#include <cmath>

namespace amr_core {

double normalize_angle(double rad) { return std::remainder(rad, kTwoPi); }

double angle_diff(double target, double current) { return normalize_angle(target - current); }

}  // namespace amr_core
