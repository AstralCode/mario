#pragma once

#include "GameObject.hpp"
#include "TilemapView.hpp"
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

	GraphicsItem mGameObjectLayer;
	std::vector<GameObject*> mGameObjects;

	PhysicsModule mPhysicsModule;
	CollisionModule mCollisionModule;
};
