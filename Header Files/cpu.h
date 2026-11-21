#pragma once
#include <stdint.h>

uint8_t cpu_current_opcode = 0;
uint32_t cpu_instruction_counter = 0;
void* cpu_current_instruction_execute = nullptr;

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

        void cpu_fetch();
        void cpu_execute();
        void cpu_reset();
};

class gb_cpu_instructions {
    public:
        const char* disassembly;
        uint8_t operand_len;
        void* execute;
};

typedef void (*cpu_execute_op)();

extern gb_cpu_registers cpu_registers;
extern const gb_cpu_instructions cpu_instructions[256] = {
    // 0x00 - 0x0F
    /* 0x00 */ {"NOP", 0, nullptr},
    /* 0x01 */ {"LD BC,nn", 2, nullptr},
    /* 0x02 */ {"LD (BC),A", 0, nullptr},
    /* 0x03 */ {"INC BC", 0, nullptr},
    /* 0x04 */ {"INC B", 0, nullptr},
    /* 0x05 */ {"DEC B", 0, nullptr},
    /* 0x06 */ {"LD B,n", 1, nullptr},
    /* 0x07 */ {"RLCA", 0, nullptr},
    /* 0x08 */ {"LD (nn),SP", 2, nullptr},
    /* 0x09 */ {"ADD HL,BC", 0, nullptr},
    /* 0x0A */ {"LD A,(BC)", 0, nullptr},
    /* 0x0B */ {"DEC BC", 0, nullptr},
    /* 0x0C */ {"INC C", 0, nullptr},
    /* 0x0D */ {"DEC C", 0, nullptr},
    /* 0x0E */ {"LD C,n", 1, nullptr},
    /* 0x0F */ {"RRCA", 0, nullptr},
    // 0x10 - 0x1F
    /* 0x10 */ {"STOP", 1, nullptr},
    /* 0x11 */ {"LD DE,nn", 2, nullptr},
    /* 0x12 */ {"LD (DE),A", 0, nullptr},
    /* 0x13 */ {"INC DE", 0, nullptr},
    /* 0x14 */ {"INC D", 0, nullptr},
    /* 0x15 */ {"DEC D", 0, nullptr},
    /* 0x16 */ {"LD D,n", 1, nullptr},
    /* 0x17 */ {"RLA", 0, nullptr},
    /* 0x18 */ {"JR e", 1, nullptr},
    /* 0x19 */ {"ADD HL,DE", 0, nullptr},
    /* 0x1A */ {"LD A,(DE)", 0, nullptr},
    /* 0x1B */ {"DEC DE", 0, nullptr},
    /* 0x1C */ {"INC E", 0, nullptr},
    /* 0x1D */ {"DEC E", 0, nullptr},
    /* 0x1E */ {"LD E,n", 1, nullptr},
    /* 0x1F */ {"RRA", 0, nullptr},
    // 0x20 - 0x2F
    /* 0x20 */ {"JR NZ,e", 1, nullptr},
    /* 0x21 */ {"LD HL,nn", 2, nullptr},
    /* 0x22 */ {"LD (HL+),A", 0, nullptr},
    /* 0x23 */ {"INC HL", 0, nullptr},
    /* 0x24 */ {"INC H", 0, nullptr},
    /* 0x25 */ {"DEC H", 0, nullptr},
    /* 0x26 */ {"LD H,n", 1, nullptr},
    /* 0x27 */ {"DAA", 0, nullptr},
    /* 0x28 */ {"JR Z,e", 1, nullptr},
    /* 0x29 */ {"ADD HL,HL", 0, nullptr},
    /* 0x2A */ {"LD A,(HL+)", 0, nullptr},
    /* 0x2B */ {"DEC HL", 0, nullptr},
    /* 0x2C */ {"INC L", 0, nullptr},
    /* 0x2D */ {"DEC L", 0, nullptr},
    /* 0x2E */ {"LD L,n", 1, nullptr},
    /* 0x2F */ {"CPL", 0, nullptr},
    // 0x30 - 0x3F
    /* 0x30 */ {"JR NC,e", 1, nullptr},
    /* 0x31 */ {"LD SP,nn", 2, nullptr},
    /* 0x32 */ {"LD (HL-),A", 0, nullptr},
    /* 0x33 */ {"INC SP", 0, nullptr},
    /* 0x34 */ {"INC (HL)", 0, nullptr},
    /* 0x35 */ {"DEC (HL)", 0, nullptr},
    /* 0x36 */ {"LD (HL),n", 1, nullptr},
    /* 0x37 */ {"SCF", 0, nullptr},
    /* 0x38 */ {"JR C,e", 1, nullptr},
    /* 0x39 */ {"ADD HL,SP", 0, nullptr},
    /* 0x3A */ {"LD A,(HL-)", 0, nullptr},
    /* 0x3B */ {"DEC SP", 0, nullptr},
    /* 0x3C */ {"INC A", 0, nullptr},
    /* 0x3D */ {"DEC A", 0, nullptr},
    /* 0x3E */ {"LD A,n", 1, nullptr},
    /* 0x3F */ {"CCF", 0, nullptr},
    // 0x40 - 0x4F
    /* 0x40 */ {"LD B,B", 0, nullptr},
    /* 0x41 */ {"LD B,C", 0, nullptr},
    /* 0x42 */ {"LD B,D", 0, nullptr},
    /* 0x43 */ {"LD B,E", 0, nullptr},
    /* 0x44 */ {"LD B,H", 0, nullptr},
    /* 0x45 */ {"LD B,L", 0, nullptr},
    /* 0x46 */ {"LD B,(HL)", 0, nullptr},
    /* 0x47 */ {"LD B,A", 0, nullptr},
    /* 0x48 */ {"LD C,B", 0, nullptr},
    /* 0x49 */ {"LD C,C", 0, nullptr},
    /* 0x4A */ {"LD C,D", 0, nullptr},
    /* 0x4B */ {"LD C,E", 0, nullptr},
    /* 0x4C */ {"LD C,H", 0, nullptr},
    /* 0x4D */ {"LD C,L", 0, nullptr},
    /* 0x4E */ {"LD C,(HL)", 0, nullptr},
    /* 0x4F */ {"LD C,A", 0, nullptr},
    // 0x50 - 0x5F
    /* 0x50 */ {"LD D,B", 0, nullptr},
    /* 0x51 */ {"LD D,C", 0, nullptr},
    /* 0x52 */ {"LD D,D", 0, nullptr},
    /* 0x53 */ {"LD D,E", 0, nullptr},
    /* 0x54 */ {"LD D,H", 0, nullptr},
    /* 0x55 */ {"LD D,L", 0, nullptr},
    /* 0x56 */ {"LD D,(HL)", 0, nullptr},
    /* 0x57 */ {"LD D,A", 0, nullptr},
    /* 0x58 */ {"LD E,B", 0, nullptr},
    /* 0x59 */ {"LD E,C", 0, nullptr},
    /* 0x5A */ {"LD E,D", 0, nullptr},
    /* 0x5B */ {"LD E,E", 0, nullptr},
    /* 0x5C */ {"LD E,H", 0, nullptr},
    /* 0x5D */ {"LD E,L", 0, nullptr},
    /* 0x5E */ {"LD E,(HL)", 0, nullptr},
    /* 0x5F */ {"LD E,A", 0, nullptr},
    // 0x60 - 0x6F
    /* 0x60 */ {"LD H,B", 0, nullptr},
    /* 0x61 */ {"LD H,C", 0, nullptr},
    /* 0x62 */ {"LD H,D", 0, nullptr},
    /* 0x63 */ {"LD H,E", 0, nullptr},
    /* 0x64 */ {"LD H,H", 0, nullptr},
    /* 0x65 */ {"LD H,L", 0, nullptr},
    /* 0x66 */ {"LD H,(HL)", 0, nullptr},
    /* 0x67 */ {"LD H,A", 0, nullptr},
    /* 0x68 */ {"LD L,B", 0, nullptr},
    /* 0x69 */ {"LD L,C", 0, nullptr},
    /* 0x6A */ {"LD L,D", 0, nullptr},
    /* 0x6B */ {"LD L,E", 0, nullptr},
    /* 0x6C */ {"LD L,H", 0, nullptr},
    /* 0x6D */ {"LD L,L", 0, nullptr},
    /* 0x6E */ {"LD L,(HL)", 0, nullptr},
    /* 0x6F */ {"LD L,A", 0, nullptr},
    // 0x70 - 0x7F
    /* 0x70 */ {"LD (HL),B", 0, nullptr},
    /* 0x71 */ {"LD (HL),C", 0, nullptr},
    /* 0x72 */ {"LD (HL),D", 0, nullptr},
    /* 0x73 */ {"LD (HL),E", 0, nullptr},
    /* 0x74 */ {"LD (HL),H", 0, nullptr},
    /* 0x75 */ {"LD (HL),L", 0, nullptr},
    /* 0x76 */ {"HALT", 0, nullptr},
    /* 0x77 */ {"LD (HL),A", 0, nullptr},
    /* 0x78 */ {"LD A,B", 0, nullptr},
    /* 0x79 */ {"LD A,C", 0, nullptr},
    /* 0x7A */ {"LD A,D", 0, nullptr},
    /* 0x7B */ {"LD A,E", 0, nullptr},
    /* 0x7C */ {"LD A,H", 0, nullptr},
    /* 0x7D */ {"LD A,L", 0, nullptr},
    /* 0x7E */ {"LD A,(HL)", 0, nullptr},
    /* 0x7F */ {"LD A,A", 0, nullptr},
    // 0x80 - 0x8F
    /* 0x80 */ {"ADD A,B", 0, nullptr},
    /* 0x81 */ {"ADD A,C", 0, nullptr},
    /* 0x82 */ {"ADD A,D", 0, nullptr},
    /* 0x83 */ {"ADD A,E", 0, nullptr},
    /* 0x84 */ {"ADD A,H", 0, nullptr},
    /* 0x85 */ {"ADD A,L", 0, nullptr},
    /* 0x86 */ {"ADD A,(HL)", 0, nullptr},
    /* 0x87 */ {"ADD A,A", 0, nullptr},
    /* 0x88 */ {"ADC A,B", 0, nullptr},
    /* 0x89 */ {"ADC A,C", 0, nullptr},
    /* 0x8A */ {"ADC A,D", 0, nullptr},
    /* 0x8B */ {"ADC A,E", 0, nullptr},
    /* 0x8C */ {"ADC A,H", 0, nullptr},
    /* 0x8D */ {"ADC A,L", 0, nullptr},
    /* 0x8E */ {"ADC A,(HL)", 0, nullptr},
    /* 0x8F */ {"ADC A,A", 0, nullptr},
    // 0x90 - 0x9F
    /* 0x90 */ {"SUB B", 0, nullptr},
    /* 0x91 */ {"SUB C", 0, nullptr},
    /* 0x92 */ {"SUB D", 0, nullptr},
    /* 0x93 */ {"SUB E", 0, nullptr},
    /* 0x94 */ {"SUB H", 0, nullptr},
    /* 0x95 */ {"SUB L", 0, nullptr},
    /* 0x96 */ {"SUB (HL)", 0, nullptr},
    /* 0x97 */ {"SUB A", 0, nullptr},
    /* 0x98 */ {"SBC A,B", 0, nullptr},
    /* 0x99 */ {"SBC A,C", 0, nullptr},
    /* 0x9A */ {"SBC A,D", 0, nullptr},
    /* 0x9B */ {"SBC A,E", 0, nullptr},
    /* 0x9C */ {"SBC A,H", 0, nullptr},
    /* 0x9D */ {"SBC A,L", 0, nullptr},
    /* 0x9E */ {"SBC A,(HL)", 0, nullptr},
    /* 0x9F */ {"SBC A,A", 0, nullptr},
    // 0xA0 - 0xAF
    /* 0xA0 */ {"AND B", 0, nullptr},
    /* 0xA1 */ {"AND C", 0, nullptr},
    /* 0xA2 */ {"AND D", 0, nullptr},
    /* 0xA3 */ {"AND E", 0, nullptr},
    /* 0xA4 */ {"AND H", 0, nullptr},
    /* 0xA5 */ {"AND L", 0, nullptr},
    /* 0xA6 */ {"AND (HL)", 0, nullptr},
    /* 0xA7 */ {"AND A", 0, nullptr},
    /* 0xA8 */ {"XOR B", 0, nullptr},
    /* 0xA9 */ {"XOR C", 0, nullptr},
    /* 0xAA */ {"XOR D", 0, nullptr},
    /* 0xAB */ {"XOR E", 0, nullptr},
    /* 0xAC */ {"XOR H", 0, nullptr},
    /* 0xAD */ {"XOR L", 0, nullptr},
    /* 0xAE */ {"XOR (HL)", 0, nullptr},
    /* 0xAF */ {"XOR A", 0, nullptr},
    // 0xB0 - 0xBF
    /* 0xB0 */ {"OR B", 0, nullptr},
    /* 0xB1 */ {"OR C", 0, nullptr},
    /* 0xB2 */ {"OR D", 0, nullptr},
    /* 0xB3 */ {"OR E", 0, nullptr},
    /* 0xB4 */ {"OR H", 0, nullptr},
    /* 0xB5 */ {"OR L", 0, nullptr},
    /* 0xB6 */ {"OR (HL)", 0, nullptr},
    /* 0xB7 */ {"OR A", 0, nullptr},
    /* 0xB8 */ {"CP B", 0, nullptr},
    /* 0xB9 */ {"CP C", 0, nullptr},
    /* 0xBA */ {"CP D", 0, nullptr},
    /* 0xBB */ {"CP E", 0, nullptr},
    /* 0xBC */ {"CP H", 0, nullptr},
    /* 0xBD */ {"CP L", 0, nullptr},
    /* 0xBE */ {"CP (HL)", 0, nullptr},
    /* 0xBF */ {"CP A", 0, nullptr},
    // 0xC0 - 0xCF
    /* 0xC0 */ {"RET NZ", 0, nullptr},
    /* 0xC1 */ {"POP BC", 0, nullptr},
    /* 0xC2 */ {"JP NZ,nn", 2, nullptr},
    /* 0xC3 */ {"JP nn", 2, nullptr},
    /* 0xC4 */ {"CALL NZ,nn", 2, nullptr},
    /* 0xC5 */ {"PUSH BC", 0, nullptr},
    /* 0xC6 */ {"ADD A,n", 1, nullptr},
    /* 0xC7 */ {"RST 00H", 0, nullptr},
    /* 0xC8 */ {"RET Z", 0, nullptr},
    /* 0xC9 */ {"RET", 0, nullptr},
    /* 0xCA */ {"JP Z,nn", 2, nullptr},
    /* 0xCB */ {"PREFIX CB", 1, nullptr},
    /* 0xCC */ {"CALL Z,nn", 2, nullptr},
    /* 0xCD */ {"CALL nn", 2, nullptr},
    /* 0xCE */ {"ADC A,n", 1, nullptr},
    /* 0xCF */ {"RST 08H", 0, nullptr},
    // 0xD0 - 0xDF
    /* 0xD0 */ {"RET NC", 0, nullptr},
    /* 0xD1 */ {"POP DE", 0, nullptr},
    /* 0xD2 */ {"JP NC,nn", 2, nullptr},
    /* 0xD3 */ {"XX", 0, nullptr},
    /* 0xD4 */ {"CALL NC,nn", 2, nullptr},
    /* 0xD5 */ {"PUSH DE", 0, nullptr},
    /* 0xD6 */ {"SUB n", 1, nullptr},
    /* 0xD7 */ {"RST 10H", 0, nullptr},
    /* 0xD8 */ {"RET C", 0, nullptr},
    /* 0xD9 */ {"RETI", 0, nullptr},
    /* 0xDA */ {"JP C,nn", 2, nullptr},
    /* 0xDB */ {"XX", 0, nullptr},
    /* 0xDC */ {"CALL C,nn", 2, nullptr},
    /* 0xDD */ {"XX", 0, nullptr},
    /* 0xDE */ {"SBC A,n", 1, nullptr},
    /* 0xDF */ {"RST 18H", 0, nullptr},
    // 0xE0 - 0xEF
    /* 0xE0 */ {"LDH (n),A", 1, nullptr},
    /* 0xE1 */ {"POP HL", 0, nullptr},
    /* 0xE2 */ {"LD (C),A", 0, nullptr},
    /* 0xE3 */ {"XX", 0, nullptr},
    /* 0xE4 */ {"XX", 0, nullptr},
    /* 0xE5 */ {"PUSH HL", 0, nullptr},
    /* 0xE6 */ {"AND n", 1, nullptr},
    /* 0xE7 */ {"RST 20H", 0, nullptr},
    /* 0xE8 */ {"ADD SP,e", 1, nullptr},
    /* 0xE9 */ {"JP HL", 0, nullptr},
    /* 0xEA */ {"LD (nn),A", 2, nullptr},
    /* 0xEB */ {"XX", 0, nullptr},
    /* 0xEC */ {"XX", 0, nullptr},
    /* 0xED */ {"XX", 0, nullptr},
    /* 0xEE */ {"XOR n", 1, nullptr},
    /* 0xEF */ {"RST 28H", 0, nullptr},
    // 0xF0 - 0xFF
    /* 0xF0 */ {"LDH A,(n)", 1, nullptr},
    /* 0xF1 */ {"POP AF", 0, nullptr},
    /* 0xF2 */ {"LD A,(C)", 0, nullptr},
    /* 0xF3 */ {"DI", 0, nullptr},
    /* 0xF4 */ {"XX", 0, nullptr},
    /* 0xF5 */ {"PUSH AF", 0, nullptr},
    /* 0xF6 */ {"OR n", 1, nullptr},
    /* 0xF7 */ {"RST 30H", 0, nullptr},
    /* 0xF8 */ {"LD HL,SP+e", 1, nullptr},
    /* 0xF9 */ {"LD SP,HL", 0, nullptr},
    /* 0xFA */ {"LD A,(nn)", 2, nullptr},
    /* 0xFB */ {"EI", 0, nullptr},
    /* 0xFC */ {"XX", 0, nullptr},
    /* 0xFD */ {"XX", 0, nullptr},
    /* 0xFE */ {"CP n", 1, nullptr},
    /* 0xFF */ {"RST 38H", 0, nullptr},
};