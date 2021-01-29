#include "Animation.hpp"

#include "SpriteAtlasRegion.hpp"

Animation::Animation(SpriteAtlasRegion& spriteAtlasRegion) :
	mSpriteAtlasRegion{spriteAtlasRegion},
	mIsPlaying{false}
{

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
	mCurrentFrameIndex = sf::Vector2i{};
	mCurrentFrame = sf::IntRect{};
	mIsPlaying = false;

	updateCurrentFrame(mCurrentFrameIndex);
}

void Animation::update(const sf::Time& frameTime)
{
	if (isPlaying())
	{
		const auto animationFrameTime = mDurationTime / static_cast<float>(getFrameCount());

		mElapsedUpdateTime += frameTime;

		while (mElapsedUpdateTime > animationFrameTime)
		{
			++mCurrentFrameIndex.x;

			if (mCurrentFrameIndex.x >= mFrameCount.x)
			{
				mCurrentFrameIndex.x = 0;
				++mCurrentFrameIndex.y;
			}

			if (mCurrentFrameIndex.y >= mFrameCount.y)
			{
				mCurrentFrameIndex.y = 0;
			}

			updateCurrentFrame(mCurrentFrameIndex);

			mElapsedUpdateTime -= animationFrameTime;
		}
	}
}

const sf::IntRect& Animation::getCurrentFrame() const
{
	return mCurrentFrame;
}

int Animation::getFrameCount() const
{
	return mFrameCount.x + mFrameCount.y;
}

const sf::Time& Animation::getDurationTime() const
{
	return mDurationTime;
}

bool Animation::isPlaying() const
{
	return mIsPlaying;
}

void Animation::updateCurrentFrame(const sf::Vector2i& currentFrameIndex)
{
	mCurrentFrame.left = currentFrameIndex.x * mFrameSize.width + (mFrameOffset.x * mFrameSize.width);
	mCurrentFrame.top = currentFrameIndex.y * mFrameSize.height + (mFrameOffset.y * mFrameSize.height);
	mCurrentFrame.width = mFrameSize.width;
	mCurrentFrame.height = mFrameSize.height;
}
