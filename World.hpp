#pragma once

#include "TilemapView.hpp"
#include "EntityContainer.hpp"
#include "PhysicsModule.hpp"
#include "CollisionModule.hpp"

class ResourceContainer;

class World final : public sf::Drawable
{
public:
	World() noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void update(const sf::Time& dt) noexcept;

	TilemapView& getTilemapView() noexcept;
	const TilemapView& getTilemapView() const noexcept;

	EntityContainer& getEntities() noexcept;
	const EntityContainer& getEntities() const noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	GraphicsItem mRoot;
	GraphicsItem& mEntityLayer;

	TilemapView mTilemapView;
	EntityContainer mEntities;

	PhysicsModule mPhysicsModule;
	CollisionModule mCollisionModule;
};
