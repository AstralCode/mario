#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include "GraphicsItem.hpp"

class GraphicsSpriteItem final : public GraphicsItem
{
public:
	void setTexture(const sf::Texture& texture);
	void setTextureArea(const sf::IntRect& area);

	const sf::Texture* getTexture() const;
	const sf::IntRect getTextureArea() const;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mSprite;
};
