#include "store.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace fs = boost::filesystem;

namespace synth {
namespace store {

namespace {

const fs::path kStoreDirectoryName = "./.cache";
const fs::path kStoreFileName = kStoreDirectoryName / "store.txt";

} // namespace

bool __IsInited() {
	return fs::is_regular_file(kStoreFileName);
}

// going through all bytes
// store could be a sparsed array so stopping when reaching an empty address
std::size_t Size() {
	return fs::file_size(kStoreFileName);
}

void Init() {
	fs::create_directory(kStoreDirectoryName);

	fs::fstream file(kStoreFileName,
			fs::fstream::in | fs::fstream::out | fs::fstream::trunc);
	if (!file) {
		file << '\n';
		file.close();
	} else {
		file.clear();
	}
}

wchar_t __GetActual(std::size_t pos) {
	fs::ifstream file(kStoreFileName);
	char ch[1];

	file.seekg(pos);
	file.read(ch, 1);
	std::cout << ch[0] << '\n';
	return wchar_t(ch[0]);
}

void Push(wchar_t value) {
	fs::fstream file(kStoreFileName);
	file.seekg(Size());
	file << uint32_t(value) + 1;
}

} // namespace store
} // namespace synth
