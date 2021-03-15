#include "TilemapView.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Area.hpp"

TilemapView::TilemapView() noexcept :
	mTilemapTexture{nullptr},
	mBackgroundColor{sf::Color::Transparent}
{
	mInformationText.setPosition(6.0f, 40.0f);
	mInformationText.setCharacterSize(12u);

	mBackgroundVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
	mTileVerticlesArray.setPrimitiveType(sf::PrimitiveType::Quads);
}

void TilemapView::setPosition(const float x, const float y) noexcept
{
	mTransform.setPosition(x, y);
}

void TilemapView::setPosition(const FloatPoint& position) noexcept
{
	mTransform.setPosition(position.getVector());
}

void TilemapView::setMargins(const float left, const float top, const float right, const float bottom) noexcept
{
	mMargins.set(left, top, right, bottom);
}

void TilemapView::setMargins(const FloatMargins& margins) noexcept
{
	mMargins = margins;
}

void TilemapView::setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept
{
	mTilemap = std::move(tilemap);
}

void TilemapView::setTilemapTexture(const sf::Texture& texture) noexcept
{
	mTilemapTexture = &texture;
}

void TilemapView::setInformationText(const sf::Font& font, const unsigned int characterSize) noexcept
{
	mInformationText.setFont(font);
	mInformationText.setCharacterSize(characterSize);
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
	const auto rowCount = calculateTileRowCount();
	const auto columnCount = calculateTileColumnCount();

	mGrid.setTileSize(tileSize);
	mGrid.setTileCount(rowCount, columnCount);
	mGrid.build();

	mBackgroundVerticlesArray.clear();
	mBackgroundVerticlesArray.resize(4u);
	mBackgroundVerticlesArray[0u] = sf::Vertex{sf::Vector2f{0.0f, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[1u] = sf::Vertex{sf::Vector2f{tileSize.getWidth() * columnCount, 0.0f}, mBackgroundColor};
	mBackgroundVerticlesArray[2u] = sf::Vertex{sf::Vector2f{tileSize.getWidth() * columnCount, tileSize.getHeight() * rowCount}, mBackgroundColor};
	mBackgroundVerticlesArray[3u] = sf::Vertex{sf::Vector2f{0.0f, tileSize.getHeight() * rowCount}, mBackgroundColor};

	mTileVerticlesArray.clear();
	mTileVerticlesArray.resize(static_cast<std::size_t>(rowCount) * static_cast<std::size_t>(columnCount) * 4u);

	for (TileIndex tileIndex{}; tileIndex.row < rowCount; tileIndex.row++)
	{
		for (tileIndex.column = 0; tileIndex.column < columnCount; tileIndex.column++)
		{
			const auto tileIdentifier = getIdentifier(tileIndex);
			setTileSprite(tileIdentifier, tileIndex);
		}
	}
}

TileIdentifier TilemapView::getIdentifier(const TileIndex& index) const noexcept
{
	return mTilemap->getIdentifier(index);
}

std::optional<TileAttributeFlags> TilemapView::getAttributes(const TileIdentifier identifier) const noexcept
{
	return mTilemap->getAttributes(identifier);
}

std::optional<TileAttributeFlags> TilemapView::getAttributes(const TileIndex& index) const noexcept
{
	return mTilemap->getAttributes(index);
}

TileIndex TilemapView::getTileIndex(const IntPoint& position) const noexcept
{
	return mGrid.getTileIndex(position);
}

TileIndex TilemapView::getTileIndex(const FloatPoint& position) const noexcept
{
	return mGrid.getTileIndex(position);
}

std::vector<TileIndex> TilemapView::getOverlapTileIndexes(const FloatArea& area) const noexcept
{
	std::vector<TileIndex> tileIndexes{};

	const auto tileLeftTop = getTileIndex(area.getTopLeft());
	const auto tileBottomRight = getTileIndex(area.getBottomRight());

	for (TileIndex tileIndex{tileLeftTop.row, 0.0f}; tileIndex.row <= tileBottomRight.row; tileIndex.row++)
	{
		for (tileIndex.column = tileLeftTop.column; tileIndex.column <= tileBottomRight.column; tileIndex.column++)
		{
			tileIndexes.push_back(tileIndex);
		}
	}

	return tileIndexes;
}

const FloatSize& TilemapView::getTileSize() const noexcept
{
	return mGrid.getTileSize();
}

const int TilemapView::getRowCount() const noexcept
{
	return mGrid.getRowCount();
}

const int TilemapView::getColumnCount() const noexcept
{
	return mGrid.getColumnCount();
}

FloatPoint TilemapView::getTilePosition(const TileIndex& index) const noexcept
{
	return mGrid.getTilePosition(index);
}

FloatArea TilemapView::getTileArea(const TileIndex& index) const noexcept
{
	return mGrid.getTileArea(index);
}

FloatArea TilemapView::getTileArea(const FloatPoint& position) const noexcept
{
	return mGrid.getTileArea(position);
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
		const auto tileIdentifier = getIdentifier(tileIndex);
		const auto tileAttributes = getAttributes(tileIndex);

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
		position.x = (tileIdentifier - 1u) % static_cast<int>(mTilemapTexture->getSize().x / tileSize.getWidth());
		position.y = (tileIdentifier - 1u) / static_cast<int>(mTilemapTexture->getSize().x / tileSize.getWidth());
	}

	return position;
}

unsigned int TilemapView::calculateTextureTileIdentifierCount(const FloatSize& tileSize) const noexcept
{
	return (mTilemapTexture->getSize().x / static_cast<unsigned int>(tileSize.getWidth())) * (mTilemapTexture->getSize().y / static_cast<unsigned int>(tileSize.getHeight()));
}

int TilemapView::calculateTileRowCount() const noexcept
{
	return mTilemap->getRowCount();
}

int TilemapView::calculateTileColumnCount() const noexcept
{
	return mTilemap->getColumnCount();
}

void TilemapView::setTileSprite(const TileIdentifier tileIdentifier, const TileIndex& tileIndex) noexcept
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	if (tileIdentifier > 0u)
	{
		auto& tileSize = mGrid.getTileSize();

		tileVerticles[0u].position = sf::Vector2f{tileIndex.column * tileSize.getWidth(), tileIndex.row * tileSize.getHeight()};
		tileVerticles[1u].position = sf::Vector2f{(tileIndex.column + 1u) * tileSize.getWidth(), tileIndex.row * tileSize.getHeight()};
		tileVerticles[2u].position = sf::Vector2f{(tileIndex.column + 1u) * tileSize.getWidth(), (tileIndex.row + 1u) * tileSize.getHeight()};
		tileVerticles[3u].position = sf::Vector2f{tileIndex.column * tileSize.getWidth(), (tileIndex.row + 1u) * tileSize.getHeight()};

		tileVerticles[0u].position.x += mMargins.getRight() + mMargins.getLeft();
		tileVerticles[0u].position.y += mMargins.getBottom() + mMargins.getTop();

		tileVerticles[1u].position.x += mMargins.getRight() + mMargins.getLeft();
		tileVerticles[1u].position.y += mMargins.getBottom() + mMargins.getTop();

		tileVerticles[2u].position.x += mMargins.getRight() + mMargins.getLeft();
		tileVerticles[2u].position.y += mMargins.getBottom() + mMargins.getTop();

		tileVerticles[3u].position.x += mMargins.getRight() + mMargins.getLeft();
		tileVerticles[3u].position.y += mMargins.getBottom() + mMargins.getTop();

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

	mTilemap->setIdentifier(tileIndex, tileIdentifier);
}

void TilemapView::clearTileSprite(const TileIndex& tileIndex) noexcept
{
	sf::Vertex* tileVerticles = getTileVerticles(tileIndex);

	tileVerticles[0u] = {};
	tileVerticles[1u] = {};
	tileVerticles[2u] = {};
	tileVerticles[3u] = {};

	mTilemap->setIdentifier(tileIndex, 0);
}

sf::Vertex* TilemapView::getTileVerticles(const TileIndex& tileIndex) noexcept
{
	const auto tileColumnCount = calculateTileColumnCount();
	const auto verticlesArrayIndex = (tileIndex.row * tileColumnCount + tileIndex.column) * 4u;

	return &mTileVerticlesArray[static_cast<std::size_t>(verticlesArrayIndex)];
}

void TilemapView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(mTransform.getTransform());

	target.draw(mBackgroundVerticlesArray, states);

	states.texture = mTilemapTexture;
	target.draw(mTileVerticlesArray, states);

	target.draw(mInformationText);
	target.draw(mGrid);
}

bool TilemapView::isContainsPoint(const FloatPoint& point) const noexcept
{
	return mGrid.getArea().isContainsPoint(point);
}
