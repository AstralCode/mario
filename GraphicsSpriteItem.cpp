#include "GraphicsSpriteItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsSpriteItem::GraphicsSpriteItem() noexcept :
	mHorizontalFlipped{false},
	mVerticalFlipped{false}
{

}

void GraphicsSpriteItem::setTexture(const sf::Texture& texture) noexcept
{
	mSprite.setTexture(texture);
	mDefaultArea = mSprite.getTextureRect();

	updateArea();
}

void GraphicsSpriteItem::setTextureArea(const IntArea& area) noexcept
{
	mSprite.setTextureRect(area.getRectangle());
	mDefaultArea = area.getRectangle();

	updateArea();
}

void GraphicsSpriteItem::flip(const Orientations orientation) noexcept
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

const sf::Texture* GraphicsSpriteItem::getTexture() const noexcept
{
	return mSprite.getTexture();
}

const IntArea& GraphicsSpriteItem::getTextureArea() const noexcept
{
	return mSprite.getTextureRect();
}

FloatArea GraphicsSpriteItem::getArea() const noexcept
{
	return getGlobalTransform().transformRect(mSprite.getLocalBounds());
}

bool GraphicsSpriteItem::isFlippedHorizontally() const noexcept
{
	return mHorizontalFlipped;
}

bool GraphicsSpriteItem::isFlippedVertically() const noexcept
{
	return mVerticalFlipped;
}

void GraphicsSpriteItem::updateArea() noexcept
{
	sf::IntRect area{};

	updateAreaHorizontally(area);
	updateAreaVertically(area);

	mSprite.setTextureRect(area);
}

void GraphicsSpriteItem::updateAreaHorizontally(sf::IntRect& area) noexcept
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

void GraphicsSpriteItem::updateAreaVertically(sf::IntRect& area) noexcept
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

void GraphicsSpriteItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(mSprite, states);
}
