#ifndef VM_H
#define VM_H
#include "bin_header.h"
#include "opcodes.h"
#include <stdbool.h>
#define TEXT_SECTION_START 0x0000
#define DATA_SECTION_STATR 0x8000
#define MEMORY_SIZE (1 << 16)
#define MAGIC_BYTE_0 'B'
#define MAGIC_BYTE_1 'V'
#define CURRENT_VERSION 1
typedef struct {
  int registers[4];
  uint16_t pc;
  bool running;
} virtual_machine;
static inline uint16_t noths_custom(uint16_t val);
bool load_program(virtual_machine *vm, const char *file_path);
void run_virtual_machine(virtual_machine *vm);
void show_registers(const virtual_machine *vm);
#endif // VM_H
