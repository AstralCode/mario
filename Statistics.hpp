#pragma once

#include "SFML/System/Time.hpp"

#include "FPSCounter.hpp"
#include "GraphicsTextItem.hpp"

class Statistics final
{
public:
	Statistics(FPSCounter& fpsCounter);

	void setPosition(const float x, const float y);
	void setText(const sf::Font& font, const unsigned int characterSize = 12u);
	void setVisible(const bool enabled);

	void update(const sf::Time& deltaTime);

	const FPSCounter& getFPSCounter() const;
	const GraphicsItem& getGraphics() const;

	bool isVisible();

private:
	FPSCounter& mFPSCounter;

	sf::Time mUpdateTime;
	sf::Time mElapsedUpdateTime;

	GraphicsItem mGraphicsItem;
	GraphicsTextItem* mFPSCounterGraphicsText;

	bool mIsVisible;
};
