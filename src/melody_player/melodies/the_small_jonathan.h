#define MAIN                                                                   \
  1, TONE(G, 4), Q4,                                                           \
  1, TONE(E, 4), Q4,                                                           \
  1, TONE(E, 4), Q2,                                                           \
  1, TONE(F, 4), Q4,                                                           \
  1, TONE(D, 4), Q4,                                                           \
  1, TONE(D, 4), Q2,                                                           \
  1, TONE(C, 4), Q4,

MELODY(THE_SMALL_JONATHAN) = {
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
  1, TONE(C, 4), Q1,

	1, TONE(D, 4), Q4,
  1, TONE(D, 4), Q4,
  1, TONE(D, 4), Q4,
  1, TONE(D, 4), Q4,

  1, TONE(D, 4), Q4,
  1, TONE(E, 4), Q4,
  1, TONE(F, 4), Q2,

  1, TONE(E, 4), Q4,
  1, TONE(E, 4), Q4,
  1, TONE(E, 4), Q4,
  1, TONE(E, 4), Q4,

  1, TONE(E, 4), Q4,
  1, TONE(F, 4), Q4,
  1, TONE(G, 4), Q2,

  MAIN
  1, TONE(E, 4), Q4,
  1, TONE(G, 4), Q4,
  1, TONE(G, 4), Q4,
  1, TONE(C, 4), Q1,
};

SECTIONS(THE_SMALL_JONATHAN) = {
	4, 4, 4, 4
};

CONTAINER(THE_SMALL_JONATHAN, 1);

#undef MAIN
