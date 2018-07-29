#pragma once

#include <cstdint>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace synth::storage {

namespace fs = boost::filesystem;

template<class Stream>
inline char GetCharFromFStream(Stream& file, std::size_t pos) {
	char buffer[1];

	file.seekg(pos);
	file.read(buffer, 1);
	return buffer[0];
}

} // namespace synth::storage
