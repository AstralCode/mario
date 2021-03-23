#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "Tile.hpp"
#include "Sides.hpp"

class Entity;

template <typename TEntity>
class EntityState
{
public:
	virtual ~EntityState() = default;

	virtual void onSet(TEntity& entity) noexcept = 0;

	virtual void update(TEntity& entity, const sf::Time& dt) noexcept = 0;

	virtual void tileCollision(TEntity& entity, const Tile& tile, const Sides side) noexcept = 0;
	virtual void entityCollision(TEntity& entity, const Entity& collider, const Sides side) noexcept = 0;

	virtual void falling(TEntity& entity) noexcept = 0;

	virtual void onKeyPressed(TEntity& entity, const sf::Event::KeyEvent& keyEvent) noexcept = 0;
	virtual void onKeyReleased(TEntity& object, const sf::Event::KeyEvent& keyEvent) noexcept = 0;

	virtual bool isJumping() const noexcept = 0;
	virtual bool isFalling() const noexcept = 0;
};
