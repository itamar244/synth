if [ ! -d "build" ]; then
	mkdir build
fi

cd build
cmake -H. -Bbuild ../
mv compile_commands.json ../compile_commands.json
