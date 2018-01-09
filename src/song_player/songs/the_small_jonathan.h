#define MAIN                                                                   \
  1, TONE(G, 4), Q4,                                                           \
  1, TONE(E, 4), Q4,                                                           \
  1, TONE(E, 4), Q2,                                                           \
  1, TONE(F, 4), Q4,                                                           \
  1, TONE(D, 4), Q4,                                                           \
  1, TONE(D, 4), Q2,                                                           \
  1, TONE(C, 4), Q4,

const uint8_t THE_SMALL_JONATHAN[] PROGMEM = {
  MAIN
  1, TONE(D, 4), Q4,
  1, TONE(E, 4), Q4,
  1, TONE(F, 4), Q4,
  1, TONE(G, 4), Q4,
  1, TONE(G, 4), Q4,
  1, TONE(G, 4), Q2,
  MAIN
  1, TONE(E, 4), Q4,
  1, TONE(G, 4), Q4,
  1, TONE(G, 4), Q4,
  1, TONE(C, 4), Q2,
};

#undef MAIN
