shopt -s globstar

FILENAMES=""
for FILENAME in "src/**/*.cc"; do
	FILENAMES+=$FILENAME
done

clang++-6.0                                                                    \
	-std=c++17 -pthread ${FILENAMES}                                             \
	-o synth -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio            \
	-lboost_system -lboost_filesystem
