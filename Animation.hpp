#pragma once

#include "SFML/System/Time.hpp"

#include "SpritesetRegion.hpp"

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

	Animation() noexcept;

	void setSpriteset(const SpritesetRegion& spriteset) noexcept;

	void setDelay(const sf::Time& delay);
	void setDirection(const Directions direction) noexcept;
	void setDuration(const sf::Time& durationTime) noexcept;
	void setRepeating(const bool repeat) noexcept;

	void play() noexcept;
	void pause() noexcept;
	void stop() noexcept;

	void update(const sf::Time& dt) noexcept;

	const SpriteArea& getCurrentSpriteArea() const noexcept;

	int getSpriteCount() const noexcept;

	const sf::Time& getDurationTime() const noexcept;

	Status getStatus() const noexcept;

private:
	void updateSpriteNormalDirection() noexcept;
	void updateSpriteReverseDirection() noexcept;
	void updateSpriteAlternateDirection() noexcept;
	void updateSpriteAlternateReverseDirection() noexcept;

	sf::Time calculateFrameTime() const noexcept;

	constexpr int getFirstSpriteIndex() const noexcept;
	int getLastSpriteIndex() const noexcept;

	SpritesetRegion mSpriteset;

	Status mStatus;
	Directions mDirection;

	sf::Time mDurationTime;
	sf::Time mElapsedUpdateTime;
	sf::Time mDelayTime;
	sf::Time mElapsedDelayTime;

	int mCurrentSpriteIndex;

	bool mIsPlaying;
	bool mIsReachEnd;
	bool mIsAlternate;
	bool mIsRepeating;
};
