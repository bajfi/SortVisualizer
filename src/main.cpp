// Copyright (c) 2026 JackLee
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "msf_gif.h"
#include "raylib.h"
#include "sort.h"
#include "utils.h"

#include <unordered_set>

int main()
{
		constexpr int GIF_RECORD_FRAMERATE = 5;
		constexpr int ScreenWidth = 1'080;
		constexpr int ScreenHeight = 720;
		constexpr size_t NumRectangles = 30;

		// generate random rectangles here
		auto rectangles = utils::generate01RandomNumber<float>(NumRectangles);

		// Test for sorted state
		std::sort(std::begin(rectangles), std::end(rectangles));
		// Swap two elements to test the visualization of the sorting process
		std::swap(rectangles[0], rectangles[NumRectangles - 1]);

		// State variables to track the sorting process and the rectangles being compared or swapped
		bool sorted{false};
		std::unordered_set<size_t> trackers{};

		// Setup GIF recording
		const char* gifFileName = "recording.gif";
		size_t gifFrameCounter{0};
		MsfGifState gifState{};
		msf_gif_begin(&gifState, ScreenWidth, ScreenHeight);
		TraceLog(LOG_INFO, "Start animated GIF recording");

		// Initialize the window and start the main loop
		InitWindow(ScreenWidth, ScreenHeight, "Sorting Visualization");
		SetTargetFPS(60);

		while (!WindowShouldClose())
		{
				if (gifFrameCounter++ >= GIF_RECORD_FRAMERATE)
				{
						// Get image data for the current frame (from backbuffer)
						auto imScreen = LoadImageFromScreen();

						// Add the frame to the gif recording, providing and "estimated" time for display in
						// centiseconds
						msf_gif_frame(
							&gifState, reinterpret_cast<uint8_t*>(imScreen.data),
							((1.0f / 60.0f) * GIF_RECORD_FRAMERATE) / 10, 16, imScreen.width * 4
						);
						gifFrameCounter = 0;
						UnloadImage(imScreen);
				}

				BeginDrawing();
				PollInputEvents();
				DrawFPS(10, 10);
				ClearBackground(BLACK);
				// sort::SortStepSelection(rectangles, trackers, sorted);
				// sort::SortStepBubble(rectangles, trackers, sorted);
				sort::SortStepInsertion(rectangles, trackers, sorted);
				utils::DrawRectangles(rectangles, ScreenWidth, ScreenHeight, trackers, sorted);

				EndDrawing();
		}

		// Finalize the GIF recording and free resources
		auto result = msf_gif_end(&gifState);
		SaveFileData(
			TextFormat("%s%s", GetApplicationDirectory(), gifFileName), result.data, result.dataSize
		);
		msf_gif_free(result);
		TraceLog(
			LOG_INFO, "Finished animated GIF recording, saved to: %s%s", GetApplicationDirectory(),
			gifFileName
		);

		CloseWindow();
		return 0;
}
