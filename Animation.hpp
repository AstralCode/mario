#pragma once

#include <vector>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion;

class Animation final
{
public:
	Animation(SpriteAtlasRegion& spriteAtlasRegion);

	void setDuration(const sf::Time& durationTime);

	void play();
	void pause();
	void stop();

	void update(const sf::Time& frameTime);

	const sf::IntRect& getCurrentFrame() const;

	int getFrameCount() const;

	const sf::Time& getDurationTime() const;

	bool isPlaying() const;

private:
	void updateCurrentFrame(const sf::Vector2i& currentFrameIndex);

	SpriteAtlasRegion& mSpriteAtlasRegion;

	sf::Time mDurationTime;
	sf::Time mElapsedUpdateTime;

	sf::Vector2i mCurrentFrameIndex;
	sf::IntRect mCurrentFrame;

	bool mIsPlaying;
};
