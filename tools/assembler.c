#include "bin_header.h"
#include "opcode.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t htnos_custom(uint16_t val) { return (val << 8) | (val >> 8); }
uint16_t make_instruction(Opcode opcode, uint8_t reg_dst,
                          uint8_t reg_imm_or_src, uint8_t imm8) {
  if (opcode == 3 || opcode == 4) {
    return (opcode << 12) | ((reg_dst & 0x03) << 8) |
           ((reg_imm_or_src & 0x03) << 4);
  }
  return (opcode << 12) | ((reg_dst & 0x03) << 8) | (imm8 & 0xFF);
}
int main() {
  FILE *file = fopen("program.bin", "wb");
  if (!file) {
    perror("Error in create the file");
    return 1;
  }
  // section .data
  uint8_t inicial_data[] = {30, 77};

  // section .text
  uint16_t instructions[] = {make_instruction(OP_LOAD_IMM, 0, 0, 10),
                             make_instruction(OP_LOAD_IMM, 1, 0, 5),
                             make_instruction(OP_ADD, 0, 1, 0),
                             make_instruction(OP_STORE, 0, 0, 0x02),
                             make_instruction(OP_FETCH, 2, 0, 0x00),
                             make_instruction(OP_SUB, 0, 0, 0),
                             make_instruction(OP_JMP_IF_ZERO, 0, 0, 0),
                             0x0012,
                             make_instruction(OP_LOAD_IMM, 3, 0, 99),
                             make_instruction(OP_LOAD_IMM, 3, 0, 77),
                             make_instruction(OP_HALT, 0, 0, 0)};
  uint16_t data_size = sizeof(inicial_data);
  uint16_t text_size = sizeof(instructions);
  bin_header header;
  header.magic[0] = 'B';
  header.magic[1] = 'V';
  header.version = 1;
  header.data_size = htnos_custom(data_size);
  header.text_size = htnos_custom(text_size);
  fwrite(&header, sizeof(header), 1, file);
  for (size_t i = 0; i < text_size / 2; i++) {
    uint16_t instructions_be = htnos_custom(instructions[i]);
    fwrite(&instructions_be, sizeof(header), 1, file);
  }
  fwrite(&inicial_data, sizeof(uint8_t), data_size, file);

  printf("Program file is done. ");

  return 0;
}
