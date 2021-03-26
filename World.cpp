#include "World.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "ResourceContainer.hpp"
#include "Mario.hpp"
#include "Enemy.hpp"
#include "Item.hpp"

World::World(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mEntityLayer{*mRoot.addItem<GraphicsItem>()},
	mEntities{mEntityLayer}
{

}

void World::setTilemapTexture(const TextureId identifier) noexcept
{
	mTilemapView.setTilemapTexture(mResources.getTexture(identifier));
}

void World::setTilemapBackground(const sf::Color& background) noexcept
{
	mTilemapView.setBackgroundColor(background);
}

void World::setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept
{
	mTilemapView.setTilemap(std::move(tilemap));
	mTilemapView.build();
}

void World::spawnMario(const Tile::Index& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto entity = mEntities.create<Mario>(mResources, mSpritesets);
		entity->setPosition(mTilemapView.getTilePosition(tileIndex));
	}
}

void World::spawnGoomba(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);
	spawnGoomba(tile.index);
}

void World::spawnGoomba(const Tile::Index& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto entity = mEntities.create<Enemy>(mResources.getTexture(TextureId::Enemies),
											  mSpritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegions::Move),
											  mSpritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegions::Lose).getSpriteArea(0));

		entity->setPosition(mTilemapView.getTilePosition(tileIndex));
	}

}

void World::putCoin(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);
	putCoin(tile.index);
}

void World::putCoin(const Tile::Index& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto entity = mEntities.create<Item>(mResources.getTexture(TextureId::Items),
											 mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegions::Coin),
											 mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegions::CoinPickup));

		entity->setPosition(mTilemapView.getTileCenterPosition(tileIndex));
		entity->setOrigin(Entity::centerOrigin(*entity));
		entity->setAttribute(Entity::Attributes::Collectable);
		entity->setDestroyLater(true);
		entity->setPickupAnimationEndTime(sf::seconds(Constants::World::Items::PickupAnimationEnd));
		entity->setPickupHitCount(1);
	}
}

void World::putCoinBox(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);
	putCoinBox(tile.index);
}

void World::putCoinBox(const Tile::Index& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto entity = mEntities.create<Item>(mResources.getTexture(TextureId::Items),
											 mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegions::QBox),
											 mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegions::QBoxEmpty));

		entity->setPosition(mTilemapView.getTileCenterPosition(tileIndex));
		entity->setOrigin(Entity::centerOrigin(*entity));
		entity->setAttribute(Entity::Attributes::Collectable);
		entity->setDestroyLater(false);
		entity->setPickupBackPosition(mTilemapView.getTileCenterPosition(tileIndex));
		entity->setPickupHitCount(3);
	}
}

void World::removeEntity(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);

	for (auto entity : mEntities)
	{
		if (entity->isIntersects(tile.area))
		{
			entity->destroy();

			return;
		}
	}
}

void World::receiveEvents(const sf::Event& event) noexcept
{
	mTilemapView.receiveEvents(event);
	mRoot.receiveEvents(event);
}

void World::update(const sf::Time& dt) noexcept
{
	for (auto entity : mEntities)
	{
		entity->update(dt);
		mPhysicsModule.updateMovement(*entity, dt);
	}

	mCollisionModule.detectCollisions(mEntities, mTilemapView);

	mEntities.clean();
	mRoot.clean();
}

const ResourceContainer& World::getResources() noexcept
{
	return mResources;
}

const SpritesetContainer& World::getSpritesets() noexcept
{
	return mSpritesets;
}

TilemapView& World::getTilemapView() noexcept
{
	return mTilemapView;
}

const TilemapView& World::getTilemapView() const noexcept
{
	return mTilemapView;
}

Entity* World::findEntity(const IntPoint& point) const noexcept
{
	for (auto entity : mEntities)
	{
		if (entity->isContainsPoint(point))
		{
			return entity;
		}
	}

	return nullptr;
}

bool World::isTileEmpty(const IntPoint& point) const noexcept
{
	const auto tile = mTilemapView.getTile(point);
	return isTileEmpty(tile.index);
}

bool World::isTileEmpty(const Tile::Index& tileIndex) const noexcept
{
	const auto tile = mTilemapView.getTile(tileIndex);

	for (auto entity : mEntities)
	{
		if (entity->isIntersects(tile.area))
		{
			return false;
		}
	}

	return true;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mTilemapView, states);
	target.draw(mRoot, states);
}
