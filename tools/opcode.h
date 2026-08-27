#ifndef OPCODE_H
#define OPCODE_H
typedef enum {
  OP_HALT,
  OP_LOAD_IMM,
  OP_ADD,
  OP_SUB,
  OP_STORE,
  OP_FETCH,
  OP_JMP_IF_ZERO
} Opcode;
#endif
