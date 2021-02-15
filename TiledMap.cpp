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
			if (isGridVisible())
			{
				const auto tileIndex = mGrid.getTileIndex({event.mouseButton.x, event.mouseButton.y});
				auto tileIdentifier = mTileIdentifierMap[tileIndex.y][tileIndex.x];

				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					if (++tileIdentifier < calculateTextureTileIdentifierCount(mGrid.getTileSize()))
					{
						setTileSprite(tileIdentifier, tileIndex);
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					if (tileIdentifier > 0u)
					{
						setTileSprite(--tileIdentifier, tileIndex);
					}
					else
					{
						clearTileSprite(tileIndex);
					}
				}
			}
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
	const auto tileCount = calculateTileCount();

	mGrid.setTileSize(tileSize);
	mGrid.setTileCount(tileCount);
	mGrid.build();

	mBackgroundVerticlesArray.clear();
	mBackgroundVerticlesArray.resize(4u);
	mBackgroundVerticlesArray[0u] = sf::Vertex{sf::Vector2f{0.0f, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[1u] = sf::Vertex{sf::Vector2f{static_cast<float>(tileSize.x * tileCount.x), 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[2u] = sf::Vertex{sf::Vector2f{static_cast<float>(tileSize.x * tileCount.x), static_cast<float>(tileSize.y * tileCount.y)}, mBackgroundColor};
	mBackgroundVerticlesArray[3u] = sf::Vertex{sf::Vector2f{0.0f, static_cast<float>(tileSize.y * tileCount.y)}, mBackgroundColor};

	mTileVerticlesArray.clear();
	mTileVerticlesArray.resize(static_cast<std::size_t>(tileCount.x) * static_cast<std::size_t>(tileCount.y) * 4u);

	for (sf::Vector2u tileIndex{}; tileIndex.y < tileCount.y; tileIndex.y++)
	{
		for (tileIndex.x = 0u; tileIndex.x < tileCount.x; tileIndex.x++)
		{
			auto tileIdentifier = mTileIdentifierMap[tileIndex.y][tileIndex.x];
			setTileSprite(tileIdentifier, tileIndex);
		}
	}
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

	if (tileIdentifier > 1u)
	{
		position.x = (tileIdentifier - 1u) % (mTileset->getSize().x / tileSize.x);
		position.y = (tileIdentifier - 1u) / (mTileset->getSize().x / tileSize.x);
	}

	return position;
}

unsigned int TiledMap::calculateTextureTileIdentifierCount(const sf::Vector2u& tileSize) const
{
	return (mTileset->getSize().x / tileSize.x) * (mTileset->getSize().y / tileSize.y);
}

sf::Vector2u TiledMap::calculateTileCount() const
{
	sf::Vector2u tileCount{};
	tileCount.x = static_cast<unsigned int>(mTileIdentifierMap[0u].size());
	tileCount.y = static_cast<unsigned int>(mTileIdentifierMap.size());

	return tileCount;
}

void TiledMap::setTileSprite(const unsigned int tileIdentifier, const sf::Vector2u& tileIndex)
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	if (tileIdentifier > 0u)
	{
		auto& tileSize = mGrid.getTileSize();

		tileVerticles[0u].position = sf::Vector2f{static_cast<float>(tileIndex.x * tileSize.x), static_cast<float>(tileIndex.y * tileSize.y)};
		tileVerticles[1u].position = sf::Vector2f{static_cast<float>((tileIndex.x + 1u) * tileSize.x), static_cast<float>(tileIndex.y * tileSize.y)};
		tileVerticles[2u].position = sf::Vector2f{static_cast<float>((tileIndex.x + 1u) * tileSize.x), static_cast<float>((tileIndex.y + 1u) * tileSize.y)};
		tileVerticles[3u].position = sf::Vector2f{static_cast<float>(tileIndex.x * tileSize.x), static_cast<float>((tileIndex.y + 1u) * tileSize.y)};

		const auto textureTilePosition = calculateTextureTilePosition(tileIdentifier, tileSize);

		tileVerticles[0u].texCoords = sf::Vector2f{static_cast<float>(textureTilePosition.x * tileSize.x), static_cast<float>(textureTilePosition.y * tileSize.y)};
		tileVerticles[1u].texCoords = sf::Vector2f{static_cast<float>((textureTilePosition.x + 1u) * tileSize.x), static_cast<float>(textureTilePosition.y * tileSize.y)};
		tileVerticles[2u].texCoords = sf::Vector2f{static_cast<float>((textureTilePosition.x + 1u) * tileSize.x), static_cast<float>((textureTilePosition.y + 1u) * tileSize.y)};
		tileVerticles[3u].texCoords = sf::Vector2f{static_cast<float>(textureTilePosition.x * tileSize.x), static_cast<float>((textureTilePosition.y + 1u) * tileSize.y)};
	}
	else
	{
		tileVerticles[0u] = {};
		tileVerticles[1u] = {};
		tileVerticles[2u] = {};
		tileVerticles[3u] = {};
	}

	mTileIdentifierMap[tileIndex.y][tileIndex.x] = tileIdentifier;
}

void TiledMap::clearTileSprite(const sf::Vector2u& tileIndex)
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	tileVerticles[0u] = {};
	tileVerticles[1u] = {};
	tileVerticles[2u] = {};
	tileVerticles[3u] = {};

	mTileIdentifierMap[tileIndex.y][tileIndex.x] = 0u;
}

sf::Vertex* TiledMap::getTileVerticles(const sf::Vector2u& tileIndex)
{
	const std::size_t verticlesArrayIndex = (static_cast<std::size_t>(tileIndex.y) * calculateTileCount().x + static_cast<std::size_t>(tileIndex.x)) * 4u;

	return &mTileVerticlesArray[verticlesArrayIndex];
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
