#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <list>

#define SYNTH_MAX_PLAYED_NOTES 4

namespace synth {

enum class AudioType {
  BUILTIN,
  SERIALPORT,
};

class Audio {
public:
  virtual ~Audio() {};

  virtual AudioType type() const = 0;

  virtual void play() const {};
  
  virtual void add_note(char note) = 0;
  virtual void remove_note(char note) = 0;
};

class BuiltinAudio: public Audio {
private:
  std::list<char> current_notes_;

public:
  AudioType type() const { return AudioType::BUILTIN; }
  void play() const;
  void add_note(char note);
  void remove_note(char note);
};

class SerialPortAudio: public Audio {
public:
  AudioType type() const { return AudioType::SERIALPORT; }
  void add_note(char note);
  void remove_note(char note);
};

} // namespace synth
