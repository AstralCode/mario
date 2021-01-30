#pragma once

#include <vector>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion;

class Animation final
{
public:
	Animation();

	void setSpriteAtlasRegion(const SpriteAtlasRegion* spriteAtlasRegion);

	void setDuration(const sf::Time& durationTime);

	void play();
	void pause();
	void stop();

	void update(const sf::Time& frameTime);

	const sf::IntRect& getCurrentSprite() const;

	int getSpriteCount() const;

	const sf::Time& getDurationTime() const;

	bool isPlaying() const;

private:
	const SpriteAtlasRegion* mSpriteAtlasRegion;

	sf::Time mDurationTime;
	sf::Time mElapsedUpdateTime;

	sf::Vector2i mCurrentSpriteIndex;
	int mSpriteCount;

	bool mIsPlaying;
};
