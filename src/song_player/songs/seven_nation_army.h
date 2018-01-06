#define ENTRY                                                                  \
  2, TONE_E4, TONE_G4, 12,                                                     \
  0, 4,                                                                        \
  2, TONE_E4, TONE_G4, 8,                                                      \
  2, TONE_G4, TONE_B4, 8,

#define RIFF1                                                                  \
  ENTRY                                                                        \
  1, TONE_E4, 8,                                                               \
  1, TONE_D4, 8,                                                               \
  1, TONE_C4, 16,                                                              \
  1, TONE_B3, 16,

#define RIFF2                                                                  \
  1, TONE_E4, 12,                                                              \
  0, 4,                                                                        \
  1, TONE_E4, 8,                                                               \
  1, TONE_G4, 8,                                                               \
  1, TONE_E4, 8,                                                               \
  1, TONE_D4, 8,                                                               \
  1, TONE_C4, 8,                                                               \
  1, TONE_D4, 8,                                                               \
  1, TONE_C4, 8,                                                               \
  1, TONE_B3, 8,                                                               \
  1, TONE_A3, 8,

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
