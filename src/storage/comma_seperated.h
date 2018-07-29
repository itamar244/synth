#pragma once

#include <cstdlib>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include "fs.h"

namespace synth::storage {

template<class T>
class CommaSeperated {
public:
	using Parse = std::function<T(char const*)>;

	// -------------------------- start class iterator ---------------------------
	class iterator {
	public:
		iterator(const fs::path path, const Parse& parse)
		: file_(fs::ifstream(path))
		, size_(fs::file_size(path))
		, parse_(parse) {}

		~iterator() {
			file_.close();
		}

		inline bool operator++() {
			start_ = GetItemEnd() + 1;
			return start_ < size_;
		}

		// functions to be used by builtin for Range-based for loops
		inline operator bool() const { return start_ < size_; }
		inline bool operator!=(bool rhs) const { return bool(*this) != rhs; }
		T operator*() {
			std::size_t buffer_size = GetItemEnd() - start_;
			char buffer[buffer_size];
			file_.seekg(start_);
			file_.read(buffer, buffer_size);

			return parse_(buffer);
		}
	private:
		fs::ifstream file_;
		const Parse& parse_;
		std::size_t start_ = 0, size_;

		std::size_t GetItemEnd() {
			std::size_t end = start_;
			while (end < size_ && GetCharFromFStream(file_, end) != ',') {
				end++;
			}
			return end;
		}
	};
	// --------------------------- end class iterator ----------------------------

	CommaSeperated(const fs::path& path, Parse parse)
		: path_(path)
		, parse_(parse) {}

	iterator begin() const { return iterator(path_, parse_); }
	bool end() const { return false; }

	constexpr inline std::size_t MaxSize() {
		return std::numeric_limits<std::size_t>::max();
	}

	inline bool IsInited() {
		return fs::is_regular_file(path_);
	}

	inline void MaybeInit() {
		if (!IsInited()) Init();
	}

	void Init() {
		std::cout << "asdf" << '\n';
		fs::create_directory(path_.parent_path());

		fs::fstream file(path_,
				fs::fstream::in | fs::fstream::out | fs::fstream::trunc);
		if (!file) {
			file << '\n';
		} else {
			file.clear();
		}
		file.close();
	}

	std::size_t Size() {
		if (size_ != nullptr) return *size_;
		auto it = begin();
		std::size_t size = 0;
		for (; ++it; size++);
		return *(size_ = std::make_unique<std::size_t>(size));
	}

	inline T Get(std::size_t pos) {
		auto it = begin();
		for (std::size_t i = 0; i < pos && ++it; i++);
		return *it;
	}

	template<class Value>
	void Push(Value value) {
		fs::wfstream file(path_);
		auto size = fs::file_size(path_);

		file.seekg(fs::file_size(path_));
		if (size > 0) {
			file.put(',');
		}
		file << value;
		file.close();

		if (size_ != nullptr) {
			(*size_)++;
		} else {
			size_ = std::make_unique<std::size_t>(1);
		}
	}

private:
	const Parse parse_;
	const fs::path path_;
	std::unique_ptr<std::size_t> size_ = nullptr;
};

} // namespace synth::storage
