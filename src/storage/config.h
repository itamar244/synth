#pragma once

#include <cstdlib>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include "base.h"
#include "fs.h"

namespace synth::storage {

class Config : public BaseStorage {
public:
	using Entry = std::pair<std::string, std::string>;

	Config(const fs::path& path) : BaseStorage(path) {}


	void InitMap() {
		if (map_inited_) return;
		map_inited_ = true;
		fs::ifstream file(path_);
		std::size_t start = 0, size = fs::file_size(path_);

		while (start < size) {
			std::string key, value;
			fs::getline(file, key, '=');
			file.seekg(start_);
			start += key.size();
			fs::getline(file, value, '\n');
			start += value.size();
			file.seekg(start_);

			config_.insert({key, value});
		}
	}

	inline std::string Get(const std::string& key) {
		InitMap();
		auto entry = config_.find(key);
		return entry != config_.end() ? entry->second : "";
	}

	void Set(const std::string& key, const std::string& value) {
		InitMap();
		fs::fstream file(path_);
		auto end = fs::file_size(path_);

		if (end > 0) {
			if (config_.find(key) != config_.end()) {
				file.close();
				fs::remove(path_);
				Init();
				file.open(path_, fs::fstream::out);
				for (const auto& entry : config_) {
					AddEntryToFile(file, entry.first, entry.second);
					file << '\n';
				}
			} else {
				config_[key] = value;
				file.seekg(end);
				file.put('\n');
				AddEntryToFile(file, key, value);
			}
		} else {
			AddEntryToFile(file, key, value);
		}
	}

private:
	std::map<std::string, std::string> config_;
	bool map_inited_ = false;

	inline void AddEntryToFile(
			fs::fstream& file, const std::string& key, const std::string& value) {
		file << key.c_str() << '=' << value.c_str();
	}
};

} // namespace synth::storage
