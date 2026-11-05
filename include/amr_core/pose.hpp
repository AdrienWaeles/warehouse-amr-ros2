#pragma once

namespace amr_core {

struct Pose2D {
  double x{};
  double y{};
  double theta{};
};

// modifies pose
void integrate(Pose2D& pose, double v, double w, double dt);

// returns a new pose, the given pose is unchanged
[[nodiscard]] Pose2D integrated(const Pose2D& pose, double v, double w, double dt);

[[nodiscard]] double distance(const Pose2D& a, const Pose2D& b);  // Euclidean distance

// goal may be absent
[[nodiscard]] bool reached(const Pose2D& pose, const Pose2D* goal, double tolerance);

}  // namespace amr_core
