FILENAMES=""
for FILENAME in "src/**.cc"; do
	FILENAMES+=$FILENAME
done

clang++-6.0 ${FILENAMES} -o synth -lsfml-graphics -lsfml-window -lsfml-system
