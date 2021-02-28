#include "TilemapView.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Area.hpp"

TilemapView::TilemapView() noexcept :
	mTilesetTexture{nullptr},
	mBackgroundColor{sf::Color::Transparent}
{
	mInformationText.setPosition(6.0f, 40.0f);
	mInformationText.setCharacterSize(12u);

	mBackgroundVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
	mTileVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
}

void TilemapView::setInformationText(const sf::Font& font, const unsigned int characterSize) noexcept
{
	mInformationText.setFont(font);
	mInformationText.setCharacterSize(characterSize);
}

void TilemapView::setTilesetTexture(const sf::Texture* tilesetTexture) noexcept
{
	mTilesetTexture = tilesetTexture;
}

void TilemapView::setTileAttributes(const std::map<TileIdentifier, TileAttributeFlags>& tileAttributes) noexcept
{
	mTileAttributes = tileAttributes;
}

void TilemapView::setTileIdentifier(const TileIdentifier identifier, const TileIndex& index) noexcept
{
	mTileIdentifiers[index.column][index.row] = identifier;
}

void TilemapView::setTileIdentifiers(const std::vector<std::vector<TileIdentifier>>& identifiers) noexcept
{
	mTileIdentifiers = identifiers;
}

void TilemapView::setBackgroundColor(const sf::Color& color) noexcept
{
	mBackgroundColor = color;
}

void TilemapView::setGridVisible(const bool visible) noexcept
{
	mGrid.setVisible(visible);
}

void TilemapView::receiveEvents(const sf::Event& event) noexcept
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

