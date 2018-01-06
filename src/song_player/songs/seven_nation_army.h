#define ENTRY                                                                  \
  2, 3, 5, 12,                                                                 \
  0, 4,                                                                        \
  2, 3, 5, 8,                                                                  \
  2, 5, 7, 8,

#define RIFF1                                                                  \
  ENTRY                                                                        \
  1, 3, 8,                                                                     \
  1, 2, 8,                                                                     \
  1, 1, 16,                                                                    \
  1, 7, 16,

#define RIFF2                                                                  \
  1, 3, 12,                                                                    \
  0, 4,                                                                        \
  1, 3, 8,                                                                     \
  1, 5, 8,                                                                     \
  1, 3, 8,                                                                     \
  1, 2, 8,                                                                     \
  1, 1, 8,                                                                     \
  1, 2, 8,                                                                     \
  1, 1, 8,                                                                     \
  1, 7, 8,                                                                     \
  1, 6, 8,

const uint8_t SEVEN_NATION_ARMY[] PROGMEM = {
  RIFF1
  RIFF2
  RIFF1
  RIFF2
  RIFF1
  RIFF2
};

#undef ENTRY
#undef RIFF1
#undef RIFF2
