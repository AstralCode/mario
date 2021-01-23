#pragma once

class FPSCounter final
{
public:
	FPSCounter();

	void tick();
	unsigned int restart();

private:
	unsigned int mCounter;
};

