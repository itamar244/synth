#pragma once

#include "storage/fs.h"

namespace synth::storage {

class BaseStorage {
public:
	BaseStorage(const fs::path& path) : path_(path) {}

	inline bool IsInited() {
		return fs::is_regular_file(path_);
	}

	inline void MaybeInit() {
		if (!IsInited()) Init();
	}

	virtual void Init() {
		if (IsInited()) {
			fs::remove(path_);
		} else {
			fs::create_directory(path_.parent_path());
		}

		fs::fstream file(
				path_,
				fs::fstream::in | fs::fstream::out | fs::fstream::trunc);
		file << '\n';
	}

protected:
	const fs::path path_;
};

} // namespace synth::storage
