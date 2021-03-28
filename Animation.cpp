#include "Animation.hpp"

#include "SpritesetRegion.hpp"

Animation::Animation() noexcept :
	mDirection{Directions::Normal},
	mCurrentSpriteIndex{getFirstSpriteIndex()},
	mIsPlaying{false},
	mIsReachEnd{true},
	mIsAlternate{false},
	mIsRepeating{false}
{

}

void Animation::setSpriteset(const SpritesetRegion& spriteset) noexcept
{
	mSpriteset = spriteset;
}

void Animation::setDelay(const sf::Time& delay)
{
	mDelayTime = delay;
}

void Animation::setDirection(const Directions direction) noexcept
{
	mDirection = direction;
}

void Animation::setDuration(const sf::Time& durationTime) noexcept
{
	mDurationTime = durationTime;
}

void Animation::setRepeating(const bool repeat) noexcept
{
	mIsRepeating = repeat;
}

void Animation::play() noexcept
{
	mIsPlaying = true;
}

void Animation::pause() noexcept
{
	mIsPlaying = false;
}

void Animation::stop() noexcept
{
	mElapsedUpdateTime = sf::Time::Zero;
	mCurrentSpriteIndex = (mDirection == Directions::Normal || mDirection == Directions::Alternate) ? getFirstSpriteIndex() : getLastSpriteIndex();
	mIsPlaying = false;
	mIsReachEnd = true;
	mIsAlternate = false;
}

void Animation::update(const sf::Time& dt) noexcept
{
	if (mIsPlaying)
	{
		if (mElapsedDelayTime >= mDelayTime)
		{
			const auto animationFrameTime = calculateAnimationFrameTime();

			mElapsedUpdateTime += dt;

			while (mElapsedUpdateTime >= animationFrameTime)
			{
				switch (mDirection)
				{
				case Directions::Normal:
					updateSpriteNormalDirection();
					break;
				case Directions::Reverse:
					updateSpriteReverseDirection();
					break;
				case Directions::Alternate:
					updateSpriteAlternateDirection();
					break;
				case Directions::AlternateReverse:
					updateSpriteAlternateReverseDirection();
					break;
				}
				
				mElapsedUpdateTime -= animationFrameTime;
			}
		}
		else
		{
			mElapsedDelayTime += dt;
		}
	}
}

const IntArea& Animation::getCurrentSpriteArea() const noexcept
{
	return mSpriteset.getSpriteArea(mCurrentSpriteIndex);
}

int Animation::getSpriteCount() const noexcept
{
	return mSpriteset.getSpriteCount();
}

const sf::Time& Animation::getDurationTime() const noexcept
{
	return mDurationTime;
}

Animation::Status Animation::getStatus() const noexcept
{
	if (mIsPlaying)
	{
		return Animation::Status::Playing;
	}
	else if(!mIsReachEnd)
	{
		return Animation::Status::Pause;
	}

	return Animation::Status::End;
}

void Animation::updateSpriteNormalDirection() noexcept
{
	++mCurrentSpriteIndex;

	if (mCurrentSpriteIndex > getLastSpriteIndex())
	{
		mCurrentSpriteIndex = getFirstSpriteIndex();

		if (!mIsRepeating)
		{
			stop();
		}

		mElapsedDelayTime = sf::Time::Zero;
	}
}

void Animation::updateSpriteReverseDirection() noexcept
{
	--mCurrentSpriteIndex;

	if (mCurrentSpriteIndex < getFirstSpriteIndex())
	{
		mCurrentSpriteIndex = getLastSpriteIndex();

		if (!mIsRepeating)
		{
			stop();
		}

		mElapsedDelayTime = sf::Time::Zero;
	}
}

void Animation::updateSpriteAlternateDirection() noexcept
{
	if (!mIsAlternate)
	{
		++mCurrentSpriteIndex;

		if (mCurrentSpriteIndex > getLastSpriteIndex())
		{
			mCurrentSpriteIndex = getLastSpriteIndex();
			mIsAlternate = true;
		}
	}
	else
	{
		--mCurrentSpriteIndex;

		if (mCurrentSpriteIndex < getFirstSpriteIndex())
		{
			mCurrentSpriteIndex = getFirstSpriteIndex();
			mIsAlternate = false;

			if (!mIsRepeating)
			{
				stop();
			}

			mElapsedDelayTime = sf::Time::Zero;
		}
	}
}

void Animation::updateSpriteAlternateReverseDirection() noexcept
{
	if (!mIsAlternate)
	{
		--mCurrentSpriteIndex;

		if (mCurrentSpriteIndex < getFirstSpriteIndex())
		{
			mCurrentSpriteIndex = getFirstSpriteIndex();
			mIsAlternate = true;
		}
	}
	else
	{
		++mCurrentSpriteIndex;

		if (mCurrentSpriteIndex > getLastSpriteIndex())
		{
			mCurrentSpriteIndex = getLastSpriteIndex();
			mIsAlternate = false;

			if (!mIsRepeating)
			{
				stop();
			}

			mElapsedDelayTime = sf::Time::Zero;
		}
	}
}

sf::Time Animation::calculateAnimationFrameTime() const noexcept
{
	return getDurationTime() / static_cast<float>(getSpriteCount());
}

constexpr int Animation::getFirstSpriteIndex() const noexcept
{
	return 0;
}

int Animation::getLastSpriteIndex() const noexcept
{
	return getSpriteCount() - 1;
}
