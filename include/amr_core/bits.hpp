#pragma once
#include <cstdint>

namespace amr_core {

// true if all bits of `flag` are 1. flag == 0 returns false
[[nodiscard]] bool has_flag(std::uint32_t status, std::uint32_t flag);

// Turns on the bits of `flag` in `status`. Other bits stay the same.
[[nodiscard]] std::uint32_t set_flag(std::uint32_t status, std::uint32_t flag);

// Turns off the bits of `flag` in `status`. Other bits stay the same.
[[nodiscard]] std::uint32_t clear_flag(std::uint32_t status, std::uint32_t flag);

// ticks moved between two reads: valid only if under 32768 ticks in this interval
[[nodiscard]] std::int16_t encoder_delta(std::uint16_t previous, std::uint16_t current);

}  // namespace amr_core
