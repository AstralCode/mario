#include "Animation.hpp"

#include "SpriteAtlasRegion.hpp"

Animation::Animation() :
	mSpriteAtlasRegion{nullptr},
	mSpriteCount{0},
	mIsPlaying{false}
{

}

void Animation::setSpriteAtlasRegion(const SpriteAtlasRegion* spriteAtlasRegion)
{
	mSpriteAtlasRegion = spriteAtlasRegion;
	mSpriteCount = spriteAtlasRegion->getSpriteAreaCount();
}

void Animation::setDuration(const sf::Time& durationTime)
{
	mDurationTime = durationTime;
}

void Animation::play()
{
	mIsPlaying = true;
}

void Animation::pause()
{
	mIsPlaying = false;
}

void Animation::stop()
{
	mElapsedUpdateTime = sf::Time::Zero;
	mCurrentSpriteIndex = sf::Vector2i{};
	mIsPlaying = false;
}

void Animation::update(const sf::Time& frameTime)
{
	if (isPlaying())
	{
		const auto animationFrameTime = mDurationTime / static_cast<float>(getSpriteCount());

		mElapsedUpdateTime += frameTime;

		while (mElapsedUpdateTime > animationFrameTime)
		{
			const auto& spriteAreas = mSpriteAtlasRegion->getSpriteAreas();

			sf::Vector2i spriteCount{};
			spriteCount.x = static_cast<int>(spriteAreas[mCurrentSpriteIndex.y].size());
			spriteCount.y = static_cast<int>(spriteAreas.size());

			++mCurrentSpriteIndex.x;

			if (mCurrentSpriteIndex.x >= spriteCount.x)
			{
				mCurrentSpriteIndex.x = 0;
				++mCurrentSpriteIndex.y;
			}

			if (mCurrentSpriteIndex.y >= spriteCount.y)
			{
				mCurrentSpriteIndex.y = 0;
			}

			mElapsedUpdateTime -= animationFrameTime;
		}
	}
}

const sf::IntRect& Animation::getCurrentSprite() const
{
	return mSpriteAtlasRegion->getSpriteAreas()[mCurrentSpriteIndex.y][mCurrentSpriteIndex.x];
}

int Animation::getSpriteCount() const
{
	return mSpriteCount;
}

const sf::Time& Animation::getDurationTime() const
{
	return mDurationTime;
}

bool Animation::isPlaying() const
{
	return mIsPlaying;
}
