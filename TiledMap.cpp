#include "TiledMap.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

TiledMap::TiledMap() :
	mTileset{nullptr},
	mBackgroundColor{sf::Color::Transparent}
{
	mBackgroundVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
	mTileVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
}

void TiledMap::setTileset(const sf::Texture* tileset)
{
	mTileset = tileset;
}

void TiledMap::setTileIdentifierMap(const std::vector<std::vector<unsigned int>>& identifierMap)
{
	mTileIdentifierMap = identifierMap;
}

void TiledMap::setBackgroundColor(const sf::Color& color)
{
	mBackgroundColor = color;
}

void TiledMap::setGridVisible(const bool visible)
{
	mGrid.setVisible(visible);
}

void TiledMap::receiveEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (isContainsPoint({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
		{

		}
		break;
	}

	case sf::Event::MouseMoved:
	{
		if (isContainsPoint({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)}))
		{

		}
		break;
	}

	default:
		break;
	}
}

void TiledMap::build(const sf::Vector2u& tileSize)
{
	constexpr const auto quadCornerCounts = 4u;
	
	sf::Vector2u tileCount{};
	tileCount.x = mTileIdentifierMap[0u].size();
	tileCount.y = mTileIdentifierMap.size();

	mBackgroundVerticlesArray.clear();
	mBackgroundVerticlesArray.resize(quadCornerCounts);
	mBackgroundVerticlesArray[0u] = sf::Vertex{sf::Vector2f{0.0f, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[1u] = sf::Vertex{sf::Vector2f{static_cast<float>(tileSize.x * tileCount.x), 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[2u] = sf::Vertex{sf::Vector2f{static_cast<float>(tileSize.x * tileCount.x), static_cast<float>(tileSize.y * tileCount.y)}, mBackgroundColor};
	mBackgroundVerticlesArray[3u] = sf::Vertex{sf::Vector2f{0.0f, static_cast<float>(tileSize.y * tileCount.y)}, mBackgroundColor};

	mTileVerticlesArray.clear();
	mTileVerticlesArray.resize(static_cast<std::size_t>(tileCount.x) * static_cast<std::size_t>(tileCount.y) * quadCornerCounts);

	for (std::size_t y = 0u; y < tileCount.y; y++)
	{
		for (std::size_t x = 0u; x < tileCount.x; x++)
		{
			auto tileIdentifier = mTileIdentifierMap[y][x];

			if (tileIdentifier-- > 0u)
			{
				sf::Vertex* tileVerticles = &mTileVerticlesArray[(y * tileCount.x + x) * quadCornerCounts];
				tileVerticles[0u].position = sf::Vector2f{static_cast<float>(x * tileSize.x), static_cast<float>(y * tileSize.y)};
				tileVerticles[1u].position = sf::Vector2f{static_cast<float>((x + 1u) * tileSize.x), static_cast<float>(y * tileSize.y)};
				tileVerticles[2u].position = sf::Vector2f{static_cast<float>((x + 1u) * tileSize.x), static_cast<float>((y + 1u) * tileSize.y)};
				tileVerticles[3u].position = sf::Vector2f{static_cast<float>(x * tileSize.x), static_cast<float>((y + 1u) * tileSize.y)};

				const auto textureTilePosition = calculateTextureTilePosition(tileIdentifier, tileSize);
				tileVerticles[0u].texCoords = sf::Vector2f{static_cast<float>(textureTilePosition.x * tileSize.x), static_cast<float>(textureTilePosition.y * tileSize.y)};
				tileVerticles[1u].texCoords = sf::Vector2f{static_cast<float>((textureTilePosition.x + 1u) * tileSize.x), static_cast<float>(textureTilePosition.y * tileSize.y)};
				tileVerticles[2u].texCoords = sf::Vector2f{static_cast<float>((textureTilePosition.x + 1u) * tileSize.x), static_cast<float>((textureTilePosition.y + 1u) * tileSize.y)};
				tileVerticles[3u].texCoords = sf::Vector2f{static_cast<float>(textureTilePosition.x * tileSize.x), static_cast<float>((textureTilePosition.y + 1u) * tileSize.y)};
			}
		}
	}

	mGrid.setTileSize(tileSize);
	mGrid.setTileCount(tileCount);
	mGrid.build();
}

const TiledMapGrid& TiledMap::getGrid() const
{
	return mGrid;
}

const sf::Vector2u& TiledMap::getTileSize() const
{
	return mGrid.getTileSize();
}

const sf::Vector2u& TiledMap::getTileCount() const
{
	return mGrid.getTileCount();
}

bool TiledMap::isGridVisible() const
{
	return mGrid.isVisible();
}

sf::Vector2u TiledMap::calculateTextureTilePosition(const unsigned int tileIdentifier, const sf::Vector2u& tileSize) const
{
	sf::Vector2u position{};
	position.x = tileIdentifier % (mTileset->getSize().x / tileSize.x);
	position.y = tileIdentifier / (mTileset->getSize().x / tileSize.x);

	return position;
}

void TiledMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackgroundVerticlesArray, states);

	states.texture = mTileset;
	target.draw(mTileVerticlesArray, states);
}

bool TiledMap::isContainsPoint(const sf::Vector2f& point) const
{
	return mGrid.getBounds().contains(point);
}
