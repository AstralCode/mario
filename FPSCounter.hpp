#pragma once

class FPSCounter final
{
public:
	FPSCounter() noexcept;

	void tick() noexcept;
	unsigned int restart() noexcept;

private:
	unsigned int mCounter;
};

