#pragma once

#include "amr_core/pose.hpp"

namespace amr_core {

struct Limits {
  double max_linear{};   // m/s
  double max_angular{};  // rad/s
};
struct WheelSpeeds {  // rad/s
  double left{};
  double right{};
};
struct Twist {
  double v{};  // m/s
  double w{};  // rad/s
};

class DiffDrive {
 public:
  // Throws std::invalid_argument if a parameter is not finite and > 0
  DiffDrive(double wheel_radius, double track_width, Limits limits);
  // Throws std::invalid_argument if v or w is not finite, the previous command is then kept
  // Otherwise v and w are clamped to [-max, max]
  void command(double v, double w);  // m/s, rad/s
  // Sets the command to zero
  void stop() noexcept;
  // in m/s
  double linear() const noexcept;
  // in rad/s
  double angular() const noexcept;
  // Wheel speeds in rad/s for the current clamped command.
  [[nodiscard]] WheelSpeeds wheel_speeds() const noexcept;
  // Inverse conversion, from wheel speeds to robot's speed
  [[nodiscard]] Twist twist_from(const WheelSpeeds& measured) const noexcept;
  // Uses integrated() from pose.hpp on current command, the pose remains unchanged if dt invalid
  [[nodiscard]] Pose2D advance(const Pose2D& pose, double dt) const;

 private:
  const double wheel_radius_;
  const double track_width_;
  const Limits limits_;
  Twist command_{};
};

}  // namespace amr_core
