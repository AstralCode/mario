#pragma once

#include "TilemapView.hpp"
#include "EntityContainer.hpp"
#include "PhysicsModule.hpp"
#include "CollisionModule.hpp"
#include "ResourceIdentifiers.hpp"

class ResourceContainer;
class SpritesetContainer;

class World final : public sf::Drawable
{
public:
	World(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	void setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept;
	void setTilemapTexture(const TextureId identifier) noexcept;
	void setTilemapBackground(const sf::Color& background) noexcept;

	void spawnMario(const TileIndex& tileIndex) noexcept;

	void spawnGoomba(const IntPoint& point) noexcept;
	void spawnGoomba(const TileIndex& tileIndex) noexcept;

	void putCoin(const IntPoint& point) noexcept;
	void putCoin(const TileIndex& tileIndex) noexcept;

	void putCoinBox(const IntPoint& point) noexcept;
	void putCoinBox(const TileIndex& tileIndex) noexcept;

	void removeEntity(const IntPoint& point) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void update(const sf::Time& dt) noexcept;

	const ResourceContainer& getResources() noexcept;
	const SpritesetContainer& getSpritesets() noexcept;

	TilemapView& getTilemapView() noexcept;
	const TilemapView& getTilemapView() const noexcept;

	Entity* findEntity(const IntPoint& point) const noexcept;

	bool isTileEmpty(const IntPoint& point) const noexcept;
	bool isTileEmpty(const TileIndex& tileIndex) const noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const ResourceContainer& mResources;
	const SpritesetContainer& mSpritesets;

	GraphicsItem mRoot;
	GraphicsItem& mEntityLayer;

	TilemapView mTilemapView;
	EntityContainer mEntities;

	PhysicsModule mPhysicsModule;
	CollisionModule mCollisionModule;
};
