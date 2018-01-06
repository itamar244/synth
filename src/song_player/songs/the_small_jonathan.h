#include <avr/pgmspace.h>

#define MAIN                                                                   \
  1, 5, 7,                                                                     \
  0, 1,                                                                        \
  1, 3, 7,                                                                     \
  0, 1,                                                                        \
  1, 3, 16,                                                                    \
  1, 4, 7,                                                                     \
  0, 1,                                                                        \
  1, 2, 7,                                                                     \
  0, 1,                                                                        \
  1, 2, 16,                                                                    \
  1, 1, 8,

const uint8_t THE_SMALL_JONATHAN[] PROGMEM = {
  MAIN
  1, 2, 8,
  1, 3, 8,
  1, 4, 8,
  1, 5, 7,
  0, 1,
  1, 5, 7,
  0, 1,
  1, 5, 15,
  0, 1,
  MAIN
  1, 3, 8,
  1, 5, 7,
  0, 1,
  1, 5, 7,
  0, 1,
  1, 1, 16,
};

#undef MAIN
