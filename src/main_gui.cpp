#include "main_gui.h"
#include "imgui/imgui.h"

#include "audio_player.h"
#include <math.h>

static const int NOTE_MIN = 24;
static const int NOTE_MAX = 96;

float note_to_frequency(int p_note)
{
	return (float)(440.0f * pow(2.0, (p_note - 69.0) / 12.0));
}

int next_window_dims(int y_pos, int height)
{
	ImGui::SetNextWindowPos(ImVec2(0, static_cast<float>(y_pos)));
	ImGui::SetNextWindowSize(ImVec2(550, static_cast<float>(height)));

	return y_pos + height;
}

void main_gui()
{
	bool update_sine = false;
	bool update_square = false;
	bool update_saw = false;

	// gui
	int window_y = next_window_dims(0, 80);
	ImGui::Begin("Sine Wave Generator");
		
		static int sine_note = 60;
		update_sine |= ImGui::SliderInt("Frequency", &sine_note, NOTE_MIN, NOTE_MAX);

		static float sine_volume = 0.0f;
		update_sine |= ImGui::SliderFloat("Volume", &sine_volume, 0.0f, 1.0f);

	ImGui::End();

	window_y = next_window_dims(window_y, 80);
	ImGui::Begin("Square Wave Generator");

		static int square_note = 60;
		update_square |= ImGui::SliderInt("Frequency", &square_note, NOTE_MIN, NOTE_MAX);

		static float square_volume = 0.0f;
		update_square |= ImGui::SliderFloat("Volume", &square_volume, 0.0f, 1.0f);

	ImGui::End();

	window_y = next_window_dims(window_y, 80);
	ImGui::Begin("Saw Tooth Generator");

		static int saw_note = 60;
		update_saw |= ImGui::SliderInt("Frequency", &saw_note, NOTE_MIN, NOTE_MAX);

		static float saw_volume = 0.0f;
		update_saw |= ImGui::SliderFloat("Volume", &saw_volume, 0.0f, 1.0f);

	ImGui::End();

	// audio control
	static AudioPlayer	player;

	if (update_sine)
	{
		player.oscillator_change(AudioPlayer::SineWave, note_to_frequency(sine_note), sine_volume);
	}

	if (update_square)
	{
		player.oscillator_change(AudioPlayer::SquareWave, note_to_frequency(square_note), square_volume);
	}

	if (update_saw)
	{
		player.oscillator_change(AudioPlayer::SawTooth, note_to_frequency(saw_note), saw_volume);
	}
}