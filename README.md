# MIDICode
A utility library to use MIDI note easily.

## Install

- Put this repo into your Arduino library directory.

## Usage

```
using namespace m2d;

// Refer midi note like this
auto c = MIDICode::Note::C; // Note number = 0, Octave = -2

// Change octave
auto c0 = MIDICode::shift_octave(c, 3); // Note number = 24, Octave = 0

```

## Note

This library is using midi note number from Yamaha style, so the minimum octave is -2.
