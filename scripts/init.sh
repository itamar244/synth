# installing boost-filesystem if it doesn't exist
if ! ldconfig -p | grep -c boost_filesystem > /dev/null; then
	sudo apt-get install libboost-filesystem-dev
fi

if [ ! -d "build" ]; then
	mkdir build
fi

cd build
cmake -H. -Bbuild ../
mv compile_commands.json ../compile_commands.json
