#ifndef FAUDIOFILTERDEMO_AUDIO_PLAYER_H
#define FAUDIOFILTERDEMO_AUDIO_PLAYER_H

#include "oscillator.h"
#include "audio.h"

class AudioPlayer
{
	public :
		enum OscillatorType {
			SineWave = 0,
			SquareWave,
			SawTooth,
			Oscillator_Count
		};

		AudioPlayer() 
		{
			oscillator_sine_wave(&m_oscillators[SineWave]);
			oscillator_square_wave(&m_oscillators[SquareWave]);
			oscillator_saw_tooth(&m_oscillators[SawTooth]);

			setup(AudioEngine_XAudio2);
		}

		void setup(AudioEngine p_engine) 
		{
			m_context = audio_create_context(p_engine);
			for (int idx = 0; idx < Oscillator_Count; ++idx)
			{
				m_voices[idx] = audio_create_voice(m_context, m_oscillators[idx].buffer, Oscillator::BUFFER_LENGTH, Oscillator::SAMPLE_RATE);
			}
		}

		void shutdown()
		{
			if (m_context == nullptr)
				return;

			for (int idx = 0; idx < Oscillator_Count; ++idx)
			{
				audio_voice_destroy(m_voices[idx]);
				m_voices[idx] = nullptr;
			}

			audio_destroy_context(m_context);
			m_context = nullptr;
		}

		void oscillator_change(OscillatorType p_type, float p_frequency, float p_volume)
		{
			audio_voice_set_frequency(m_voices[p_type], p_frequency / Oscillator::BASE_FREQ);
			audio_voice_set_volume(m_voices[p_type], p_volume);
		}

	private : 
		Oscillator		m_oscillators[Oscillator_Count];
		AudioContext *	m_context;
		AudioVoice *	m_voices[Oscillator_Count];
};

#endif // FAUDIOFILTERDEMO_AUDIO_PLAYER_H