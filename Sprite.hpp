#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include "GraphicsItem.hpp"

class Sprite final : public GraphicsItem
{
public:
	enum class Orientations
	{
		Horizontal,
		Vertical
	};

	Sprite() noexcept;

	void setTexture(const sf::Texture& texture) noexcept;
	void setTextureArea(const IntArea& area) noexcept;

	void flip(const Orientations orientation) noexcept;

	const sf::Texture* getTexture() const noexcept;
	IntArea getTextureArea() const noexcept;

	bool isFlippedHorizontally() const noexcept;
	bool isFlippedVertically() const noexcept;

	FloatArea getLocalArea() const noexcept override;

private:
	void updateArea() noexcept;
	void updateAreaHorizontally(sf::IntRect& area) noexcept;
	void updateAreaVertically(sf::IntRect& area) noexcept;

	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

	sf::Sprite mSprite;
	sf::IntRect mDefaultArea;

	bool mHorizontalFlipped;
	bool mVerticalFlipped;
};
