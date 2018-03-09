#include "audio.h"

#include <FAudio.h>
#include <math.h>

struct AudioContext 
{
	FAudio *faudio;
	FAudioMasteringVoice *mastering_voice;
};

struct AudioVoice
{
	AudioContext *context;
	FAudioSourceVoice *voice;
};

struct AudioFilter
{
	AudioContext *context;
	FAudioFilterParameters params;
};

void faudio_destroy_context(AudioContext *p_context)
{
	FAudioVoice_DestroyVoice(p_context->mastering_voice);
	FAudioDestroy(p_context->faudio);
	delete p_context;
}

AudioVoice *faudio_create_voice(AudioContext *p_context, float *p_buffer, size_t p_buffer_size, int p_sample_rate)
{
	// create a source voice
	FAudioWaveFormatEx waveFormat;
	waveFormat.wFormatTag = 3;
	waveFormat.nChannels = 1;
	waveFormat.nSamplesPerSec = p_sample_rate;
	waveFormat.nAvgBytesPerSec = p_sample_rate * 4;
	waveFormat.nBlockAlign = 4;
	waveFormat.wBitsPerSample = 32;
	waveFormat.cbSize = 0;

	FAudioSourceVoice *voice;
	uint32_t hr = FAudio_CreateSourceVoice(p_context->faudio, &voice, &waveFormat, FAUDIO_VOICE_USEFILTER, FAUDIO_MAX_FREQ_RATIO, NULL, NULL, NULL);

	if (hr != 0) {
		return nullptr;
	}

	FAudioVoice_SetVolume(voice, 0.0f, FAUDIO_COMMIT_NOW);
	
	// submit the array
	FAudioBuffer buffer = { 0 };
	buffer.AudioBytes = 4 * p_buffer_size;
	buffer.pAudioData = (uint8_t *)p_buffer;
	buffer.Flags = FAUDIO_END_OF_STREAM;
	buffer.PlayBegin = 0;
	buffer.PlayLength = p_buffer_size;
	buffer.LoopBegin = 0;
	buffer.LoopLength = p_buffer_size;
	buffer.LoopCount = FAUDIO_LOOP_INFINITE;

	FAudioSourceVoice_SubmitSourceBuffer(voice, &buffer, NULL);

	// start the voice playing
	FAudioSourceVoice_Start(voice, 0, FAUDIO_COMMIT_NOW);

	// return a voice struct
	AudioVoice *result = new AudioVoice();
	result->context = p_context;
	result->voice = voice;
	return result;
}

void faudio_voice_destroy(AudioVoice *p_voice)
{
	FAudioVoice_DestroyVoice(p_voice->voice);
}

void faudio_voice_set_volume(AudioVoice *p_voice, float p_volume)
{
	FAudioVoice_SetVolume(p_voice->voice, p_volume, FAUDIO_COMMIT_NOW);
}

void faudio_voice_set_frequency(AudioVoice *p_voice, float p_frequency)
{
	FAudioSourceVoice_SetFrequencyRatio(p_voice->voice, p_frequency, FAUDIO_COMMIT_NOW);
}

AudioFilter *faudio_create_filter(AudioContext *p_context)
{
	AudioFilter *filter = new AudioFilter();
	filter->context = p_context;
	return filter;
}

void faudio_filter_update(AudioFilter *p_filter, int p_type, float p_cutoff_frequency, float p_q)
{
	if (p_type != -1)
	{
		p_filter->params.Type = FAudioFilterType(p_type);
		p_filter->params.Frequency = (float) (2 * sin(PI * p_cutoff_frequency / 44100));
		p_filter->params.OneOverQ = (float)(1.0 / p_q);
	}
	else 
	{
		// documentation of XAUDIO2_FILTER_PARAMETERS: 
		// Setting XAUDIO2_FILTER_PARAMETERS with the following values is acoustically equivalent to the filter being fully bypassed.
		p_filter->params.Type = LowPassFilter;
		p_filter->params.Frequency = 1.0f;
		p_filter->params.OneOverQ = 1.0f;
	}
}

void faudio_filter_apply(AudioFilter *p_filter, AudioVoice *p_voice)
{
	FAudioVoice_SetFilterParameters(p_voice->voice, &p_filter->params, FAUDIO_COMMIT_NOW);
}

AudioContext *faudio_create_context()
{
	// setup function pointers
	audio_destroy_context = faudio_destroy_context;
	audio_create_voice = faudio_create_voice;
	audio_voice_destroy = faudio_voice_destroy;
	audio_voice_set_volume = faudio_voice_set_volume;
	audio_voice_set_frequency = faudio_voice_set_frequency;
	audio_create_filter = faudio_create_filter;
	audio_filter_update = faudio_filter_update;
	audio_filter_apply = faudio_filter_apply;

	// create Faudio object
	FAudio *faudio;

	uint32_t hr = FAudioCreate(&faudio, 0, FAUDIO_DEFAULT_PROCESSOR);
	if (hr != 0)
		return nullptr;

	// create a mastering voice
	FAudioMasteringVoice *mastering_voice;

	hr = FAudio_CreateMasteringVoice(faudio, &mastering_voice, FAUDIO_DEFAULT_CHANNELS, FAUDIO_DEFAULT_SAMPLERATE, 0, NULL, NULL);
	if (hr != 0)
		return nullptr;

	// return a context object
	AudioContext *context = new AudioContext();
	context->faudio = faudio;
	context->mastering_voice = mastering_voice;

	return context;
}
