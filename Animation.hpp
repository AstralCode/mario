#pragma once

#include <vector>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Rect.hpp"

#include "SpriteArea.hpp"

class SpritesetRegion;

class Animation final
{
public:
	enum class Status
	{
		Playing,
		Pause,
		End
	};

	enum class Directions
	{
		Normal,
		Reverse,
		Alternate,
		AlternateReverse
	};

	Animation(const SpritesetRegion& spritesetRegion) noexcept;

	void setDelay(const sf::Time& delay);
	void setDirection(const Directions direction) noexcept;
	void setDuration(const sf::Time& durationTime) noexcept;
	void setRepeating(const bool repeat) noexcept;

	void play() noexcept;
	void pause() noexcept;
	void stop() noexcept;

	void update(const sf::Time& frameTime) noexcept;

	const SpriteArea& getCurrentSpriteArea() const noexcept;

	int getSpriteCount() const noexcept;

	const sf::Time& getDurationTime() const noexcept;

	Status getStatus() const noexcept;

private:
	void updateSpriteNormalDirection() noexcept;
	void updateSpriteReverseDirection() noexcept;
	void updateSpriteAlternateDirection() noexcept;
	void updateSpriteAlternateReverseDirection() noexcept;

	sf::Time calculateAnimationFrameTime() const noexcept;

	constexpr int getFirstSpriteIndex() const noexcept;
	int getLastSpriteIndex() const noexcept;

	const SpritesetRegion& mSpritesetRegion;

	Status mStatus;
	Directions mDirection;

	sf::Time mDurationTime;
	sf::Time mElapsedUpdateTime;
	sf::Time mDelayTime;
	sf::Time mElapsedDelayTime;

	int mCurrentSpriteIndex;

	bool mPlaying;
	bool mReachEnd;
	bool mAlternate;
	bool mRepeating;
};
