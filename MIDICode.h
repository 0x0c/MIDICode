#pragma once

#include <algorithm>
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

	template <class T>
	class Note
	{
		T _note;

	public:
		Note(int code, int octave)
		{
			_note = T(code, octave);
		}

		int code()
		{
			return _note.code();
		}

		int octave()
		{
			return _note.octave();
		}

		int rawValue()
		{
			return _note.rawValue();
		}

		static int safe_octave(int octave)
		{
			return T::safe_octave(octave);
		}
	};

	class NoteImpl
	{
	protected:
		int _code = 0;
		int _octave = 0;

	public:
		NoteImpl()
		    : _code(0)
		    , _octave(0)
		{
		}

		NoteImpl(int code, int octave)
		    : _code(code)
		    , _octave(octave)
		{
		}

		virtual std::string to_string(bool append_style) = 0;

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

		virtual int rawValue() = 0;
	};

	class International : public NoteImpl
	{
	public:
		International()
		    : NoteImpl(0, 0)
		{
		}

		International(int code, int octave)
		    : NoteImpl(code, octave)
		{
		}

		static int safe_octave(int octave)
		{
			return std::min(std::max(-1, octave), 9);
		}

		int shift_octave(int octave)
		{
			return NoteImpl::safe_note(_code + (International::safe_octave(octave) * 12));
		}

		static int note(int base_code, int octave)
		{
			auto c0 = 12;
			return NoteImpl::safe_note(base_code + (International::safe_octave(octave) * 12) + c0);
		}

		std::string to_string(bool append_style)
		{
			static std::vector<std::string> code_string { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
			static std::vector<std::string> octave_string { "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
			return code_string[_code] + octave_string[_octave];
		}

		int rawValue()
		{
			return NoteImpl::safe_note(_code + (International::safe_octave(_octave) * 12));
		}
	};

	class Yamaha : public NoteImpl
	{
	public:
		Yamaha()
		    : NoteImpl(0, 0)
		{
		}

		Yamaha(int code, int octave)
		    : NoteImpl(code, octave)
		{
		}

		static int safe_octave(int octave)
		{
			return std::min(std::max(-2, octave), 8);
		}

		int shift_octave(int octave)
		{
			return NoteImpl::safe_note(_code + (Yamaha::safe_octave(octave) * 12));
		}

		static int note(int base_code, int octave)
		{
			auto c0 = 24;
			return NoteImpl::safe_note(base_code + (Yamaha::safe_octave(octave) * 12) + c0);
		}

		std::string to_string(bool append_style)
		{
			static std::vector<std::string> code_string { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
			static std::vector<std::string> octave_string { "-2", "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8" };
			return code_string[_code] + octave_string[_octave];
		}

		int rawValue()
		{
			return NoteImpl::safe_note(_code + (Yamaha::safe_octave(_octave) * 12));
		}
	};

	using InternationalNote = Note<International>;
	using YamahaNote = Note<Yamaha>;
};
}