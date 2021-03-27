#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "Tile.hpp"
#include "CollisionSideType.hpp"

class Hero;
class Enemy;
class Item;

template <typename TEntity>
class EntityState
{
public:
	virtual ~EntityState() = default;

	virtual void onSet(TEntity& entity) noexcept = 0;

	virtual void update(TEntity& entity, const sf::Time& dt) noexcept = 0;

	virtual void collision(TEntity& entity, const Tile& tile, const CollisionSideType side) noexcept = 0;

	virtual void collision(TEntity& entity, const Hero& hero, const CollisionSideType side) noexcept = 0;
	virtual void collision(TEntity& entity, const Enemy& enemy, const CollisionSideType side) noexcept = 0;
	virtual void collision(TEntity& entity, const Item& item, const CollisionSideType side) noexcept = 0;

	virtual void falling(TEntity& entity) noexcept = 0;

	virtual void onKeyPressed(TEntity& entity, const sf::Event::KeyEvent& keyEvent) noexcept = 0;
	virtual void onKeyReleased(TEntity& entity, const sf::Event::KeyEvent& keyEvent) noexcept = 0;

	virtual bool isJumping() const noexcept = 0;
	virtual bool isFalling() const noexcept = 0;
};
