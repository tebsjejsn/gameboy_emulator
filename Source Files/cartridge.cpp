#include "cartridge.h"

#include <Windows.h>

#include <cstdint>
#include <fstream>
#include <iostream>

char runtime_path_buffer[MAX_PATH];
uint8_t cartridge_data[MAX_CART_SIZE];
bool cartridge_loaded = false;
cart_header_struct* cartridge_header =
    (cart_header_struct*)(cartridge_data + 0x100);

bool cart_open_file() {
  char filename[MAX_PATH] = {0};
  char start_dir[MAX_PATH] = {0};
  GetCurrentDirectoryA(MAX_PATH, start_dir);

  OPENFILENAMEA ofn = {0};
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = nullptr;
  ofn.lpstrFilter = "GB ROM Files\0*.gb\0All Files\0*.*\0";
  ofn.lpstrFile = filename;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrInitialDir = start_dir;
  ofn.lpstrTitle = "Select a ROM file";
  ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

  if (GetOpenFileNameA(&ofn)) {
    return cart_load(filename);
  }
  return false;
}

bool cart_load(const char* filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::binary | std::ios::in | std::ios::ate);

  if (file.is_open()) {
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read((char*)cartridge_data, MAX_CART_SIZE);
    file.close();
    printf("ROM %s loaded, size: %lli bytes\n", filename, std::streamoff(size));
    return true;
  }

  printf("Failed to load file %s\n", filename);
  return false;
}

void cart_print_info() {
  printf("Entry point: %.2X%.2X%.2X%.2X\n", cartridge_header->entry_point[0],
         cartridge_header->entry_point[1], cartridge_header->entry_point[2],
         cartridge_header->entry_point[3]);
  printf("Title: %.16s\n", cartridge_header->title);
  printf("New license code: %.2X, %.2X\n",
         cartridge_header->new_licensee_code[0],
         cartridge_header->new_licensee_code[1]);
  printf("SGB flag: %.2X\n", cartridge_header->sgb_flag);
  printf("Cartridge type: %.2X\n", cartridge_header->cartridge_type);
  printf("ROM Size: %.2X\n", cartridge_header->rom_size);
  printf("RAM Size: %.2X\n", cartridge_header->ram_size);
  printf("Destination code: %.2X\n", cartridge_header->destination_code);
  printf("Old Licensee code: %.2X\n", cartridge_header->old_licensee_code);
  printf("Version: %.2X\n", cartridge_header->mask_rom_version_number);
  printf("Header checksum: %.2X\n", cartridge_header->header_checksum);
  printf("Global checksum: %.2X%.2X\n", cartridge_header->global_checksum[0],
         cartridge_header->global_checksum[1]);
}
