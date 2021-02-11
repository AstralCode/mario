#include "Animation.hpp"

#include "SpriteAtlasRegion.hpp"

Animation::Animation() :
	mSprites{nullptr},
	mCurrentSpriteIndex{0},
	mPlaying{false}
{

}

void Animation::setSprites(const SpriteAtlasRegion* spriteAtlasRegion)
{
	mSprites = spriteAtlasRegion;
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
	return mSprites->getSprite(mCurrentSpriteIndex);
}

int Animation::getSpriteCount() const
{
	return mSprites->getSpriteCount();
}

const sf::Time& Animation::getDurationTime() const
{
	return mDurationTime;
}

bool Animation::isPlaying() const
{
	return mPlaying;
}
