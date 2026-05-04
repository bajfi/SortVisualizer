// Copyright (c) 2026 JackLee
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include "raylib.h"
#include <random>
#include <unordered_set>
#include <vector>

struct utils
{
    /**
     * @brief Draws the rectangles on the screen. If the sorting is complete, it uses a sliding
     * window to highlight the sorted rectangles in green. Otherwise, it highlights the rectangles
     * being compared or swapped in red.
     * @tparam Container The type of the container holding the rectangles (e.g.,
     * std::vector<float>).
     * @param rectangles The container of rectangles to be drawn, where each element represents the
     * height of a rectangle.
     * @param ScreenWidth The width of the screen for scaling the rectangles.
     * @param ScreenHeight The height of the screen for scaling the rectangles.
     */
    template <typename Container>
    static void DrawSortedComplete(const Container& rectangles, int ScreenWidth, int ScreenHeight)
    {
        if (static bool firstTime = true; firstTime)
        {
            SetTargetFPS(30); // Reset FPS to normal after the animation is complete
            firstTime = false;
        }

        // Create a sliding window to move across the sorted rectangles
        // Color the windows as green to indicate completion
        size_t N = rectangles.size();
        size_t windowSize = N / 20;
        static size_t windowStart = 0; // Starting index of the sliding window
        if (windowStart >= N)
        {
            DrawRectangles(
              rectangles, ScreenWidth, ScreenHeight, std::unordered_set<size_t>{}, false
            );
            return; // All rectangles have been drawn, exit the function
        }
        auto step = 1.0f * ScreenWidth / N;
        for (size_t i = 0; i < N; ++i)
        {
            auto value = rectangles[i];
            auto height = value * 0.9f * ScreenHeight; // Scale height to fit within the screen
            if (i >= windowStart && i < windowStart + windowSize)
                DrawRectangle(i * step, ScreenHeight - height, step, height, GREEN);
            else
                DrawRectangle(i * step, ScreenHeight - height, step, height, RAYWHITE);
        }
        windowStart += windowSize; // Move the sliding window to the right
    }

    /**
     * @brief Draws the rectangles on the screen. If the sorting is complete, it calls
     * DrawSortedComplete to highlight the sorted rectangles. Otherwise, it highlights the
     * rectangles being compared or swapped in red, while the rest are drawn in white.
     * @tparam Container The type of the container holding the rectangles (e.g.,
     * std::vector<float>).
     * @tparam Tracker The type of the tracker used to identify which rectangles are being compared
     * or swapped (e.g., std::unordered_set<size_t>).
     * @param rectangles The container of rectangles to be drawn, where each element represents the
     * height of a rectangle.
     * @param ScreenWidth The width of the screen for scaling the rectangles.
     * @param ScreenHeight The height of the screen for scaling the rectangles.
     * @param trackers The tracker containing the indices of the rectangles being compared or
     * swapped.
     * @param sorted A boolean indicating whether the sorting is complete or not.
     */
    template <typename Container, typename Tracker>
    static void DrawRectangles(
      const Container& rectangles,
      int ScreenWidth,
      int ScreenHeight,
      const Tracker& trackers,
      bool sorted
    )
    {
        size_t N = rectangles.size();
        auto step = 1.0f * ScreenWidth / N;

        if (sorted)
        {
            DrawSortedComplete(rectangles, ScreenWidth, ScreenHeight);
            return;
        }

        for (size_t i = 0; i < N; ++i)
        {
            auto value = rectangles[i];
            // Scale height to fit within the screen
            auto height = value * 0.9f * ScreenHeight; // 0.9 to leave some margin at the top

            if (trackers.contains(i))
                DrawRectangle(i * step, ScreenHeight - height, step, height, RED);
            else
                DrawRectangle(i * step, ScreenHeight - height, step, height, RAYWHITE);
        }
    }

    /**
     * @brief Generates a vector of random numbers between 0 and 1.
     * @tparam T The type of the numbers to generate.
     * @param N The number of random numbers to generate.
     * @return A vector containing the generated random numbers.
     */
    template <typename T>
    static std::vector<T> generate01RandomNumber(size_t N)
    {
        std::vector<T> rectangles(N);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(0.0, 1.0);

        for (size_t i = 0; i < N; ++i)
        {
            rectangles[i] = dis(gen);
        }
        return rectangles;
    }
};
