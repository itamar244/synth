#define MAIN                                                                   \
  1, NOTE(G, 4), Q4,                                                           \
  1, NOTE(E, 4), Q4,                                                           \
  1, NOTE(E, 4), Q2,                                                           \
  1, NOTE(F, 4), Q4,                                                           \
  1, NOTE(D, 4), Q4,                                                           \
  1, NOTE(D, 4), Q2,                                                           \
  1, NOTE(C, 4), Q4,

MELODY(THE_SMALL_JONATHAN) = {
  MAIN
  1, NOTE(D, 4), Q4,
  1, NOTE(E, 4), Q4,
  1, NOTE(F, 4), Q4,
  1, NOTE(G, 4), Q4,
  1, NOTE(G, 4), Q4,
  1, NOTE(G, 4), Q2,

  MAIN
  1, NOTE(E, 4), Q4,
  1, NOTE(G, 4), Q4,
  1, NOTE(G, 4), Q4,
  1, NOTE(C, 4), Q1,

	1, NOTE(D, 4), Q4,
  1, NOTE(D, 4), Q4,
  1, NOTE(D, 4), Q4,
  1, NOTE(D, 4), Q4,

  1, NOTE(D, 4), Q4,
  1, NOTE(E, 4), Q4,
  1, NOTE(F, 4), Q2,

  1, NOTE(E, 4), Q4,
  1, NOTE(E, 4), Q4,
  1, NOTE(E, 4), Q4,
  1, NOTE(E, 4), Q4,

  1, NOTE(E, 4), Q4,
  1, NOTE(F, 4), Q4,
  1, NOTE(G, 4), Q2,

  MAIN
  1, NOTE(E, 4), Q4,
  1, NOTE(G, 4), Q4,
  1, NOTE(G, 4), Q4,
  1, NOTE(C, 4), Q1,
};

SECTIONS(THE_SMALL_JONATHAN) = {
	4, 4, 4, 4
};

#undef MAIN
