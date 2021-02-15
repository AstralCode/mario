#pragma once

#include "SFML/Graphics/Text.hpp"

#include "GraphicsItem.hpp"

class GraphicsTextItem final : public GraphicsItem
{
public:
	void setFont(const sf::Font& font);
	void setString(const sf::String& string);
	void setCharacterSize(const unsigned int size);

	const sf::Font* getFont() const;
	const sf::String& getString() const;
	unsigned int getCharacterSize() const;

	sf::FloatRect getBounds() const override;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Text mText;
};
