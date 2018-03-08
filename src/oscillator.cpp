#include "oscillator.h"

#define _USE_MATH_DEFINES 
#include <math.h>

void oscillator_sine_wave(Oscillator *p_oscillator)
{
	for (int sample = 0; sample < Oscillator::BUFFER_LENGTH; ++sample)
	{
		p_oscillator->buffer[sample] = (float) sin(2 * M_PI * sample / Oscillator::BUFFER_LENGTH);
	}
}

void oscillator_square_wave(Oscillator *p_oscillator)
{
	for (int sample = 0; sample < Oscillator::BUFFER_LENGTH / 2; ++sample)
	{
		p_oscillator->buffer[sample] = 1.0f;
	}

	for (int sample = Oscillator::BUFFER_LENGTH / 2; sample < Oscillator::BUFFER_LENGTH; ++sample)
	{
		p_oscillator->buffer[sample] = -1.0f;
	}
}

void oscillator_saw_tooth(Oscillator *p_oscillator)
{
	for (int sample = 0; sample < Oscillator::BUFFER_LENGTH; ++sample)
	{
		p_oscillator->buffer[sample] = (2.0f * sample / Oscillator::BUFFER_LENGTH) - 1.0f;
	}
}