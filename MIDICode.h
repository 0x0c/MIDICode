#pragma once

#include <string>
#include <vector>

namespace m2d
{
class MIDI
{
private:
	static int _min(int a, int b)
	{
		return a < b ? a : b;
	}

	static int _max(int a, int b)
	{
		return a > b ? a : b;
	}

public:
	enum Note : int
	{
		C = 60,
		CSharp,
		D,
		DSharp,
		E,
		F,
		FSharp,
		G,
		GSharp,
		A,
		ASharp,
		B
	};
	static int safe_note(int note)
	{
		return MIDI::_min(MIDI::_max(0, note), 127);
	}

	static int safe_octave(int octave)
	{
		return MIDI::_min(MIDI::_max(-2, octave), 8);
	}

	static int shift_octave(int note, int octave)
	{
		return MIDI::safe_note(note + (MIDI::safe_octave(octave) * 12));
	}

	static std::string to_string(int note)
	{
		int index = note % 12;
		int octave = (note / 12);
		std::vector<std::string> code { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
		std::vector<std::string> o { "-2", "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8" };
		return code[index] + o[octave];
	}
};
}
