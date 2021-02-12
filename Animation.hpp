#pragma once

#include <vector>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion;

class Animation final
{
public:
	enum class Directions
	{
		Normal,
		Reverse,
		Alternate,
		AlternateReverse
	};

	Animation(const SpriteAtlasRegion& sprites) noexcept;

	void setDirection(const Directions direction) noexcept;
	void setDuration(const sf::Time& durationTime) noexcept;
	void setRepeating(const bool repeat) noexcept;

	void play() noexcept;
	void pause() noexcept;
	void stop() noexcept;

	void update(const sf::Time& frameTime) noexcept;

	const sf::IntRect& getCurrentSprite() const noexcept;

	int getSpriteCount() const noexcept;

	const sf::Time& getDurationTime() const noexcept;

	bool isPlaying() const noexcept;
	bool isRepeating() const noexcept;

private:
	constexpr int getFirstSpriteIndex() const noexcept;
	int getLastSpriteIndex() const noexcept;

	const SpriteAtlasRegion& mSprites;

	Directions mDirection;

	sf::Time mDurationTime;
	sf::Time mElapsedUpdateTime;

	int mCurrentSpriteIndex;

	bool mPlaying;
	bool mRepeating;
	bool mReachEnd;
};
