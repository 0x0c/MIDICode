#pragma once

#include <string>
#include <vector>

namespace m2d
{
namespace MIDI
{
	enum Code : int
	{
		C = 0,
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

	class Note
	{
	protected:
		int _code = 0;
		int _octave = 0;

	public:
		Note()
		    : _code(0)
		    , _octave(0)
		{
		}

		Note(int code, int octave)
		    : _code(code)
		    , _octave(octave)
		{
		}

		static int safe_note(int note)
		{
			return std::min(std::max(0, note), 127);
		}

		int code()
		{
			return _code;
		}

		int octave()
		{
			return _octave;
		}

		virtual std::string to_string(bool print_type = false) = 0;
		virtual int rawValue() = 0;
	};

	class InternationalNote : public Note
	{
	public:
		InternationalNote()
		    : Note(0, 0)
		{
		}

		InternationalNote(int code, int octave)
		    : Note(code, octave)
		{
		}

		static int safe_octave(int octave)
		{
			return std::min(std::max(-1, octave), 9);
		}

		std::string to_string(bool print_type)
		{
			static std::vector<std::string> code_string{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
			static std::vector<std::string> octave_string{ "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
			return (print_type == true ? "International " : "") + code_string[_code] + octave_string[_octave];
		}

		int rawValue()
		{
			auto c0 = 12;
			return Note::safe_note(_code + (InternationalNote::safe_octave(_octave) * 12) + c0);
		}
	};

	class YamahaNote : public Note
	{
	public:
		YamahaNote()
		    : Note(0, 0)
		{
		}

		YamahaNote(int code, int octave)
		    : Note(code, octave)
		{
		}

		static int safe_octave(int octave)
		{
			return std::min(std::max(-2, octave), 8);
		}

		std::string to_string(bool print_type)
		{
			static std::vector<std::string> code_string{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
			static std::vector<std::string> octave_string{ "-2", "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8" };
			return (print_type == true ? "Yamaha " : "") + code_string[_code] + octave_string[_octave];
		}

		int rawValue()
		{
			auto c0 = 24;
			return Note::safe_note(_code + (YamahaNote::safe_octave(_octave) * 12) + c0);
		}
	};
};
}