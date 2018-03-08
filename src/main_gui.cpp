#include "main_gui.h"
#include "imgui/imgui.h"

static const int NOTE_MIN = 24;
static const int NOTE_MAX = 96;

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
}