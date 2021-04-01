#include "World.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "Mario.hpp"
#include "Goomba.hpp"
#include "Coin.hpp"

World::World(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mHeroLayer{*mSceneRoot.addItem<GraphicsItem>()},
	mEnemyLayer{*mSceneRoot.addItem<GraphicsItem>()},
	mItemLayer{*mSceneRoot.addItem<GraphicsItem>()},
	mHeroes{mHeroLayer, *this},
	mEnemies{mEnemyLayer, *this},
	mItems{mItemLayer, *this}
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

void World::spawnMario(const TileIndex& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto mario = mHeroes.create<Mario>();
		mario->setPosition(mTilemapView.getTilePosition(tileIndex));
	}
}

void World::spawnGoomba(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);
	spawnGoomba(tile.getIndex());
}

void World::spawnGoomba(const TileIndex& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto goomba = mEnemies.create<Goomba>();
		goomba->setPosition(mTilemapView.getTilePosition(tileIndex));
	}
}

void World::putCoin(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);
	putCoin(tile.getIndex());
}

void World::putCoin(const TileIndex& tileIndex) noexcept
{
	if (isTileEmpty(tileIndex))
	{
		auto coin = mItems.create<Coin>();
		coin->setPosition(mTilemapView.getTileCenterPosition(tileIndex));
	}
}

void World::putCoinBox(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);
	putCoinBox(tile.getIndex());
}

void World::putCoinBox(const TileIndex&) noexcept
{

}

void World::removeEntity(const IntPoint& point) noexcept
{
	const auto tile = mTilemapView.getTile(point);

	for (auto entity : mHeroes)
	{
		if (entity->isIntersects(tile.getArea()))
		{
			entity->destroy();
			return;
		}
	}
}

Entity* World::findEntity(const IntPoint& point) const noexcept
{
	Entity* entity = findEntity(mHeroes, point);
	if (entity != nullptr)
	{
		return entity;
	}

	entity = findEntity(mEnemies, point);
	if (entity != nullptr)
	{
		return entity;
	}

	entity = findEntity(mItems, point);
	if (entity != nullptr)
	{
		return entity;
	}

	return entity;
}

void World::receiveEvents(const sf::Event& event) noexcept
{
	mTilemapView.receiveEvents(event);
	mSceneRoot.receiveEvents(event);
}

void World::update(const sf::Time& dt) noexcept
{
	updateEntities(dt);

	detectTileCollisions();
	detectEntityCollisions();

	cleanEntities();
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

bool World::isTileEmpty(const IntPoint& point) const noexcept
{
	const auto tile = mTilemapView.getTile(point);
	return isTileEmpty(tile.getIndex());
}

bool World::isTileEmpty(const TileIndex& tileIndex) const noexcept
{
	return isTileEmpty(mHeroes, tileIndex) &&
		   isTileEmpty(mEnemies, tileIndex) &&
		   isTileEmpty(mItems, tileIndex);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mTilemapView, states);
	target.draw(mSceneRoot, states);
}

void World::updateEntities(const sf::Time& dt) noexcept
{
	updateEntities(mHeroes, dt);
	updateEntities(mEnemies, dt);
	updateEntities(mItems, dt);
}

void World::updateEntities(EntityContainer& entities, const sf::Time& dt) noexcept
{
	for (auto entity : entities)
	{
		entity->update(dt);
		mPhysicsModule.updateMovement(*entity, dt);
	}
}

void World::detectTileCollisions() noexcept
{
	mCollisionModule.detectTileCollisions(mHeroes, mTilemapView);
	mCollisionModule.detectTileCollisions(mEnemies, mTilemapView);
}

void World::detectEntityCollisions() noexcept
{
	mCollisionModule.detectEntityCollisions(mHeroes, mEnemies);

	mCollisionModule.detectEntityCollisions(mEnemies, mEnemies);
	mCollisionModule.detectEntityCollisions(mEnemies, mHeroes);

	mCollisionModule.detectEntityCollisions(mHeroes, mItems);
	mCollisionModule.detectEntityCollisions(mEnemies, mItems);

	mCollisionModule.detectEntityCollisions(mItems, mHeroes);
	mCollisionModule.detectEntityCollisions(mItems, mEnemies);
}

void World::cleanEntities() noexcept
{
	mHeroes.clean();
	mEnemies.clean();
	mItems.clean();

	mSceneRoot.clean();
}

Entity* World::findEntity(const EntityContainer& entities, const IntPoint& point) const noexcept
{
	for (auto entity : entities)
	{
		if (entity->isContainsPoint(point))
		{
			return entity;
		}
	}

	return nullptr;
}

bool World::isTileEmpty(const EntityContainer& entities, const TileIndex& tileIndex) const noexcept
{
	const auto tile = mTilemapView.getTile(tileIndex);

	for (auto entity : entities)
	{
		if (entity->isIntersects(tile.getArea()))
		{
			return false;
		}
	}

	return true;
}
