#pragma once

#include <cstdlib>
#include <cstdint>
#include <functional>
#include <memory>
#include "base.h"
#include "fs.h"

namespace synth::storage {

template<class T>
class CommaSeperated : public BaseStorage {
public:
	using Parse = std::function<T(char const*)>;

	// -------------------------- start class iterator ---------------------------
	class iterator {
	public:
		iterator(const fs::path path, const Parse& parse)
				: file_(fs::ifstream(path))
				, size_(fs::file_size(path))
				, parse_(parse) {}


		inline iterator& operator++() {
			start_ = GetItemEnd() + 1;
			return *this;
		}

		inline iterator& operator+=(std::size_t to_move) {
			for (std::size_t i = 0; i < to_move && ++(*this); i++);
			return *this;
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
		: BaseStorage(path)
		, parse_(parse) {}

	iterator begin() const { return iterator(path_, parse_); }
	bool end() const { return false; }

	inline void MaybeInit() {
		if (!IsInited()) Init();
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
		fs::fstream file(path_);
		auto end = fs::file_size(path_);

		file.seekg(end);
		if (end > 0) {
			file.put(',');
		}
		file << value;

		if (size_ != nullptr) {
			(*size_)++;
		} else {
			size_ = std::make_unique<std::size_t>(1);
		}
	}

private:
	const Parse parse_;
	std::unique_ptr<std::size_t> size_ = nullptr;
};

} // namespace synth::storage
