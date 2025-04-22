#include "Profiler.h"

double Timer::Elapsed() {
	return (double)(GetPerformanceCounter() - last) / (double)GetPerformanceFrequency();
}

void Timer::Reset() {
	last = GetPerformanceCounter();
}
