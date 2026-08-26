#ifndef BIN_HEADER_H
#define BIN_HEADER_H
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
  char magic[2];
  uint8_t version;
  uint16_t text_size;
  uint16_t data_size;
} bin_header;
#pragma pack(pop)
#endif // BIN_HEADER_H
