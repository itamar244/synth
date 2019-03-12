// Audio is an abstract class managing the current state of the played notes.
// Each Audio implementation implements specific Audio's lifecycles
// and must implement `virtual Type AudioType` to determine
// the type of handler at runtime.
//
// The following lifecycles are:
//   - `AddNote`. should always call super if inherited
//   - `RemoveNote`. should always call super even inherited
#pragma once

#include <cstdint>
#include <list>
#include <algorithm>
#include "types.h"
#include "sound.h"

namespace synth {

class Audio {
public:
	const static uint8_t kMaxNotes = 4;

	enum AudioType {
		kBuiltin,
		kMessaging,
	};

	using Note = types::Note;
	using NoteList = types::NoteList;

	virtual ~Audio() {}
	virtual AudioType Type() const = 0;

	virtual bool AddNote(Note note);
	virtual bool RemoveNote(Note note);

	inline const NoteList& current_notes() const {
		return current_notes_;
	}

	// `AddNotes` and `RemoveNotes` are wrappers for calling their singular functions
	// with iterable classes
	template<class Iterable>
	inline void AddNotes(const Iterable& notes) {
		for (Note note : notes) AddNote(note);
	}

	template<class Iterable>
	inline void RemoveNotes(const Iterable& notes) {
		for (Note note : notes) RemoveNote(note);
	}

protected:
	NoteList current_notes_;
};

#define AUDIO_INHERIT_FUNCTIONS(NAME)                                          \
		AudioType Type() const override { return k ## NAME; }                      \
		bool AddNote(Note note) override;                                          \
		bool RemoveNote(Note note) override;

class BuiltinAudio : public Audio {
public:
	AUDIO_INHERIT_FUNCTIONS(Builtin)

private:
	SineWavesSynth sine_synth_;
};

class MessagingAudio : public Audio {
public:
	AUDIO_INHERIT_FUNCTIONS(Messaging)
};

} // namespace synth
