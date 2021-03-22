#pragma once

#include "TilemapView.hpp"
#include "EntityContainer.hpp"
#include "PhysicsModule.hpp"
#include "CollisionModule.hpp"
#include "Resources.hpp"

class ResourceContainer;
class SpritesetContainer;

class World final : public sf::Drawable
{
public:
	World(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	void setTilemap(std::unique_ptr<Tilemap> tilemap, const Textures textureIdentifier, const Fonts fontIdentifier, const sf::Color& background) noexcept;

	void spawnMario(const Tile::Index& tileIndex) noexcept;
	void spawnGoomba(const Tile::Index& tileIndex) noexcept;

	void putCoin(const Tile::Index& tileIndex) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void update(const sf::Time& dt) noexcept;

	const ResourceContainer& getResources() noexcept;
	const SpritesetContainer& getSpritesets() noexcept;

	TilemapView& getTilemapView() noexcept;
	const TilemapView& getTilemapView() const noexcept;

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
