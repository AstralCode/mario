#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "Tile.hpp"
#include "CollisionSideType.hpp"

class Entity;

template <typename TEntity>
class EntityState
{
public:
	virtual ~EntityState() = default;

	virtual void onSet(TEntity& entity) noexcept = 0;

	virtual void update(TEntity& entity, const sf::Time& dt) noexcept = 0;

	virtual void collision(TEntity& entity, const Tile& tile, const CollisionSideType side) noexcept = 0;
	virtual void collision(TEntity& entity, const Entity& collider, const CollisionSideType side) noexcept = 0;

	virtual void falling(TEntity& entity) noexcept = 0;

	virtual void onKeyPressed(TEntity& entity, const sf::Event::KeyEvent& keyEvent) noexcept = 0;
	virtual void onKeyReleased(TEntity& entity, const sf::Event::KeyEvent& keyEvent) noexcept = 0;
};
