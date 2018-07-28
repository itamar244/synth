#include "audio.h"
#include <cstdint>
#include "utils.h"
#include "sound.h"

namespace synth {

bool Audio::AddNote(Note note) {
  if (current_notes_.size() == kMaxNotes) return false;
  if (!utils::HasItem(current_notes_, note)) {
    current_notes_.push_back(note);
    return true;
  }
  return false;
}

bool Audio::RemoveNote(Note note) {
  auto searched_note = utils::FindItem(current_notes_, note);
  if (searched_note != current_notes_.end()) {
    current_notes_.erase(searched_note);
    return true;
  }
  return false;
}

// wrapper for all note lifecycles. receives a audio class's prefix name
// and a macro method to call on update with the lifecycle type
#define NOTE_LIFECYLCES(CLASS, V)                                              \
	__CREATOR(CLASS, Add, V)                                                     \
	__CREATOR(CLASS, Remove, V)

#define __CREATOR(CLASS, FUNC, V)                                              \
	bool CLASS ## Audio::FUNC ## Note(Note note) {                               \
		bool updated_notes = Audio::FUNC ## Note(note);                            \
		/* V's call is inside a block for potentially a multi line code */         \
		if (updated_notes) { V(FUNC) }                                             \
		return updated_notes;                                                      \
	}

#define V(_) sound::SetPlayedNotes(current_notes_);
	NOTE_LIFECYLCES(Builtin, V)
#undef V

// #define V(FUNC) serial::Send(serial::k ## FUNC ## Note, note);
// 	NOTE_LIFECYLCES(SerialPort, V)
// #undef V

} // namespace synth
