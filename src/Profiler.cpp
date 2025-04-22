#include "Profiler.h"

double Timer::Elapsed() {
	return (double)(GetPerformanceCounter() - last) / (double)GetPerformanceFrequency();
}

void Timer::Reset() {
	last = GetPerformanceCounter();
}

double Averager::Average() {
	double total = 0.0;

	for (double& n : samples) {
		total += n;
	}

	return total / (double)samples.size();
}
