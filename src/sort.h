// Copyright (c) 2026 JackLee
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <algorithm>
#include <ranges>

struct sort
{
		/**
		 * @brief Performs one step of the selection sort algorithm on the given container of
		 * rectangles. This function identifies the minimum element in the unsorted portion of the array
		 * and swaps it with the first element of that portion. It also updates the tracker to highlight
		 * the swapped elements.
		 * @param rectangles The container of rectangles to be sorted.
		 * @param tracker The tracker used to highlight the indices of the swapped elements.
		 * @param sorted A boolean reference that will be set to true if the sorting is complete,
		 * otherwise it will remain false.
		 */
		template <std::ranges::range Container, typename Tracker>
		static void SortStepSelection(Container& rectangles, Tracker& tracker, bool& sorted)
		{
				static size_t RIGHT_IDX = 0;
				const size_t N = rectangles.size();
				if (RIGHT_IDX >= N - 1)
				{
						sorted = true;
						return;
				}
				// Find the index of the minimum element in the unsorted portion of the array
				auto min_ele = std::min_element(std::begin(rectangles) + RIGHT_IDX, std::end(rectangles));

				// Swap the found minimum element with the first element of the unsorted portion
				std::swap(rectangles[RIGHT_IDX], *min_ele);

				// Update the tracker to highlight the swapped elements
				tracker.clear();
				tracker.insert(RIGHT_IDX);
				tracker.insert(std::distance(std::begin(rectangles), min_ele));
				++RIGHT_IDX;
		}

		/**
		 * @brief Performs one step of the bubble sort algorithm on the given container of rectangles.
		 * This function compares adjacent elements and swaps them if they are in the wrong order. It
		 * also updates the tracker to highlight the indices of the swapped elements.
		 * @param rectangles The container of rectangles to be sorted.
		 * @param tracker The tracker used to highlight the indices of the swapped elements.
		 * @param sorted A boolean reference that will be set to true if the sorting is complete,
		 * otherwise it will remain false.
		 */
		template <std::ranges::range Container, typename Tracker>
		static void SortStepBubble(Container& rectangles, Tracker& tracker, bool& sorted)
		{
				// Indicator to track if any swaps were made during this loop iteration
				const size_t N = rectangles.size();
				static size_t RIGHT_IDX = N - 1;
				static size_t CURR_IDX = 0;
				static bool swapped = false;

				if (RIGHT_IDX <= 0)
				{
						sorted = true;
						return;
				}
				if (rectangles[CURR_IDX] > rectangles[CURR_IDX + 1])
				{
						tracker.clear();
						std::swap(rectangles[CURR_IDX], rectangles[CURR_IDX + 1]);
						tracker.insert(CURR_IDX);
						tracker.insert(CURR_IDX + 1);

						swapped = true;
				}

				++CURR_IDX;
				if (CURR_IDX >= RIGHT_IDX)
				{
						CURR_IDX = 0;
						--RIGHT_IDX;

						if (!swapped)
						{
								sorted = true;
						}
						swapped = false;
				}
		}

		/**
		 * @brief Performs one step of the insertion sort algorithm on the given container of
		 * rectangles. This function takes the next element from the unsorted portion of the array and
		 * inserts it into the correct position in the sorted portion. It also updates the tracker to
		 * highlight the indices of the compared or swapped elements.
		 * @param rectangles The container of rectangles to be sorted.
		 * @param tracker The tracker used to highlight the indices of the compared or swapped elements.
		 * @param sorted A boolean reference that will be set to true if the sorting is complete,
		 * otherwise it will remain false.
		 */
		template <std::ranges::range Container, typename Tracker>
		static void SortStepInsertion(Container& rectangles, Tracker& tracker, bool& sorted)
		{
				const size_t N = rectangles.size();
				static size_t RIGHT_IDX = 1;
				static size_t CURRENT_IDX = RIGHT_IDX;
				static bool loopOver = true;

				// Find the next element to be inserted into the sorted portion of the array
				while (loopOver && rectangles[RIGHT_IDX] > rectangles[RIGHT_IDX - 1] && RIGHT_IDX < N)
				{
						++RIGHT_IDX;
				}

				if (RIGHT_IDX >= N)
				{
						sorted = true;
						return;
				}

				// Insert the current element into the correct position in the sorted portion of the array
				if (rectangles[CURRENT_IDX] > rectangles[CURRENT_IDX - 1])
				{
						CURRENT_IDX = RIGHT_IDX;
						loopOver = true;
				}
				else
				{
						tracker.clear();
						tracker.insert(CURRENT_IDX);
						tracker.insert(CURRENT_IDX - 1);
						std::swap(rectangles[CURRENT_IDX], rectangles[CURRENT_IDX - 1]);
						--CURRENT_IDX;
						loopOver = false;
				}
		}

		/**
		 * @brief Performs one step of the cocktail shaker sort algorithm on the given container of
		 * rectangles. This function is a variation of bubble sort that sorts in both directions on each
		 * pass through the list. It compares adjacent elements and swaps them if they are in the wrong
		 * order, and it also updates the tracker to highlight the indices of the compared or swapped
		 * elements.
		 * @param rectangles The container of rectangles to be sorted.
		 * @param tracker The tracker used to highlight the indices of the compared or swapped elements.
		 * @param sorted A boolean reference that will be set to true if the sorting is complete,
		 * otherwise it will remain false.
		 */
		template <std::ranges::range Container, typename Tracker>
		static void SortStepCocktail(Container& rectangles, Tracker& tracker, bool& sorted)
		{
				const size_t N = rectangles.size();
				static size_t LEFT_IDX = 0;
				static size_t RIGHT_IDX = N - 1;
				static size_t CURR_IDX = 0;
				static bool swapped = false;
				static bool forward = true;

				if (RIGHT_IDX <= LEFT_IDX)
				{
						sorted = true;
						return;
				}

				if (forward)
				{
						if (rectangles[CURR_IDX] > rectangles[CURR_IDX + 1])
						{
								tracker.clear();
								std::swap(rectangles[CURR_IDX], rectangles[CURR_IDX + 1]);
								tracker.insert(CURR_IDX);
								tracker.insert(CURR_IDX + 1);
								swapped = true;
						}

						++CURR_IDX;
						if (CURR_IDX >= RIGHT_IDX)
						{
								--RIGHT_IDX;
								CURR_IDX = RIGHT_IDX;
								forward = false;

								if (!swapped)
								{
										sorted = true;
								}
								swapped = false;
						}
				}
				else
				{
						if (rectangles[CURR_IDX] < rectangles[CURR_IDX - 1])
						{
								tracker.clear();
								std::swap(rectangles[CURR_IDX], rectangles[CURR_IDX - 1]);
								tracker.insert(CURR_IDX);
								tracker.insert(CURR_IDX - 1);
								swapped = true;
						}

						--CURR_IDX;
						if (CURR_IDX <= LEFT_IDX)
						{
								++LEFT_IDX;
								CURR_IDX = LEFT_IDX;
								forward = true;

								if (!swapped)
								{
										sorted = true;
								}
								swapped = false;
						}
				}
		}
};
