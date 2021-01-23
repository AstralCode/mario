#include "GraphicsSpriteItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void GraphicsSpriteItem::setTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

void GraphicsSpriteItem::setTextureArea(const sf::IntRect& area)
{
	mSprite.setTextureRect(area);
}

const sf::Texture* GraphicsSpriteItem::getTexture() const
{
	return mSprite.getTexture();
}

const sf::IntRect GraphicsSpriteItem::getTextureArea() const
{
	return mSprite.getTextureRect();
}

void GraphicsSpriteItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
