#pragma once

#include <cstdlib>
#include <cstdint>
#include <functional>
#include <memory>
#include "base.h"
#include "fs.h"

namespace synth::storage {

template<class T>
class List : public BaseStorage {
public:
	using Parse = std::function<T(char const*)>;

	// -------------------------- start class iterator ---------------------------
	class iterator {
	public:
		iterator(const fs::path path, const Parse& parse, char seperator)
				: file_(fs::ifstream(path))
				, size_(fs::file_size(path))
				, parse_(parse)
				, seperator_(seperator) {}

		inline iterator& operator++() {
			pos_ = GetItemEnd() + 1;
			return *this;
		}

		inline iterator& operator+=(std::size_t to_move) {
			for (std::size_t i = 0; i < to_move && ++(*this); i++);
			return *this;
		}

		// functions to be used by builtin for Range-based for loops
		inline operator bool() const { return pos_ < size_; }
		inline bool operator!=(bool rhs) const { return bool(*this) != rhs; }
		T operator*() {
			std::string value;

			file_.seekg(pos_);
			std::getline(file_, value, seperator_);

			return parse_(value.c_str());
		}

	private:
		fs::ifstream file_;
		const Parse parse_;
		const char seperator_;
		std::size_t pos_ = 0, size_;

		std::size_t GetItemEnd() {
			std::size_t end = pos_;
			while (end < size_ && GetCharFromFStream(file_, end) != seperator_) {
				end++;
			}
			return end;
		}
	};
	// --------------------------- end class iterator ----------------------------

	List(const fs::path& path, Parse parse, char seperator)
		: BaseStorage(path)
		, parse_(parse)
		, seperator_(seperator) {}

	iterator begin() const { return iterator(path_, parse_, seperator_); }
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

		if (end > 0) {
			file.seekg(end);
			file.put(seperator_);
		}
		file << value;

		if (size_ != nullptr) {
			(*size_)++;
		} else {
			size_ = std::make_unique<std::size_t>(1);
		}
	}

protected:
	const Parse parse_;
	const char seperator_;
	std::unique_ptr<std::size_t> size_ = nullptr;
};

} // namespace synth::storage
