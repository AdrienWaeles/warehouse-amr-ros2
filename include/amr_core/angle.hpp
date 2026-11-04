#pragma once

namespace amr_core {

inline constexpr double kPi{3.14159265358979323846};
inline constexpr double kTwoPi{2.0 * kPi};

[[nodiscard]] constexpr double deg2rad(double deg) { return deg * kPi / 180.0; }
[[nodiscard]] constexpr double rad2deg(double rad) { return rad * 180.0 / kPi; }

// Wraps `rad` into [-pi, pi]. NaN and inf give NaN.
[[nodiscard]] double normalize_angle(double rad);

// Shortest rotation from `current` to `target` in [-pi, pi].
[[nodiscard]] double angle_diff(double target, double current);

}  // namespace amr_core
