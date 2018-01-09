#define ENTRY                                                                  \
  1, TONE(E, 4), Q4,                                                           \
  0, Q8,                                                                       \
  1, TONE(E, 4), Q8,                                                           \
  1, TONE(G, 4), Q8 + Q16,                                                     \
  1, TONE(E, 4), Q8 + Q16,                                                     \
  1, TONE(D, 4), Q8,                                                           \

#define RIFF                                                                   \
  ENTRY                                                                        \
  1, TONE(C, 4), Q2,                                                           \
  1, TONE(B, 3), Q2,

#define BREAK                                                                  \
  1, TONE(G, 4), Q8, 1, TONE(G, 4), Q8, 1, TONE(G, 4), Q8, 1, TONE(G, 4), Q8,  \
  1, TONE(G, 4), Q8, 1, TONE(G, 4), Q8, 1, TONE(G, 4), Q8, 1, TONE(G, 4), Q8,  \
  1, TONE(A, 4), Q8, 1, TONE(A, 4), Q8, 1, TONE(A, 4), Q8, 1, TONE(A, 4), Q8,  \
  1, TONE(A, 4), Q8, 1, TONE(A, 4), Q8, 1, TONE(A, 4), Q8, 1, TONE(A, 4), Q8,

#define CHORUS                                                                 \
  RIFF                                                                         \
  ENTRY                                                                        \
  1, TONE(C, 4), Q8 + Q16,                                                     \
  1, TONE(D, 4), Q8 + Q16,                                                     \
  1, TONE(C, 4), Q8,                                                           \
  1, TONE(B, 3), Q4,                                                           \
  1, TONE(A, 3), Q8 + Q16,                                                     \
  0, Q16,

const uint8_t SEVEN_NATION_ARMY[] PROGMEM = {
  RIFF
  RIFF
  BREAK
  CHORUS
  CHORUS
};

#undef ENTRY
#undef RIFF
#undef CHORUS
#undef BREAK
