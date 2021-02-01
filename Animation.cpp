#include "Animation.hpp"

#include "SpriteAtlasRegion.hpp"

Animation::Animation() :
	mSpriteAtlasRegion{nullptr},
	mCurrentSpriteIndex{0},
	mPlaying{false}
{

}

void Animation::setSpriteAtlasRegion(const SpriteAtlasRegion* spriteAtlasRegion)
{
	mSpriteAtlasRegion = spriteAtlasRegion;
}

void Animation::setDuration(const sf::Time& durationTime)
{
	mDurationTime = durationTime;
}

void Animation::play()
{
	mPlaying = true;
}

void Animation::pause()
{
	mPlaying = false;
}

void Animation::stop()
{
	mElapsedUpdateTime = sf::Time::Zero;
	mCurrentSpriteIndex = 0;
	mPlaying = false;
}

void Animation::update(const sf::Time& frameTime)
{
	if (isPlaying())
	{
		const auto spriteCount = getSpriteCount();
		const auto animationFrameTime = mDurationTime / static_cast<float>(spriteCount);

		mElapsedUpdateTime += frameTime;

		while (mElapsedUpdateTime > animationFrameTime)
		{
			if (++mCurrentSpriteIndex >= spriteCount)
			{
				mCurrentSpriteIndex = 0;
			}

			mElapsedUpdateTime -= animationFrameTime;
		}
	}
}

const sf::IntRect& Animation::getCurrentSprite() const
{
	return mSpriteAtlasRegion->getSprite(mCurrentSpriteIndex);
}

int Animation::getSpriteCount() const
{
	return mSpriteAtlasRegion->getSpriteCount();
}

const sf::Time& Animation::getDurationTime() const
{
	return mDurationTime;
}

bool Animation::isPlaying() const
{
	return mPlaying;
}
