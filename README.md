# MIDICode
A utility library to use MIDI note easily.

## Install

- Put this repo into your Arduino library directory.

## Usage

```
using namespace m2d;

// Refer midi note like this

auto note = MIDI::YamahaNote(MIDI::Code::C, -2); // Note number = 0, Octave = -2

// Change octave
note.change_octave(0); // Note number = 24, Octave = 0

// Get note number
auto number = note.rawValue();

```

## Note

This library is using midi note number from Yamaha style, so the minimum octave is -2.
