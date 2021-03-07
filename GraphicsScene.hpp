#pragma once

#include "TilemapView.hpp"
#include "GameObjectContainer.hpp"
#include "PhysicsModule.hpp"
#include "CollisionModule.hpp"

class GraphicsScene final : public sf::Drawable
{
public:
	GraphicsScene() noexcept;
	
	GameObject* createGameObject(const GameObjectIdentifiers identifier) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void update(const sf::Time& frameTime) noexcept;

	TilemapView& getTilemapView() noexcept;
	const TilemapView& getTilemapView() const noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	TilemapView mTilemapView;

	GraphicsItem mRoot;
	GraphicsItem& mGameObjectLayer;

	GameObjectContainer mGameObjectContainer;

	PhysicsModule mPhysicsModule;
	CollisionModule mCollisionModule;
};
