#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class TilemapGrid final : public sf::Drawable
{
public:
	TilemapGrid();

	void setTileSize(const sf::Vector2u& size);
	void setTileCount(const sf::Vector2u& count);

	void setVisible(const bool visible);
	void setGridColor(const sf::Color& color);

	void build();

	const sf::Vector2u& getTileSize() const;
	const sf::Vector2u& getTileCount() const;

	sf::Vector2u getTileIndex(const sf::Vector2f& position) const;
	sf::Vector2u getTileIndex(const sf::Vector2i& mousePosition) const;
	sf::Vector2f getTilePosition(const sf::Vector2u& index) const;

	sf::FloatRect getBounds() const;

	bool isVisible() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2u mTileSize;
	sf::Vector2u mTileCount;

	sf::Color mGridColor;

	sf::VertexArray mTilemapVertexArray;

	bool mGridVisible;
};
