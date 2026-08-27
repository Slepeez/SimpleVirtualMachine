#ifndef VM_H
#define VM_H
#include "bin_header.h"
#include "opcodes.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int registers[4];
  uint16_t pc;
  bool running;
} virtual_machine;

#endif // VM_H
