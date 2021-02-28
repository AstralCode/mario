#pragma once

#include "SFML/System/Time.hpp"

#include "FPSCounter.hpp"
#include "Text.hpp"

class Statistics final
{
public:
	Statistics(FPSCounter& fpsCounter) noexcept;

	void setPosition(const float x, const float y) noexcept;
	void setText(const sf::Font& font, const unsigned int characterSize = 12u) noexcept;

	void setVisible(const bool enabled) noexcept;

	void update(const sf::Time& updateTime) noexcept;

	const FPSCounter& getFPSCounter() const noexcept;
	const GraphicsItem& getGraphics() const noexcept;

	bool isVisible() noexcept;

private:
	FPSCounter& mFPSCounter;

	sf::Time mUpdateTime;
	sf::Time mElapsedUpdateTime;

	GraphicsItem mGraphicsItem;
	Text* mFPSCounterGraphicsText;

	bool mVisible;
};
