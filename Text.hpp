#pragma once

#include "SFML/Graphics/Text.hpp"

#include "GraphicsItem.hpp"

class Text final : public GraphicsItem
{
public:
	void setFont(const sf::Font& font) noexcept;
	void setString(const sf::String& string) noexcept;
	void setCharacterSize(const unsigned int size) noexcept;

	const sf::Font* getFont() const noexcept;
	const sf::String& getString() const noexcept;
	unsigned int getCharacterSize() const noexcept;

	FloatArea getLocalArea() const noexcept override;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

	sf::Text mText;
};
