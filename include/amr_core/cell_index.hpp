#pragma once
#include <ostream>

// A grid cell, or an offset between two cells (x and y can be negative).
// No overflow check to allow better perf: an int overflow is UB.
// Map coordinates are small and the grid checks the bounds.

namespace amr_core {
struct CellIndex {
  int x{};  // column
  int y{};  // row
  constexpr CellIndex& operator+=(const CellIndex& rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  constexpr CellIndex& operator-=(const CellIndex& rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
};

constexpr CellIndex operator+(CellIndex a, const CellIndex& b) noexcept {
  a += b;  // a is already a copy: we modify it
  return a;
}
constexpr CellIndex operator-(CellIndex a, const CellIndex& b) noexcept {
  a -= b;
  return a;
}
constexpr CellIndex operator-(const CellIndex& c) noexcept {  // unary
  return CellIndex{-c.x, -c.y};
}
constexpr bool operator==(const CellIndex& a, const CellIndex& b) noexcept {
  return (a.x == b.x) && (a.y == b.y);
}
constexpr bool operator!=(const CellIndex& a, const CellIndex& b) noexcept { return !(a == b); }

// Order by x, then by y: ordering used by std::set and std::sort.
constexpr bool operator<(const CellIndex& a, const CellIndex& b) noexcept {
  if (a.x == b.x) {
    return a.y < b.y;
  }
  return a.x < b.x;
}
// prints "(x, y)"
inline std::ostream& operator<<(std::ostream& os, const CellIndex& c) {
  return os << "(" << c.x << ", " << c.y << ")";
}

}  // namespace amr_core
