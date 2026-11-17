#pragma once
#include <cstdint>

struct Twobytes {
    Twobytes() = default;
    Twobytes(uint8_t first, uint8_t second) : first(first), second(second), full((second << 8) | first) {}
    Twobytes(uint16_t full) : first(full & 0xFF), second(full >> 8), full(full) {} // maybe reversed?
    uint8_t first;
    uint8_t second;

    uint16_t full;
};
