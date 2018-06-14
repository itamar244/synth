#define MAIN_LINE1                                                             \
  1, NOTE(D, 4), Q8,                                                           \
  1, NOTE(E, 4), Q4,                                                           \
  1, NOTE(F, 4), Q4,                                                           \
  1, NOTE(E, 4), Q4 + Q8,                                                      \

#define MAIN_LINE2                                                             \
  1, NOTE(D, 4), Q4,                                                           \
  1, NOTE(E, 4), Q8,                                                           \
  1, NOTE(F, 4), Q4 + Q8,                                                      \
  1, NOTE(E, 4), Q4,                                                           \

#define CHORDS_BEAT_WITHOUT_END                                                \
	3, NOTE(A, 3), NOTE(D, 4), NOTE(F, 4), Q8 + Q16,                             \
	3, NOTE(A, 3), NOTE(D, 4), NOTE(F, 4), Q16,                                  \
	1, NOTE(D, 3), Q4,                                                           \
	3, NOTE(A, 3), NOTE(D, 4), NOTE(F, 4), Q16,                                  \
	3, NOTE(A, 3), NOTE(D, 4), NOTE(F, 4), Q16,                                  \
	0, Q8,                                                                       \
	3, NOTE(A, 3), NOTE(D, 4), NOTE(F, 4), Q16,                                  \
	3, NOTE(A, 3), NOTE(D, 4), NOTE(F, 4), Q16,

#define CHORDS_BEAT                                                            \
	CHORDS_BEAT_WITHOUT_END                                                      \
	0, Q8,

#define CHORDS_BEAT_WITH_A                                                     \
	CHORDS_BEAT_WITHOUT_END                                                      \
	1, NOTE(A, 3), Q8,

MELODY(ANOTHER_BRICK_IN_THE_WALL) = {
  MAIN_LINE1
  MAIN_LINE2
	CHORDS_BEAT
	CHORDS_BEAT
  MAIN_LINE1
  MAIN_LINE2
	CHORDS_BEAT
	CHORDS_BEAT_WITH_A
  MAIN_LINE2
  MAIN_LINE2
};

SECTIONS(ANOTHER_BRICK_IN_THE_WALL) = {
	2, 2, 2, 2, 2
};

#undef MAIN_LINE1
#undef MAIN_LINE2
#undef CHORDS_BEAT_WITHOUT_END
#undef CHORDS_BEAT
#undef CHORDS_BEAT_WITH_A
