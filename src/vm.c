#include "vm.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
static inline uint16_t noths_custom(uint16_t val) {
  return (val << 8) | (val >> 8);
}
bool load_program(virtual_machine *vm, const char *file_path) {
  FILE *file = fopen(file_path, "rb");
  if (!file) {
    perror("Error with open the file.\n");
    return false;
  }
  bin_header header;
  if(fread(&header, sizeof(header), 1, file) != 1){
    fprintf(stderr ,"Error of read header in file.\n");
    fclose(file);
    return false;
  }
  if(header.magic[0] != MAGIC_BYTE_0 && header.magic[1] != MAGIC_BYTE_1){
      fprintf(stderr, "Magic words don't matching.\n");
      fclose(file);
      return false;
  }
  uint16_t text_size =  noths_custom(header.text_size);
  uint16_t data_size = noths_custom(header.data_size);
  fclose(file);
  vm->pc = TEXT_SECTION_START;
  return true;
}
void show_registers(const virtual_machine *vm){
   for(int i = 0; i < 4; i++){
      printf("R: %u (0x%04X)\n", i, vm->registers[i], vm->registers[i]);
   }
  printf("PC: 0x%04X", vm->pc);
}
void run_virtual_machine(virtual_machine *vm){
    vm->running = true;
    while(vm->running){
      if(vm->pc + 1 >= DATA_SECTION_START){
        printf("Error: PC is trying to reading data section.\n");
        break;
      }
      uint8_t byte1 = vm->memory[vm->pc];
      uint8_t byte2 = vm->memory[vm->pc + 1];
      uint16_t current_pc = vm->pc;
      vm->pc += 2;
      uint16_t instruction = (byte1 << 8) | byte2;
      uint8_t opcode =  (instruction >> 12) & 0x0F;
      uint8_t reg_dst = (instruction >> 8 ) & 0x03;
      uint8_t reg_src = (instruction >> 4) & 0x03;
      uint8_t imm8 = instruction & 0xFF;
      switch(opcode){
        case OP_HALT: {
          printf("[0x%04X] HALT \n", current_pc);
          vm->running = false;
          break;
        }
        case OP_ADD: {
          vm->registers[reg_dst] += vm->registers[reg_src];
          printf("[0x%04X] ADD R%d, R%d -> %u\n", current_pc, reg_dst, reg_src, vm->registers[reg_dst]);
          break;
        }
        case OP_SUB: {
          vm->registers[reg_dst] -= vm->registers[reg_src];
          printf("[0x%04X] SUB R%d, R%d -> %u\n", current_pc, reg_dst, reg_src, vm->registers[reg_dst]);
          break;
        }
      }
    }
}
