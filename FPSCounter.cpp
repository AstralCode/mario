#include "FPSCounter.hpp"

FPSCounter::FPSCounter() noexcept :
	mCounter{0u}
{

}

void FPSCounter::tick() noexcept
{
	++mCounter;
}

unsigned int FPSCounter::restart() noexcept
{
	const auto counter{mCounter};

	mCounter = 0u;

	return counter;
}
