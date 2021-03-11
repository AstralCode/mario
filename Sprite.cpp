#include "Sprite.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Sprite::Sprite() noexcept :
	mHorizontalFlipped{false},
	mVerticalFlipped{false}
{

}

void Sprite::setTexture(const sf::Texture& texture) noexcept
{
	mSprite.setTexture(texture);
	mDefaultArea = mSprite.getTextureRect();

	updateArea();
}

void Sprite::setTextureArea(const IntArea& area) noexcept
{
	mSprite.setTextureRect(area.getRectangle());
	mDefaultArea = area.getRectangle();

	updateArea();
}

void Sprite::flip(const Orientations orientation) noexcept
{
	switch (orientation)
	{
	case Orientations::Horizontal:
		mHorizontalFlipped = !mHorizontalFlipped;
		break;

	case Orientations::Vertical:
		mVerticalFlipped = !mVerticalFlipped;
		break;

	default:
		break;
	}

	updateArea();
}

const sf::Texture* Sprite::getTexture() const noexcept
{
	return mSprite.getTexture();
}

IntArea Sprite::getTextureArea() const noexcept
{
	return mSprite.getTextureRect();
}

bool Sprite::isFlippedHorizontally() const noexcept
{
	return mHorizontalFlipped;
}

bool Sprite::isFlippedVertically() const noexcept
{
	return mVerticalFlipped;
}

void Sprite::updateArea() noexcept
{
	sf::IntRect area{};

	updateAreaHorizontally(area);
	updateAreaVertically(area);

	mSprite.setTextureRect(area);
}

void Sprite::updateAreaHorizontally(sf::IntRect& area) noexcept
{
	if (isFlippedHorizontally())
	{
		area.left = mDefaultArea.left + mDefaultArea.width;
		area.width = -mDefaultArea.width;
	}
	else
	{
		area.left = mDefaultArea.left;
		area.width = mDefaultArea.width;
	}
}

void Sprite::updateAreaVertically(sf::IntRect& area) noexcept
{
	if (isFlippedVertically())
	{
		area.top = mDefaultArea.top + mDefaultArea.height;
		area.height = -mDefaultArea.height;
	}
	else
	{
		area.top = mDefaultArea.top;
		area.height = mDefaultArea.height;
	}
}

FloatArea Sprite::getLocalArea() const noexcept
{
	return mSprite.getLocalBounds();
}

void Sprite::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(mSprite, states);
}
