#include "Statistics.hpp"

#include "SFML/Graphics/Font.hpp"

Statistics::Statistics(FPSCounter& fpsCounter) noexcept :
	mFPSCounter{fpsCounter},
	mUpdateTime{sf::seconds(1.0f)},
	mVisible{false}
{
	mFPSCounterGraphicsText = mGraphicsItem.addItem<GraphicsTextItem>();
	mFPSCounterGraphicsText->setPosition(6.0f, 6.0f);
	mFPSCounterGraphicsText->setString("FPS: 0");
	mFPSCounterGraphicsText->setCharacterSize(12u);
}

void Statistics::setPosition(const float x, const float y) noexcept
{
	mFPSCounterGraphicsText->setPosition(x, y);
}

void Statistics::setText(const sf::Font& font, const unsigned int characterSize) noexcept
{
	mFPSCounterGraphicsText->setFont(font);
	mFPSCounterGraphicsText->setCharacterSize(characterSize);
}

void Statistics::setVisible(const bool visible) noexcept
{
	mVisible = visible;
}

void Statistics::update(const sf::Time& updateTime) noexcept
{
	if (isVisible())
	{
		mElapsedUpdateTime += updateTime;

		if (mElapsedUpdateTime > mUpdateTime)
		{
			if (mFPSCounterGraphicsText)
			{
				const auto fpsCounter = mFPSCounter.restart();
				mFPSCounterGraphicsText->setString("FPS: " + std::to_string(fpsCounter));
			}

			mElapsedUpdateTime = sf::Time::Zero;
		}
	}
}

const FPSCounter& Statistics::getFPSCounter() const noexcept
{
	return mFPSCounter;
}

const GraphicsItem& Statistics::getGraphics() const noexcept
{
	return mGraphicsItem;
}

bool Statistics::isVisible() noexcept
{
	return mVisible;
}
