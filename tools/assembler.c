#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int htnos_custom(uint16_t val) { return (val << 8) | (val >> 8); }
int main() {}
