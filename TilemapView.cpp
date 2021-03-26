#include "TilemapView.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

TilemapView::TilemapView() noexcept :
	mTilemapTexture{nullptr},
	mBackgroundColor{sf::Color::Transparent},
	mBackgroundVerticlesArray{sf::PrimitiveType::Quads},
	mTileVerticlesArray{sf::PrimitiveType::Quads}
{

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

void TilemapView::receiveEvents(const sf::Event& event) noexcept
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (isContainsPoint({event.mouseButton.x, event.mouseButton.y}))
		{
			for (auto& onMouseClickDelegate : mOnMouseClickDelegates)
			{
				onMouseClickDelegate({event.mouseButton.x, event.mouseButton.y}, event.mouseButton.button);
			}
		}
		break;
	}

	case sf::Event::MouseMoved:
	{
		if (isContainsPoint({event.mouseButton.x, event.mouseButton.y}))
		{
			for (auto& onMouseMoveDelegate : mOnMouseMoveDelegates)
			{
				onMouseMoveDelegate({event.mouseButton.x, event.mouseButton.y});
			}
		}
		break;
	}

	default:
		break;
	}
}

void TilemapView::addOnMouseClick(OnMouseClickDelegate delegate) noexcept
{
	mOnMouseClickDelegates.push_back(std::move(delegate));
}

void TilemapView::addOnMouseMove(OnMouseMoveDelegate delegate) noexcept
{
	mOnMouseMoveDelegates.push_back(std::move(delegate));
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

	for (int row{0}; row < rowCount; row++)
	{
		for (int column{0}; column < columnCount; column++)
		{
			const auto tileIdentifier = mTilemap->getTileIdentifier({row, column});
			setTileSprite(tileIdentifier, {row, column});
		}
	}

	mGrid.setTileCount(rowCount, columnCount);
	mGrid.setTileSize(tileSize);
	mGrid.build();
}

Tile TilemapView::getTile(const IntPoint& position) const noexcept
{
	auto& tileSize = getTileSize();

	TileIndex tileIndex{};
	tileIndex.setColumn(position.getX() / static_cast<int>(tileSize.getWidth()));
	tileIndex.setRow(position.getY() / static_cast<int>(tileSize.getHeight()));

	return getTile(tileIndex);
}

Tile TilemapView::getTile(const FloatPoint& position) const noexcept
{
	IntPoint fixedPosition{};
	fixedPosition.setX(static_cast<int>(std::ceil(position.getX())));
	fixedPosition.setY(static_cast<int>(std::ceil(position.getY())));

	return getTile(fixedPosition);
}

Tile TilemapView::getTile(const TileIndex& index) const noexcept
{
	Tile tile{};

	if (index.getColumn() >= 0 && index.getRow() >= 0 &&
		index.getColumn() < getColumnCount() && index.getRow() < getRowCount())
	{
		tile.setIdentifier(mTilemap->getTileIdentifier(index));
		tile.setIndex(index);
		tile.setTraits(mTilemap->getTileTraits(index));
		tile.setArea({getTilePosition(index), getTileSize()});
	}

	return tile;
}

std::vector<Tile> TilemapView::getTiles(const FloatArea& area) const noexcept
{
	std::vector<Tile> tiles{};

	const auto tileLeft = getTile(area.getTopLeft());
	const auto tileRight = getTile(area.getBottomRight());

	for (int row{tileLeft.getIndex().getRow()}; row <= tileRight.getIndex().getRow(); row++)
	{
		for (int column{tileLeft.getIndex().getColumn()}; column <= tileRight.getIndex().getColumn(); column++)
		{
			tiles.push_back(getTile(TileIndex{row, column}));
		}
	}

	return tiles;
}

FloatPoint TilemapView::getTilePosition(const TileIndex& index) const noexcept
{
	auto& tileSize = mTilemap->getTileSize();

	return {tileSize.getWidth() * index.getColumn(), tileSize.getHeight() * index.getRow()};
}

FloatPoint TilemapView::getTileCenterPosition(const TileIndex& index) const noexcept
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

void TilemapView::setTileSprite(const Tile::Identifier tileIdentifier, const TileIndex& tileIndex) noexcept
{
	sf::Vertex* tileSpriteVerticles = getTileSpriteVerticles(tileIndex);

	if (tileIdentifier > 0)
	{
		auto& tileSize = getTileSize();

		tileSpriteVerticles[0].position = sf::Vector2f{tileIndex.getColumn() * tileSize.getWidth(), tileIndex.getRow() * tileSize.getHeight()};
		tileSpriteVerticles[1].position = sf::Vector2f{(tileIndex.getColumn() + 1) * tileSize.getWidth(), tileIndex.getRow() * tileSize.getHeight()};
		tileSpriteVerticles[2].position = sf::Vector2f{(tileIndex.getColumn() + 1) * tileSize.getWidth(), (tileIndex.getRow() + 1) * tileSize.getHeight()};
		tileSpriteVerticles[3].position = sf::Vector2f{tileIndex.getColumn() * tileSize.getWidth(), (tileIndex.getRow() + 1) * tileSize.getHeight()};

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

void TilemapView::clearTileSprite(const TileIndex& tileIndex) noexcept
{
	sf::Vertex* tileVerticles = getTileSpriteVerticles(tileIndex);
	tileVerticles[0] = {};
	tileVerticles[1] = {};
	tileVerticles[2] = {};
	tileVerticles[3] = {};

	mTilemap->setTileIdentifier(tileIndex, 0);
}

void TilemapView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(mTransform.getTransform());
	target.draw(mBackgroundVerticlesArray, states);
	target.draw(mGrid);

	states.texture = mTilemapTexture;
	target.draw(mTileVerticlesArray, states);
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

sf::Vertex* TilemapView::getTileSpriteVerticles(const TileIndex& tileIndex) noexcept
{
	const auto tileColumnCount = mTilemap->getColumnCount();
	const auto verticlesArrayIndex = (tileIndex.getRow() * tileColumnCount + tileIndex.getColumn()) * 4;

	return &mTileVerticlesArray[static_cast<std::size_t>(verticlesArrayIndex)];
}

bool TilemapView::isContainsPoint(const IntPoint& point) const noexcept
{
	return getArea().isContainsPoint(static_cast<float>(point.getX()), static_cast<float>(point.getY()));
}
