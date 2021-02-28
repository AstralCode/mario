#include "Text.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void Text::setFont(const sf::Font& font) noexcept
{
	mText.setFont(font);
}

void Text::setString(const sf::String& string) noexcept
{
	mText.setString(string);
}

void Text::setCharacterSize(const unsigned int size) noexcept
{
	mText.setCharacterSize(size);
}

const sf::String& Text::getString() const noexcept
{
	return mText.getString();
}

const sf::Font* Text::getFont() const noexcept
{
	return mText.getFont();
}

unsigned int Text::getCharacterSize() const noexcept
{
	return mText.getCharacterSize();
}

FloatArea Text::getArea() const noexcept
{
	return getGlobalTransform().transformRect(mText.getLocalBounds());
}

void Text::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(mText, states);
}
