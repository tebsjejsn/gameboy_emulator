#include "cartridge.h"
#include <cstdint>
#include <fstream>
#include <iostream>

uint8_t cartridge_data[MAX_CART_SIZE];
bool cartridge_loaded = false;
cart_header_struct* cartridge_header;

void cart_print_info() {

}

bool cart_load(const char* filename) {

}

bool cart_open_file() {
    
}