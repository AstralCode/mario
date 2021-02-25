#include "GraphicsTextItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void GraphicsTextItem::setFont(const sf::Font& font) noexcept
{
	mText.setFont(font);
}

void GraphicsTextItem::setString(const sf::String& string) noexcept
{
	mText.setString(string);
}

void GraphicsTextItem::setCharacterSize(const unsigned int size) noexcept
{
	mText.setCharacterSize(size);
}

const sf::String& GraphicsTextItem::getString() const noexcept
{
	return mText.getString();
}

const sf::Font* GraphicsTextItem::getFont() const noexcept
{
	return mText.getFont();
}

unsigned int GraphicsTextItem::getCharacterSize() const noexcept
{
	return mText.getCharacterSize();
}

FloatArea GraphicsTextItem::getArea() const noexcept
{
	return getGlobalTransform().transformRect(mText.getLocalBounds());
}

void GraphicsTextItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(mText, states);
}
