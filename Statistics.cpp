#include "Statistics.hpp"

#include "SFML/Graphics/Font.hpp"

Statistics::Statistics(FPSCounter& fpsCounter) :
	mFPSCounter{fpsCounter},
	mUpdateTime{sf::seconds(1.0f)},
	mIsVisible{false}
{
	mFPSCounterGraphicsText = mGraphicsItem.addItem<GraphicsTextItem>();
	mFPSCounterGraphicsText->setPosition(6.0f, 6.0f);
	mFPSCounterGraphicsText->setString("FPS: 0");
	mFPSCounterGraphicsText->setCharacterSize(12u);
}

void Statistics::setPosition(const float x, const float y)
{
	mFPSCounterGraphicsText->setPosition(x, y);
}

void Statistics::setText(const sf::Font& font, const unsigned int characterSize)
{
	mFPSCounterGraphicsText->setFont(font);
	mFPSCounterGraphicsText->setCharacterSize(characterSize);
}

void Statistics::setVisible(const bool visible)
{
	mIsVisible = visible;
}

void Statistics::update(const sf::Time& deltaTime)
{
	mElapsedUpdateTime += deltaTime;

	if (mElapsedUpdateTime > mUpdateTime)
	{
		const auto fpsCounter = mFPSCounter.restart();

		if (mIsVisible)
		{
			if (mFPSCounterGraphicsText)
			{
				mFPSCounterGraphicsText->setString("FPS: " + std::to_string(fpsCounter));
			}
		}

		mElapsedUpdateTime = sf::Time::Zero;
	}
}

const FPSCounter& Statistics::getFPSCounter() const
{
	return mFPSCounter;
}

const GraphicsItem& Statistics::getGraphics() const
{
	return mGraphicsItem;
}

bool Statistics::isVisible()
{
	return mIsVisible;
}
