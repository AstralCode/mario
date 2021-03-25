#include "TilemapView.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

TilemapView::TilemapView() noexcept :
	mTilemapTexture{nullptr},
	mBackgroundColor{sf::Color::Transparent},
	mBackgroundVerticlesArray{sf::PrimitiveType::Quads},
	mTileVerticlesArray{sf::PrimitiveType::Quads}
{
	mInformationText.setPosition(4.0f, 20.0f);
	mInformationText.setCharacterSize(12u);
}

void TilemapView::setPosition(const float x, const float y) noexcept
{
	mTransform.setPosition(x, y);
}

void TilemapView::setPosition(const FloatPoint& position) noexcept
{
	mTransform.setPosition(position.getVector());
}

void TilemapView::setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept
{
	mTilemap = std::move(tilemap);
}

void TilemapView::setTilemapTexture(const sf::Texture& texture) noexcept
{
	mTilemapTexture = &texture;
}

void TilemapView::setBackgroundColor(const sf::Color& color) noexcept
{
	mBackgroundColor = color;
}

void TilemapView::setGridVisible(const bool visible) noexcept
{
	mGrid.setVisible(visible);
}

void TilemapView::setInformationText(const sf::Font& font, const unsigned int characterSize) noexcept
{
	mInformationText.setFont(font);
	mInformationText.setCharacterSize(characterSize);
}

void TilemapView::receiveEvents(const sf::Event& event) noexcept
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (isContainsPoint({event.mouseButton.x, event.mouseButton.y}))
		{
			onMouseClick({event.mouseButton.x, event.mouseButton.y}, event.mouseButton.button);
		}
		break;
	}

	case sf::Event::MouseMoved:
	{
		if (isContainsPoint({event.mouseButton.x, event.mouseButton.y}))
		{
			onMouseMoved({event.mouseButton.x, event.mouseButton.y});
		}
		break;
	}

	default:
		break;
	}
}

