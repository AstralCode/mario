#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include "GraphicsItem.hpp"

class GraphicsSpriteItem final : public GraphicsItem
{
public:
	enum class Orientations
	{
		Horizontal,
		Vertical
	};

	GraphicsSpriteItem();

	void setTexture(const sf::Texture& texture);
	void setTextureArea(const sf::IntRect& area);

	void flip(const Orientations orientation);

	const sf::Texture* getTexture() const;
	const sf::IntRect& getTextureArea() const;

	sf::FloatRect getBounds() const override;

	bool isFlippedHorizontally() const;
	bool isFlippedVertically() const;

private:
	void updateArea();
	void updateAreaHorizontally(sf::IntRect& area);
	void updateAreaVertically(sf::IntRect& area);

	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mSprite;
	sf::IntRect mDefaultArea;

	bool mHorizontalFlipped;
	bool mVerticalFlipped;
};
