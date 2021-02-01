#include "GraphicsSpriteItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsSpriteItem::GraphicsSpriteItem() :
	mHorizontalFlipped{false},
	mVerticalFlipped{false}
{

}

void GraphicsSpriteItem::setTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
	mDefaultArea = mSprite.getTextureRect();

	updateArea();
}

void GraphicsSpriteItem::setTextureArea(const sf::IntRect& area)
{
	mSprite.setTextureRect(area);
	mDefaultArea = area;

	updateArea();
}

void GraphicsSpriteItem::flip(const Orientations orientation)
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

const sf::Texture* GraphicsSpriteItem::getTexture() const
{
	return mSprite.getTexture();
}

const sf::IntRect& GraphicsSpriteItem::getTextureArea() const
{
	return mSprite.getTextureRect();
}

sf::FloatRect GraphicsSpriteItem::getBounds() const
{
	return getGlobalTransform().transformRect(mSprite.getLocalBounds());
}

bool GraphicsSpriteItem::isFlippedHorizontally() const
{
	return mHorizontalFlipped;
}

bool GraphicsSpriteItem::isFlippedVertically() const
{
	return mVerticalFlipped;
}

void GraphicsSpriteItem::updateArea()
{
	sf::IntRect area{};

	updateAreaHorizontally(area);
	updateAreaVertically(area);

	mSprite.setTextureRect(area);
}

void GraphicsSpriteItem::updateAreaHorizontally(sf::IntRect& area)
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

void GraphicsSpriteItem::updateAreaVertically(sf::IntRect& area)
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

void GraphicsSpriteItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
