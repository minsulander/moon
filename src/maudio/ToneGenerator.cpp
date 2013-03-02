#include "ToneGenerator.h"
#ifdef __linux__
#include <stdlib.h>
#endif
#include <math.h>
#include <iostream>

namespace maudio {

  ToneGenerator::ToneGenerator(const int newSampleFrequency)
    : sampleFrequency(newSampleFrequency)
  {
  }

  /**
     \param waveform  Waveform shape to be generated
     \param frequency Frequency of the tone
     \param gain      Amplitude of the tone (0..1)
     \param duration  Duration of the tone (seconds)
     \param start     Start time of the tone (seconds)
     \param degphase  Phase of the tone (degrees)
     \param prf_freq  Pulse repetition frequency
     \see prf()
  */
  void ToneGenerator::generate(const Waveform waveform, const float frequency, const float gain, const float duration, const float start, const float degphase, const float prf_freq) 
  {
    static const long prime = 67867967L;
    float lastPhase, phase;
    phase = degphase / 180; // normalized phase

    size_t numSamples, startSample, prfSamples;
    if (duration > 0)
      numSamples = (size_t) floor(duration * sampleFrequency);
    else
      numSamples = buffer.size();
    startSample = (size_t) floor(start * sampleFrequency);
    if (prf_freq > 0)
      prfSamples = (size_t) floor(1.0/prf_freq * sampleFrequency);
    else
      prfSamples = 0;

    if (startSample + numSamples > buffer.size())
      buffer.resize(startSample + numSamples,0);

    lastPhase = phase - frequency / sampleFrequency;
    lastPhase -= floor (lastPhase);
    bool on = true;
    for (size_t i = startSample; i < startSample+numSamples; i++) {
      float p = phase + frequency * (float) i / sampleFrequency;
      float currentPhase = p - floor (p);
      float amplitude;
      switch (waveform) {
      case SINE:
	amplitude = sin(currentPhase * M_PI*2);
	//std::cout << "deg " << (currentPhase * M_PI)*180.0/M_PI << "\n";
	break;
      case SQUARE:
	amplitude = (currentPhase >= 0.5 ? -1 : 1);
	break;
      case SAW:
	amplitude = 2*currentPhase-1;
	break;
      case NOISE:
	amplitude = 2 * (double) (rand() % prime) / prime - 1;
	break;
      case IMPULSE:
	amplitude = (lastPhase > currentPhase) ? 1 : 0;
	break;
      case SILENCE:
	amplitude = 0;
	break;
      default:
	throw SampleException("Unknown waveform");
      }
      if (prfSamples && i > 0 && i % prfSamples == 0)
	on = !on;
      if (on)
	buffer[i] += (short) (gain * amplitude * 32767);
      lastPhase = currentPhase;
    }
  }

  void ToneGenerator::clear()
  {
    buffer.clear();
  }

  void ToneGenerator::prf(const float frequency)
  {
    size_t numSamplesPerBlock = (size_t) floor((float)sampleFrequency / frequency);
    bool on = true;
    for (size_t i = 0; i < buffer.size(); i++) {
      if (i > 0 && i % numSamplesPerBlock == 0)
	on = !on;
      if (!on)
	buffer[i] = 0;
    }
  }

} // namespace

/** \class maudio::ToneGenerator

Tones can be superimposed/mixed or sequenced by calling generate() multiple times.
When mixing tones care must be taken so that the summed gain of the signal does not
exceed 1.

\todo Implement normalization of some kind to prevent clipping when mixing tones.
 */
