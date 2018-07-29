#include "store.h"
#include "storage/comma_seperated.h"


namespace synth::store {

using Database = storage::CommaSeperated<double>;

namespace {

Database database("./.store/store", std::atof);

} // namespace

bool __IsInited() {
	return database.IsInited();
}

// going through all bytes
// store could be a sparsed array so stopping when reaching an empty address
std::size_t Size() {
	return database.Size();
}

void Init() {
	database.Init();
}

void MaybeInit() {
	std::cout << "asdf" << '\n';
	database.MaybeInit();
}

float Get(std::size_t pos) {
	return database.Get(pos);
}

Database::iterator GetIterateor() {
	return database.begin();
}

void Iterate(std::function<void(float)> func) {
	for (float val : database) {
		func(val);
	}
}

void Push(float value) {
	database.Push(value);
}

} // namespace synth::store
