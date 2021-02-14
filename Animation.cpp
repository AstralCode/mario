#include "Animation.hpp"

#include "SpriteAtlasRegion.hpp"

Animation::Animation(const SpriteAtlasRegion& sprites) noexcept :
	mSprites{sprites},
	mDirection{Directions::Normal},
	mCurrentSpriteIndex{getFirstSpriteIndex()},
	mPlaying{false},
	mReachEnd{true},
	mAlternate{false},
	mRepeating{false}
{

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
	mRepeating = repeat;
}

void Animation::play() noexcept
{
	mPlaying = true;
}

void Animation::pause() noexcept
{
	mPlaying = false;
}

void Animation::stop() noexcept
{
	mElapsedUpdateTime = sf::Time::Zero;
	mCurrentSpriteIndex = (mDirection == Directions::Normal || mDirection == Directions::Alternate) ? getFirstSpriteIndex() : getLastSpriteIndex();
	mPlaying = false;
	mReachEnd = true;
	mAlternate = false;
}

void Animation::update(const sf::Time& frameTime) noexcept
{
	if (mPlaying)
	{
		if (mElapsedDelayTime >= mDelayTime)
		{
			const auto animationFrameTime = calculateAnimationFrameTime();

			mElapsedUpdateTime += frameTime;

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
			mElapsedDelayTime += frameTime;
		}
	}
}

const sf::IntRect& Animation::getCurrentSprite() const noexcept
{
	return mSprites.getSprite(mCurrentSpriteIndex);
}

int Animation::getSpriteCount() const noexcept
{
	return mSprites.getSpriteCount();
}

const sf::Time& Animation::getDurationTime() const noexcept
{
	return mDurationTime;
}

Animation::Status Animation::getStatus() const noexcept
{
	if (mPlaying)
	{
		return Animation::Status::Playing;
	}
	else if(!mReachEnd)
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

		if (!mRepeating)
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

		if (!mRepeating)
		{
			stop();
		}

		mElapsedDelayTime = sf::Time::Zero;
	}
}

void Animation::updateSpriteAlternateDirection() noexcept
{
	if (!mAlternate)
	{
		++mCurrentSpriteIndex;

		if (mCurrentSpriteIndex > getLastSpriteIndex())
		{
			mCurrentSpriteIndex = getLastSpriteIndex();
			mAlternate = true;
		}
	}
	else
	{
		--mCurrentSpriteIndex;

		if (mCurrentSpriteIndex < getFirstSpriteIndex())
		{
			mCurrentSpriteIndex = getFirstSpriteIndex();
			mAlternate = false;

			if (!mRepeating)
			{
				stop();
			}

			mElapsedDelayTime = sf::Time::Zero;
		}
	}
}

void Animation::updateSpriteAlternateReverseDirection() noexcept
{
	if (!mAlternate)
	{
		--mCurrentSpriteIndex;

		if (mCurrentSpriteIndex < getFirstSpriteIndex())
		{
			mCurrentSpriteIndex = getFirstSpriteIndex();
			mAlternate = true;
		}
	}
	else
	{
		++mCurrentSpriteIndex;

		if (mCurrentSpriteIndex > getLastSpriteIndex())
		{
			mCurrentSpriteIndex = getLastSpriteIndex();
			mAlternate = false;

			if (!mRepeating)
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