void TilemapView::build() noexcept
{
	const auto rowCount = mTilemap->getRowCount();
	const auto columnCount = mTilemap->getColumnCount();

	auto& tileSize = getTileSize();

	mBackgroundVerticlesArray.clear();
	mBackgroundVerticlesArray.resize(4u);
	mBackgroundVerticlesArray[0] = sf::Vertex{sf::Vector2f{0.0f, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[1] = sf::Vertex{sf::Vector2f{tileSize.getWidth() * columnCount, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[2] = sf::Vertex{sf::Vector2f{tileSize.getWidth() * columnCount, tileSize.getHeight() * rowCount}, mBackgroundColor};
	mBackgroundVerticlesArray[3] = sf::Vertex{sf::Vector2f{0.0f, tileSize.getHeight() * rowCount}, mBackgroundColor};

	mTileVerticlesArray.clear();
	mTileVerticlesArray.resize(static_cast<std::size_t>(rowCount) * static_cast<std::size_t>(columnCount) * 4u);

	for (Tile::Index tileIndex{}; tileIndex.row < rowCount; tileIndex.row++)
	{
		for (tileIndex.column = 0; tileIndex.column < columnCount; tileIndex.column++)
		{
			const auto tileIdentifier = mTilemap->getTileIdentifier(tileIndex);
			setTileSprite(tileIdentifier, tileIndex);
		}
	}

	mGrid.setTileCount(rowCount, columnCount);
	mGrid.setTileSize(tileSize);
	mGrid.build();
}

Tile TilemapView::getTile(const IntPoint& position) const noexcept
{
	auto& tileSize = getTileSize();

	Tile::Index tileIndex{};
	tileIndex.column = position.getX() / static_cast<int>(tileSize.getWidth());
	tileIndex.row = position.getY() / static_cast<int>(tileSize.getHeight());

	return getTile(tileIndex);
}

Tile TilemapView::getTile(const FloatPoint& position) const noexcept
{
	IntPoint fixedPosition{};
	fixedPosition.setX(static_cast<int>(std::ceil(position.getX())));
	fixedPosition.setY(static_cast<int>(std::ceil(position.getY())));

	return getTile(fixedPosition);
}

Tile TilemapView::getTile(const Tile::Index& index) const noexcept
{
	Tile tile{};

	if (index.column >= 0 && index.row >= 0 && index.column < getColumnCount() && index.row < getRowCount())
	{
		tile.index = index;
		tile.identifier = mTilemap->getTileIdentifier(tile.index);
		tile.attributes = mTilemap->getTileAttributes(tile.index);
		tile.area.setPosition(getTilePosition(index));
		tile.area.setSize(getTileSize());
	}

	return tile;
}

std::vector<Tile> TilemapView::getTiles(const FloatArea& area) const noexcept
{
	std::vector<Tile> tiles{};

	const auto tileLeft = getTile(area.getTopLeft());
	const auto tileRight = getTile(area.getBottomRight());

	for (Tile::Index tileIndex{tileLeft.index.row, 0}; tileIndex.row <= tileRight.index.row; tileIndex.row++)
	{
		for (tileIndex.column = tileLeft.index.column; tileIndex.column <= tileRight.index.column; tileIndex.column++)
		{
			tiles.push_back(getTile(tileIndex));
		}
	}

	return tiles;
}

FloatPoint TilemapView::getTilePosition(const Tile::Index& index) const noexcept
{
	auto& tileSize = mTilemap->getTileSize();

	return {tileSize.getWidth() * index.column, tileSize.getHeight() * index.row};
}

FloatPoint TilemapView::getTileCenterPosition(const Tile::Index& index) const noexcept
{
	auto position = getTilePosition(index);

	return {position.getX() + getTileWidth() / 2.0f, position.getY() + getTileHeight() / 2.0f};
}

float TilemapView::getTileWidth() const noexcept
{
	return mTilemap->getTileSize().getWidth();
}

float TilemapView::getTileHeight() const noexcept
{
	return mTilemap->getTileSize().getHeight();
}

const FloatSize& TilemapView::getTileSize() const noexcept
{
	return mTilemap->getTileSize();
}

const sf::Text& TilemapView::getText() const noexcept
{
	return mInformationText;
}

FloatArea TilemapView::getArea() const noexcept
{
	FloatArea area{};
	area.setPosition(mTransform.getTransform() * sf::Vector2f{});
	area.setWidth(getColumnCount() * getTileSize().getWidth());
	area.setHeight(getRowCount() * getTileSize().getHeight());

	return area;
}

const int TilemapView::getRowCount() const noexcept
{
	return mTilemap->getRowCount();
}

const int TilemapView::getColumnCount() const noexcept
{
	return mTilemap->getColumnCount();
}

bool TilemapView::isGridVisible() const noexcept
{
	return mGrid.isVisible();
}

void TilemapView::setTileSprite(const Tile::Identifier tileIdentifier, const Tile::Index& tileIndex) noexcept
{
	sf::Vertex* tileSpriteVerticles = getTileSpriteVerticles(tileIndex);

	if (tileIdentifier > 0)
	{
		auto& tileSize = getTileSize();

		tileSpriteVerticles[0].position = sf::Vector2f{tileIndex.column * tileSize.getWidth(), tileIndex.row * tileSize.getHeight()};
		tileSpriteVerticles[1].position = sf::Vector2f{(tileIndex.column + 1) * tileSize.getWidth(), tileIndex.row * tileSize.getHeight()};
		tileSpriteVerticles[2].position = sf::Vector2f{(tileIndex.column + 1) * tileSize.getWidth(), (tileIndex.row + 1) * tileSize.getHeight()};
		tileSpriteVerticles[3].position = sf::Vector2f{tileIndex.column * tileSize.getWidth(), (tileIndex.row + 1) * tileSize.getHeight()};

		const auto textureTilePosition = calculateTextureTilePosition(tileIdentifier);

		tileSpriteVerticles[0].texCoords = sf::Vector2f{textureTilePosition.x * tileSize.getWidth(), textureTilePosition.y * tileSize.getHeight()};
		tileSpriteVerticles[1].texCoords = sf::Vector2f{(textureTilePosition.x + 1) * tileSize.getWidth(), textureTilePosition.y * tileSize.getHeight()};
		tileSpriteVerticles[2].texCoords = sf::Vector2f{(textureTilePosition.x + 1) * tileSize.getWidth(), (textureTilePosition.y + 1) * tileSize.getHeight()};
		tileSpriteVerticles[3].texCoords = sf::Vector2f{textureTilePosition.x * tileSize.getWidth(), (textureTilePosition.y + 1) * tileSize.getHeight()};
	}
	else
	{
		tileSpriteVerticles[0] = {};
		tileSpriteVerticles[1] = {};
		tileSpriteVerticles[2] = {};
		tileSpriteVerticles[3] = {};
	}

	mTilemap->setTileIdentifier(tileIndex, tileIdentifier);
}

void TilemapView::clearTileSprite(const Tile::Index& tileIndex) noexcept
{
	sf::Vertex* tileVerticles = getTileSpriteVerticles(tileIndex);
	tileVerticles[0] = {};
	tileVerticles[1] = {};
	tileVerticles[2] = {};
	tileVerticles[3] = {};

	mTilemap->setTileIdentifier(tileIndex, 0);
}

void TilemapView::onMouseClick(const IntPoint& position, const sf::Mouse::Button button) noexcept
{
	if (button == sf::Mouse::Button::Left)
	{
		const auto tile = getTile(position);

		std::string information{};
		information.append("TileIndex: [" + std::to_string(tile.index.row) + ", " + std::to_string(tile.index.column) + "]\n");
		information.append("TileId: " + std::to_string(tile.identifier) + "\n");
		information.append("TilePos: (" + std::to_string(tile.area.getLeft()) + ", " + std::to_string(tile.area.getTop()) + ")");

		if (!tile.attributes.isEmpty())
		{
			information.append("\n");
			information.append("Attributes:");
		}

		if (tile.attributes.isSet(Tile::Attributes::Collider))
		{
			information.append("\n\t\t");
			information.append("Collider");
		}

		mInformationText.setString(information);
	}
}

void TilemapView::onMouseMoved(const IntPoint&) noexcept
{

}

void TilemapView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(mTransform.getTransform());
	target.draw(mBackgroundVerticlesArray, states);
	target.draw(mGrid);

	states.texture = mTilemapTexture;
	target.draw(mTileVerticlesArray, states);
	target.draw(mInformationText);
}

sf::Vector2u TilemapView::calculateTextureTilePosition(const Tile::Identifier tileIdentifier) const noexcept
{
	sf::Vector2u position{};

	if (tileIdentifier > 1)
	{
		auto& tileSize = mTilemap->getTileSize();

		position.x = (tileIdentifier - 1) % static_cast<int>(mTilemapTexture->getSize().x / tileSize.getWidth());
		position.y = (tileIdentifier - 1) / static_cast<int>(mTilemapTexture->getSize().x / tileSize.getWidth());
	}

	return position;
}

unsigned int TilemapView::calculateTextureTileIdentifierCount() const noexcept
{
	auto& tileSize = mTilemap->getTileSize();

	return (mTilemapTexture->getSize().x / static_cast<int>(tileSize.getWidth())) * (mTilemapTexture->getSize().y / static_cast<int>(tileSize.getHeight()));
}

sf::Vertex* TilemapView::getTileSpriteVerticles(const Tile::Index& tileIndex) noexcept
{
	const auto tileColumnCount = mTilemap->getColumnCount();
	const auto verticlesArrayIndex = (tileIndex.row * tileColumnCount + tileIndex.column) * 4;

	return &mTileVerticlesArray[static_cast<std::size_t>(verticlesArrayIndex)];
}

bool TilemapView::isContainsPoint(const IntPoint& point) const noexcept
{
	return getArea().isContainsPoint(static_cast<float>(point.getX()), static_cast<float>(point.getY()));
}
