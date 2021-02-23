#include "Tilemap.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

Tilemap::Tilemap() :
	mTilesetTexture{nullptr},
	mBackgroundColor{sf::Color::Transparent}
{
	mInformationText.setPosition(6.0f, 40.0f);
	mInformationText.setCharacterSize(12u);

	mBackgroundVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
	mTileVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
}

void Tilemap::setInformationText(const sf::Font& font, const unsigned int characterSize)
{
	mInformationText.setFont(font);
	mInformationText.setCharacterSize(characterSize);
}

void Tilemap::setTilesetTexture(const sf::Texture* tilesetTexture)
{
	mTilesetTexture = tilesetTexture;
}

void Tilemap::setTileAttributes(const std::map<unsigned int, TileAttributeFlags>& tileAttributes)
{
	mTileAttributes = tileAttributes;
}

void Tilemap::setTileIdentifier(const unsigned int identifier, const sf::Vector2u& tileIndex)
{
	mTileIdentifiers[tileIndex.y][tileIndex.x] = identifier;
}

void Tilemap::setTileIdentifiers(const std::vector<std::vector<unsigned int>>& identifiers)
{
	mTileIdentifiers = identifiers;
}

void Tilemap::setBackgroundColor(const sf::Color& color)
{
	mBackgroundColor = color;
}

void Tilemap::setGridVisible(const bool visible)
{
	mGrid.setVisible(visible);
}

void Tilemap::receiveEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (isContainsPoint({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
		{
			onMouseClick({event.mouseButton.x, event.mouseButton.y}, event.mouseButton.button);
		}
		break;
	}

	case sf::Event::MouseMoved:
	{
		if (isContainsPoint({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
		{
			onMouseMoved({event.mouseButton.x, event.mouseButton.y});
		}
		break;
	}

	default:
		break;
	}
}

void Tilemap::build(const sf::Vector2u& tileSize)
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
			const auto tileIdentifier = getTileIdentifier(tileIndex);
			setTileSprite(tileIdentifier, tileIndex);
		}
	}
}

const TilemapGrid& Tilemap::getGrid() const
{
	return mGrid;
}

unsigned int Tilemap::getTileIdentifier(const sf::Vector2u& tileIndex) const
{
	return mTileIdentifiers[tileIndex.y][tileIndex.x];
}

sf::Vector2u Tilemap::getTileIndex(const sf::Vector2f& position) const
{
	return mGrid.getTileIndex(position);
}

const sf::Vector2u& Tilemap::getTileSize() const
{
	return mGrid.getTileSize();
}

const sf::Vector2u& Tilemap::getTileCount() const
{
	return mGrid.getTileCount();
}

std::optional<TileAttributeFlags> Tilemap::getTileAttributes(const unsigned int identifier) const
{
	std::optional<TileAttributeFlags> attributes{};

	const auto tileAttributesIterator = mTileAttributes.find(identifier);
	if (tileAttributesIterator != mTileAttributes.end())
	{
		attributes = tileAttributesIterator->second;
	}

	return attributes;
}

std::optional<TileAttributeFlags> Tilemap::getTileAttributes(const sf::Vector2u& tileIndex) const
{
	const auto tileIdentifier = getTileIdentifier(tileIndex);

	return getTileAttributes(tileIdentifier);
}

sf::Vector2f Tilemap::getTilePosition(const sf::Vector2u& tileIndex) const
{
	return mGrid.getTilePosition(tileIndex);
}

sf::Vector2f Tilemap::getTileCenterPosition(const sf::Vector2u& tileIndex) const
{
	auto& tileSize = mGrid.getTileSize();

	auto position = getTilePosition(tileIndex);
	position.x += tileSize.x / 2.0f;
	position.y += tileSize.y / 2.0f;

	return position;
}

const sf::Text& Tilemap::getText() const
{
	return mInformationText;
}

bool Tilemap::isGridVisible() const
{
	return mGrid.isVisible();
}

void Tilemap::onMouseClick(const sf::Vector2i& position, const sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		const auto tileIndex = getGrid().getTileIndex(position);
		const auto tileIdentifier = getTileIdentifier(tileIndex);
		const auto tileAttributes = getTileAttributes(tileIndex);

		auto information =
			"TileIndex: " + std::to_string(tileIndex.x) + ", " + std::to_string(tileIndex.y) + "\n" +
			"TileId: " + std::to_string(tileIdentifier);

		if (tileAttributes.has_value())
		{
			information.append("\n");
			information.append("\tSolid: " + std::to_string(tileAttributes->isSet(TileAttributes::Solid)));
		}

		mInformationText.setString(information);
	}
}

void Tilemap::onMouseMoved(const sf::Vector2i&)
{

}

sf::Vector2u Tilemap::calculateTextureTilePosition(const unsigned int tileIdentifier, const sf::Vector2u& tileSize) const
{
	sf::Vector2u position{};

	if (tileIdentifier > 1u)
	{
		position.x = (tileIdentifier - 1u) % (mTilesetTexture->getSize().x / tileSize.x);
		position.y = (tileIdentifier - 1u) / (mTilesetTexture->getSize().x / tileSize.x);
	}

	return position;
}

unsigned int Tilemap::calculateTextureTileIdentifierCount(const sf::Vector2u& tileSize) const
{
	return (mTilesetTexture->getSize().x / tileSize.x) * (mTilesetTexture->getSize().y / tileSize.y);
}

sf::Vector2u Tilemap::calculateTileCount() const
{
	sf::Vector2u tileCount{};
	tileCount.x = static_cast<unsigned int>(mTileIdentifiers[0u].size());
	tileCount.y = static_cast<unsigned int>(mTileIdentifiers.size());

	return tileCount;
}

void Tilemap::setTileSprite(const unsigned int tileIdentifier, const sf::Vector2u& tileIndex)
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

	setTileIdentifier(tileIdentifier, tileIndex);
}

void Tilemap::clearTileSprite(const sf::Vector2u& tileIndex)
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	tileVerticles[0u] = {};
	tileVerticles[1u] = {};
	tileVerticles[2u] = {};
	tileVerticles[3u] = {};

	setTileIdentifier(0u, tileIndex);
}

sf::Vertex* Tilemap::getTileVerticles(const sf::Vector2u& tileIndex)
{
	const std::size_t verticlesArrayIndex = (static_cast<std::size_t>(tileIndex.y) * calculateTileCount().x + static_cast<std::size_t>(tileIndex.x)) * 4u;

	return &mTileVerticlesArray[verticlesArrayIndex];
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackgroundVerticlesArray, states);

	states.texture = mTilesetTexture;
	target.draw(mTileVerticlesArray, states);

	target.draw(mInformationText, states);
}

bool Tilemap::isContainsPoint(const sf::Vector2f& point) const
{
	return mGrid.getBounds().contains(point);
}
