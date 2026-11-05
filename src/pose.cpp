#include "amr_core/pose.hpp"

#include <cmath>

#include "amr_core/angle.hpp"

namespace amr_core {

void integrate(Pose2D& pose, double v, double w, double dt) {
  if (!(dt > 0.0)) {  // also catches NaN (NaN > 0.0 is false)
    return;
  }
  pose.x += v * std::cos(pose.theta) * dt;
  pose.y += v * std::sin(pose.theta) * dt;
  pose.theta = normalize_angle(pose.theta + w * dt);
}

Pose2D integrated(const Pose2D& pose, double v, double w, double dt) {
  Pose2D new_pose{pose};
  integrate(new_pose, v, w, dt);
  return new_pose;
}

double distance(const Pose2D& a, const Pose2D& b) { return std::hypot(b.x - a.x, b.y - a.y); }

bool reached(const Pose2D& pose, const Pose2D* goal, double tolerance) {
  if (goal == nullptr || tolerance < 0.0) {
    return false;
  }
  return distance(pose, *goal) <= tolerance;
}

}  // namespace amr_core
