#include "audio.h"

PFN_AUDIO_DESTROY_CONTEXT audio_destroy_context = nullptr;
PFN_AUDIO_CREATE_VOICE audio_create_voice = nullptr;
PFN_AUDIO_VOICE_DESTROY audio_voice_destroy = nullptr;
PFN_AUDIO_VOICE_SET_VOLUME audio_voice_set_volume = nullptr;
PFN_AUDIO_VOICE_SET_FREQUENCY audio_voice_set_frequency = nullptr;

PFN_AUDIO_CREATE_FILTER audio_create_filter = nullptr;
PFN_AUDIO_FILTER_UPDATE audio_filter_update = nullptr;
PFN_AUDIO_FILTER_APPLY audio_filter_apply = nullptr;

extern AudioContext *xaudio_create_context();

AudioContext *audio_create_context(AudioEngine p_engine)
{
	switch (p_engine)
	{
		case AudioEngine_XAudio2:
			return xaudio_create_context();
		
		default:
			return nullptr;
	}

}
