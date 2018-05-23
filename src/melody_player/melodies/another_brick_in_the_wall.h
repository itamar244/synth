#define MAIN_LINE1                                                             \
  1, TONE(D, 4), Q8,                                                           \
  1, TONE(E, 4), Q4,                                                           \
  1, TONE(F, 4), Q4,                                                           \
  1, TONE(E, 4), Q4 + Q8,                                                      \

#define MAIN_LINE2                                                             \
  1, TONE(D, 4), Q4,                                                           \
  1, TONE(E, 4), Q8,                                                           \
  1, TONE(F, 4), Q4 + Q8,                                                      \
  1, TONE(E, 4), Q4,                                                           \

#define BREAK_WITH_A                                                           \
	0, Q1 + Q2 + Q4 + Q8,                                                        \
	1, TONE(A, 3), Q8,

const uint8_t ANOTHER_BRICK_IN_THE_WALL[] PROGMEM = {
  MAIN_LINE1
  MAIN_LINE2
	0, Q2 * 2,
  MAIN_LINE1
  MAIN_LINE2
	BREAK_WITH_A
  MAIN_LINE2
};

const std::vector<uint8_t> ANOTHER_BRICK_IN_THE_WALL_PRACTICE_SECTIONS = {
	4, 2, 2, 2, 4
};

CREATE_CONTAINER(ANOTHER_BRICK_IN_THE_WALL, 0.7);

#undef ENTRY
#undef RIFF
#undef CHORUS
#undef BREAK
