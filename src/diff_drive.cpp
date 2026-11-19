#include "amr_core/diff_drive.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <string_view>

namespace amr_core {

namespace {
// Throw with std::invalid_argument if the value is not finite or not > 0
void require_finite_positive(double value, std::string_view name) {
  if (!std::isfinite(value) || value <= 0) {
    throw std::invalid_argument(std::string(name) + " must be finite and > 0");
  }
}

void require_finite(double value, std::string_view name) {
  if (!std::isfinite(value)) {
    throw std::invalid_argument(std::string(name) + " must be finite");
  }
}
}  // namespace

DiffDrive::DiffDrive(double wheel_radius, double track_width, Limits limits)
    : wheel_radius_{wheel_radius}, track_width_{track_width}, limits_{limits} {
  require_finite_positive(wheel_radius_, "DiffDrive: wheel_radius");
  require_finite_positive(track_width_, "DiffDrive: track_width");
  require_finite_positive(limits_.max_linear, "DiffDrive: limits.max_linear");
  require_finite_positive(limits_.max_angular, "DiffDrive: limits.max_angular");
}

void DiffDrive::command(double v, double w) {
  require_finite(v, "DiffDrive: v");
  require_finite(w, "DiffDrive: w");
  command_.v = std::clamp(v, -limits_.max_linear, limits_.max_linear);
  command_.w = std::clamp(w, -limits_.max_angular, limits_.max_angular);
}

void DiffDrive::stop() noexcept {
  command_.v = 0.0;
  command_.w = 0.0;
}

double DiffDrive::linear() const noexcept { return command_.v; }

double DiffDrive::angular() const noexcept { return command_.w; }

WheelSpeeds DiffDrive::wheel_speeds() const noexcept {
  const double left_speed = (command_.v - (command_.w * track_width_) / 2.0) / wheel_radius_;
  const double right_speed = (command_.v + (command_.w * track_width_) / 2.0) / wheel_radius_;
  return {left_speed, right_speed};
}

Twist DiffDrive::twist_from(const WheelSpeeds& measured) const noexcept {
  const double v = wheel_radius_ * (measured.left + measured.right) / 2.0;
  const double w = wheel_radius_ * (measured.right - measured.left) / track_width_;
  return {v, w};
}

Pose2D DiffDrive::advance(const Pose2D& pose, double dt) const {
  return integrated(pose, command_.v, command_.w, dt);
}
}  // namespace amr_core
