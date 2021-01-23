#include "FPSCounter.hpp"

FPSCounter::FPSCounter() :
	mCounter{0u}
{

}

void FPSCounter::tick()
{
	++mCounter;
}

unsigned int FPSCounter::restart()
{
	const auto counter = mCounter;
	mCounter = 0u;

	return counter;
}