void TilemapView::build(const FloatSize& tileSize) noexcept
{
	const auto tileRowCount = calculateTileRowCount();
	const auto tileColumnCount = calculateTileColumnCount();

	mGrid.setTileSize(tileSize);
	mGrid.setTileCount(tileRowCount, tileColumnCount);
	mGrid.build();

	mBackgroundVerticlesArray.clear();
	mBackgroundVerticlesArray.resize(4u);
	mBackgroundVerticlesArray[0u] = sf::Vertex{sf::Vector2f{0.0f, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[1u] = sf::Vertex{sf::Vector2f{tileSize.getWidth() * tileRowCount, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[2u] = sf::Vertex{sf::Vector2f{tileSize.getWidth() * tileRowCount, tileSize.getHeight() * tileColumnCount}, mBackgroundColor};
	mBackgroundVerticlesArray[3u] = sf::Vertex{sf::Vector2f{0.0f, tileSize.getHeight() * tileColumnCount}, mBackgroundColor};

	mTileVerticlesArray.clear();
	mTileVerticlesArray.resize(static_cast<std::size_t>(tileRowCount * tileColumnCount * 4u));

	for (TileIndex tileIndex{}; tileIndex.column < tileColumnCount; tileIndex.column++)
	{
		for (tileIndex.row = 0u; tileIndex.row < tileRowCount; tileIndex.row++)
		{
			const auto tileIdentifier = getTileIdentifier(tileIndex);
			setTileSprite(tileIdentifier, tileIndex);
		}
	}
}

const TilemapGrid& TilemapView::getGrid() const noexcept
{
	return mGrid;
}

TileIdentifier TilemapView::getTileIdentifier(const TileIndex& index) const noexcept
{
	return mTileIdentifiers[index.column][index.row];
}

TileIndex TilemapView::getTileIndex(const IntPoint& position) const noexcept
{
	return mGrid.getTileIndex(position);
}

TileIndex TilemapView::getTileIndex(const FloatPoint& position) const noexcept
{
	return mGrid.getTileIndex(position);
}

const FloatSize& TilemapView::getTileSize() const noexcept
{
	return mGrid.getTileSize();
}

const int TilemapView::getTileRowCount() const noexcept
{
	return mGrid.getTileRowCount();
}

const int TilemapView::getTileColumnCount() const noexcept
{
	return mGrid.getTileColumnCount();
}

std::optional<TileAttributeFlags> TilemapView::getTileAttributes(const TileIdentifier identifier) const noexcept
{
	std::optional<TileAttributeFlags> attributes{};

	const auto tileAttributesIterator = mTileAttributes.find(identifier);
	if (tileAttributesIterator != mTileAttributes.end())
	{
		attributes = tileAttributesIterator->second;
	}

	return attributes;
}

std::optional<TileAttributeFlags> TilemapView::getTileAttributes(const TileIndex& index) const noexcept
{
	return getTileAttributes(getTileIdentifier(index));
}

FloatPoint TilemapView::getTilePosition(const TileIndex& index) const noexcept
{
	return mGrid.getTilePosition(index);
}

FloatArea TilemapView::getTileArea(const TileIndex& index) const noexcept
{
	return mGrid.getTileArea(index);
}

const sf::Text& TilemapView::getText() const noexcept
{
	return mInformationText;
}

bool TilemapView::isGridVisible() const noexcept
{
	return mGrid.isVisible();
}

void TilemapView::onMouseClick(const IntPoint& position, const sf::Mouse::Button button) noexcept
{
	if (button == sf::Mouse::Button::Left)
	{
		const auto tileIndex = getTileIndex(position);
		const auto tileIdentifier = getTileIdentifier(tileIndex);
		const auto tileAttributes = getTileAttributes(tileIndex);

		auto information =
			"TileIndex: " + std::to_string(tileIndex.row) + ", " + std::to_string(tileIndex.column) + "\n" +
			"TileId: " + std::to_string(tileIdentifier);

		if (tileAttributes.has_value())
		{
			information.append("\n");
			information.append("\tSolid: " + std::to_string(tileAttributes->isSet(TileAttributes::Collider)));
		}

		mInformationText.setString(information);
	}
}

void TilemapView::onMouseMoved(const IntPoint&) noexcept
{

}

sf::Vector2u TilemapView::calculateTextureTilePosition(const TileIdentifier tileIdentifier, const FloatSize& tileSize) const noexcept
{
	sf::Vector2u position{};

	if (tileIdentifier > 1u)
	{
		position.x = (tileIdentifier - 1u) % static_cast<int>(mTilesetTexture->getSize().x / tileSize.getWidth());
		position.y = (tileIdentifier - 1u) / static_cast<int>(mTilesetTexture->getSize().x / tileSize.getWidth());
	}

	return position;
}

unsigned int TilemapView::calculateTextureTileIdentifierCount(const FloatSize& tileSize) const noexcept
{
	return (mTilesetTexture->getSize().x / static_cast<unsigned int>(tileSize.getWidth())) * (mTilesetTexture->getSize().y / static_cast<unsigned int>(tileSize.getHeight()));
}

int TilemapView::calculateTileRowCount() const noexcept
{
	return static_cast<int>(mTileIdentifiers[0u].size());
}

int TilemapView::calculateTileColumnCount() const noexcept
{
	return static_cast<int>(mTileIdentifiers.size());
}

void TilemapView::setTileSprite(const TileIdentifier tileIdentifier, const TileIndex& tileIndex) noexcept
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	if (tileIdentifier > 0u)
	{
		auto& tileSize = mGrid.getTileSize();

		tileVerticles[0u].position = sf::Vector2f{tileIndex.row * tileSize.getWidth(), tileIndex.column * tileSize.getHeight()};
		tileVerticles[1u].position = sf::Vector2f{(tileIndex.row + 1u) * tileSize.getWidth(), tileIndex.column * tileSize.getHeight()};
		tileVerticles[2u].position = sf::Vector2f{(tileIndex.row + 1u) * tileSize.getWidth(), (tileIndex.column + 1u) * tileSize.getHeight()};
		tileVerticles[3u].position = sf::Vector2f{tileIndex.row * tileSize.getWidth(), (tileIndex.column + 1u) * tileSize.getHeight()};

		const auto textureTilePosition = calculateTextureTilePosition(tileIdentifier, tileSize);

		tileVerticles[0u].texCoords = sf::Vector2f{textureTilePosition.x * tileSize.getWidth(), textureTilePosition.y * tileSize.getHeight()};
		tileVerticles[1u].texCoords = sf::Vector2f{(textureTilePosition.x + 1u) * tileSize.getWidth(), textureTilePosition.y * tileSize.getHeight()};
		tileVerticles[2u].texCoords = sf::Vector2f{(textureTilePosition.x + 1u) * tileSize.getWidth(), (textureTilePosition.y + 1u) * tileSize.getHeight()};
		tileVerticles[3u].texCoords = sf::Vector2f{textureTilePosition.x * tileSize.getWidth(), (textureTilePosition.y + 1u) * tileSize.getHeight()};
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

void TilemapView::clearTileSprite(const TileIndex& tileIndex) noexcept
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	tileVerticles[0u] = {};
	tileVerticles[1u] = {};
	tileVerticles[2u] = {};
	tileVerticles[3u] = {};

	setTileIdentifier(0u, tileIndex);
}

sf::Vertex* TilemapView::getTileVerticles(const TileIndex& tileIndex) noexcept
{
	const auto tileRowCount = calculateTileRowCount();
	const auto verticlesArrayIndex = (tileIndex.column * tileRowCount + tileIndex.row) * 4u;

	return &mTileVerticlesArray[static_cast<std::size_t>(verticlesArrayIndex)];
}

void TilemapView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackgroundVerticlesArray, states);

	states.texture = mTilesetTexture;
	target.draw(mTileVerticlesArray, states);

	target.draw(mInformationText, states);
}

bool TilemapView::isContainsPoint(const FloatPoint& point) const noexcept
{
	return mGrid.getArea().isContainsPoint(point);
}