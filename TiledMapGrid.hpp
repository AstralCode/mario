#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class TiledMapGrid final : public sf::Drawable
{
public:
	TiledMapGrid();

	void setTileSize(const sf::Vector2f& size);
	void setTileCount(const sf::Vector2i& count);

	void setVisible(const bool visible);
	void setGridColor(const sf::Color& color);

	void build();

	const sf::Vector2f& getTileSize() const;
	const sf::Vector2i& getTileCount() const;

	sf::Vector2i getTileIndex(const sf::Vector2i& mousePosition) const;
	sf::Vector2f getTilePosition(const sf::Vector2i& index) const;

	sf::FloatRect getBounds() const;

	bool isVisible() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f mTileSize;
	sf::Vector2i mTileCount;

	sf::Color mGridColor;

	sf::VertexArray mTiledMapVertexArray;

	bool mGridVisible;
};
