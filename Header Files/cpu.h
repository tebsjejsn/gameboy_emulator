#pragma once
#include <stdint.h>

class gb_cpu_registers {
    public:
        union {
            struct {
                uint8_t c;
                uint8_t b;
            };
            uint16_t bc;
        };
        union {
            struct {
                uint8_t f;
                uint8_t a;
            };
            uint16_t af;
        };
        union {
            struct {
                uint8_t e;
                uint8_t d;
            };
            uint16_t de;
        };
        union {
            struct {
                uint8_t l;
                uint8_t h;
            };
            uint16_t hl;
        };
        union {
            struct {
                uint8_t p;
                uint8_t s;
            };
            uint16_t sp; // stack pointer
        };
        uint16_t pc; // program counter
};

extern gb_cpu_registers cpu_registers;