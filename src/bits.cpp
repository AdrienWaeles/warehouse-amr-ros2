#include "amr_core/bits.hpp"

namespace amr_core {

bool has_flag(std::uint32_t status, std::uint32_t flag) {
  if (flag == 0u) {
    return false;
  }
  return (status & flag) == flag;
}

std::uint32_t set_flag(std::uint32_t status, std::uint32_t flag) { return status | flag; }

std::uint32_t clear_flag(std::uint32_t status, std::uint32_t flag) { return status & ~flag; }

// The subtraction is done in int (promotion), so it can be negative with wrap.
// The cast to uint16_t takes it modulo 65536, and the cast to
// int16_t makes it signed (forward or backward ticks).
std::int16_t encoder_delta(std::uint16_t previous, std::uint16_t current) {
  const std::uint16_t delta = static_cast<std::uint16_t>(current - previous);
  return static_cast<std::int16_t>(delta);
}
}  // namespace amr_core
