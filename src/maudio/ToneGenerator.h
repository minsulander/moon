#ifndef MAUDIO_TONEGENERATOR_H
#define MAUDIO_TONEGENERATOR_H

#include "Sample.h"

namespace maudio {
	
	/// \addtogroup audio
	/// @{
	
	enum Waveform {
		SINE,
		SQUARE,
		SAW,
		NOISE,
		IMPULSE,
		SILENCE
	};
	
	/// Waveform generator
	class MAUDIO_EXPORT ToneGenerator {
	public:
		ToneGenerator(const int sampleFrequency = 44100);
		
		/// Generate the specified tone
		void generate(const Waveform waveform = SINE, const float frequency = 1000, const float gain = 1, const float duration = 0, const float start = 0, const float phase = 0, const float prf_freq = 0);
		/// Apply a pulse repetition frequency (PRF), a frequency with which the signal changes between "signal with tone frequency" and no signal
		void prf(const float frequency);
		/// Clear buffer data
		void clear();
		/// Return a reference to the buffer data (\b not OpenAL buffer)
		const SampleBuffer& getBuffer() { return buffer; }
		
	protected:
		int sampleFrequency;
		SampleBuffer buffer;
	};
	
	/// @}
	
}

#endif
