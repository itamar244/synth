#define MAIN                                                                   \
  1, TONE_G4, 7,                                                                     \
  0, 1,                                                                        \
  1, TONE_E4, 7,                                                                     \
  0, 1,                                                                        \
  1, TONE_E4, 16,                                                                    \
  1, TONE_F4, 7,                                                                     \
  0, 1,                                                                        \
  1, TONE_D4, 7,                                                                     \
  0, 1,                                                                        \
  1, TONE_D4, 16,                                                                    \
  1, TONE_C4, 8,

const uint8_t THE_SMALL_JONATHAN[] PROGMEM = {
  MAIN
  1, TONE_D4, 8,
  1, TONE_E4, 8,
  1, TONE_F4, 8,
  1, TONE_G4, 7,
  0, 1,
  1, TONE_G4, 7,
  0, 1,
  1, TONE_G4, 15,
  0, 1,
  MAIN
  1, TONE_E4, 8,
  1, TONE_G4, 7,
  0, 1,
  1, TONE_G4, 7,
  0, 1,
  1, TONE_C4, 16,
};

#undef MAIN
