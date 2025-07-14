#pragma once

#include <SDL3/SDL_timer.h>

#include <cstdint>
#include <concepts>
#include <optional>

class Timer
{
private:
	uint64_t last = GetPerformanceCounter();

public:
	inline uint64_t GetPerformanceCounter()
	{
		return SDL_GetPerformanceCounter();
	}

	inline uint64_t GetPerformanceFrequency()
	{
		return SDL_GetPerformanceFrequency();
	}

	inline double Elapsed()
	{
		return static_cast<double>(GetPerformanceCounter() - last) / static_cast<double>(GetPerformanceFrequency());
	}

	inline void Reset()
	{
		last = GetPerformanceCounter();
	}
};

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template<arithmetic T, size_t size>
class Sampler
{
	T samples[size];
	size_t index;

public:
	void Push(T n)
	{
		samples[index] = n;

		if (++index >= size)
		{
			index = 0;
		}
	}

	std::optional<T> Max() const
	{
		std::optional<T> max;

		for (size_t i = 0; i < size; i++)
		{
			if (!max.has_value() || samples[i] > max.value())
			{
				max = samples[i];
			}
		}

		return max;
	}

	std::optional<T> Min() const
	{
		std::optional<T> min;

		for (size_t i = 0; i < size; i++)
		{
			if (!min.has_value() || samples[i] < min.value())
			{
				min = samples[i];
			}
		}

		return min;
	}

	T Average() const
	{
		T total = 0;

		for (size_t i = 0; i < size; i++)
		{
			total += samples[i];
		}

		return total / static_cast<T>(size);
	}
};
