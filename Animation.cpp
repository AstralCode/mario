#include "Animation.hpp"

#include "SpriteAtlasRegion.hpp"

Animation::Animation(const SpriteAtlasRegion& sprites) noexcept :
	mSprites{sprites},
	mDirection{Directions::Normal},
	mCurrentSpriteIndex{getFirstSpriteIndex()},
	mPlaying{false},
	mRepeating{false},
	mReachEnd{false}
{

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
	mReachEnd = false;
}

void Animation::update(const sf::Time& frameTime) noexcept
{
	if (isPlaying())
	{
		const auto animationFrameTime = mDurationTime / static_cast<float>(getSpriteCount());

		mElapsedUpdateTime += frameTime;

		while (mElapsedUpdateTime > animationFrameTime)
		{
			if (mDirection == Directions::Normal)
			{
				++mCurrentSpriteIndex;

				if (mCurrentSpriteIndex > getLastSpriteIndex())
				{
					mCurrentSpriteIndex = getFirstSpriteIndex();

					if (!isRepeating())
					{
						stop();
					}
				}
			}
			else if (mDirection == Directions::Reverse)
			{
				--mCurrentSpriteIndex;

				if (mCurrentSpriteIndex < getFirstSpriteIndex())
				{
					mCurrentSpriteIndex = getLastSpriteIndex();
					
					if (!isRepeating())
					{
						stop();
					}
				}
			}
			else if (mDirection == Directions::Alternate)
			{
				if (!mReachEnd)
				{
					++mCurrentSpriteIndex;

					if (mCurrentSpriteIndex > getLastSpriteIndex())
					{
						mCurrentSpriteIndex = getLastSpriteIndex();
						mReachEnd = true;
					}
				}
				else
				{
					--mCurrentSpriteIndex;

					if (mCurrentSpriteIndex < getFirstSpriteIndex())
					{
						mCurrentSpriteIndex = getFirstSpriteIndex();
						mReachEnd = false;

						if (!isRepeating())
						{
							stop();
						}
					}
				}
			}
			else if (mDirection == Directions::AlternateReverse)
			{
				if (!mReachEnd)
				{
					--mCurrentSpriteIndex;

					if (mCurrentSpriteIndex < getFirstSpriteIndex())
					{
						mCurrentSpriteIndex = getFirstSpriteIndex();
						mReachEnd = true;
					}
				}
				else
				{
					++mCurrentSpriteIndex;

					if (mCurrentSpriteIndex > getLastSpriteIndex())
					{
						mCurrentSpriteIndex = getLastSpriteIndex();
						mReachEnd = false;

						if (!isRepeating())
						{
							stop();
						}
					}
				}
			}

			mElapsedUpdateTime -= animationFrameTime;
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

bool Animation::isPlaying() const noexcept
{
	return mPlaying;
}

bool Animation::isRepeating() const noexcept
{
	return mRepeating;
}

constexpr int Animation::getFirstSpriteIndex() const noexcept
{
	return 0;
}

int Animation::getLastSpriteIndex() const noexcept
{
	return getSpriteCount() - 1;
}
