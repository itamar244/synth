#define ENTRY                                                                  \
  1, NOTE(E, 4), Q4,                                                           \
  0, Q8,                                                                       \
  1, NOTE(E, 4), Q8,                                                           \
  1, NOTE(G, 4), Q8 + Q16,                                                     \
  1, NOTE(E, 4), Q8 + Q16,                                                     \
  1, NOTE(D, 4), Q8,                                                           \

#define RIFF                                                                   \
  ENTRY                                                                        \
  1, NOTE(C, 4), Q2,                                                           \
  1, NOTE(B, 3), Q2,

#define BREAK                                                                  \
  1, NOTE(G, 4), Q8, 1, NOTE(G, 4), Q8, 1, NOTE(G, 4), Q8, 1, NOTE(G, 4), Q8,  \
  1, NOTE(G, 4), Q8, 1, NOTE(G, 4), Q8, 1, NOTE(G, 4), Q8, 1, NOTE(G, 4), Q8,  \
  1, NOTE(A, 4), Q8, 1, NOTE(A, 4), Q8, 1, NOTE(A, 4), Q8, 1, NOTE(A, 4), Q8,  \
  1, NOTE(A, 4), Q8, 1, NOTE(A, 4), Q8, 1, NOTE(A, 4), Q8, 1, NOTE(A, 4), Q8,

#define CHORUS                                                                 \
  RIFF                                                                         \
  ENTRY                                                                        \
  1, NOTE(C, 4), Q8 + Q16,                                                     \
  1, NOTE(D, 4), Q8 + Q16,                                                     \
  1, NOTE(C, 4), Q8,                                                           \
  1, NOTE(B, 3), Q4,                                                           \
  1, NOTE(A, 3), Q8 + Q16,                                                     \
  0, Q16,

MELODY(SEVEN_NATION_ARMY) = {
  RIFF
  RIFF
  BREAK
  CHORUS
  CHORUS
};

SECTIONS(SEVEN_NATION_ARMY) = {
	4, 2, 2, 2, 4
};

#undef ENTRY
#undef RIFF
#undef CHORUS
#undef BREAK
