#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Rect.hpp"

class Animation final
{
public:
	Animation();

	void setDuration(const sf::Time& durationTime);
	void setFrameCount(const sf::Vector2i& frameCount);
	void setFrameOffset(const sf::Vector2i& frameOffset);
	void setFrameSize(const sf::IntRect& frameSize);

	void play();
	void pause();
	void stop();

	void update(const sf::Time& frameTime);

	sf::IntRect getCurrentFrame() const;

	int getFrameCount() const;

	const sf::Time& getDurationTime() const;

	bool isPlaying() const;

private:
	void updateCurrentFrame(const sf::Vector2i& currentFrameIndex);

	sf::Time mDurationTime;
	sf::Time mElapsedUpdateTime;

	sf::Vector2i mCurrentFrameIndex;
	sf::Vector2i mFrameCount;
	sf::Vector2i mFrameOffset;
	sf::IntRect mFrameSize;

	sf::IntRect mCurrentFrame;

	bool mIsPlaying;
};
