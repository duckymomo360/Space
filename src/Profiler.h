#pragma once

#include <SDL3/SDL_timer.h>

#include <cstdint>
#include <deque>

struct Timer {
	uint64_t last = 0;

	double Elapsed();

	void Reset();

	static inline uint64_t GetPerformanceCounter() {
		return SDL_GetPerformanceCounter();
	}

	static inline uint64_t GetPerformanceFrequency() {
		return SDL_GetPerformanceFrequency();
	}
};

struct Averager {
	std::deque<double> samples;

	Averager() : samples(10) {}

	inline void Resize(size_t size) {
		samples.resize(size, 0);
	}

	inline void Push(double n) {
		samples.pop_back();
		samples.push_front(n);
	}

	double Average();
};
