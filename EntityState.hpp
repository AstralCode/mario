#pragma once

#include "Tile.hpp"

class Entity;

template <typename TEntity>
class EntityState
{
public:
	~EntityState() = default;

	virtual void onSet(TEntity& entity) noexcept = 0;

	virtual void update(TEntity& entity, const sf::Time& dt) noexcept = 0;

	virtual void tileCollision(TEntity& entity, const Tile& tile, const Tile::Sides side) noexcept = 0;
	virtual void entityCollision(TEntity& entity, Entity& collider) noexcept = 0;

	virtual void falling() noexcept = 0;

	virtual bool isJumping() const noexcept = 0;
	virtual bool isFalling() const noexcept = 0;
};
