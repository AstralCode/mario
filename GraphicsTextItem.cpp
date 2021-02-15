#include "GraphicsTextItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void GraphicsTextItem::setFont(const sf::Font& font)
{
	mText.setFont(font);
}

void GraphicsTextItem::setString(const sf::String& string)
{
	mText.setString(string);
}

void GraphicsTextItem::setCharacterSize(const unsigned int size)
{
	mText.setCharacterSize(size);
}

const sf::String& GraphicsTextItem::getString() const
{
	return mText.getString();
}

const sf::Font* GraphicsTextItem::getFont() const
{
	return mText.getFont();
}

unsigned int GraphicsTextItem::getCharacterSize() const
{
	return mText.getCharacterSize();
}

sf::FloatRect GraphicsTextItem::getBounds() const
{
	return getGlobalTransform().transformRect(mText.getLocalBounds());
}

void GraphicsTextItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}
