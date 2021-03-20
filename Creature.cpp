#include "Creature.hpp"

void Creature::update(const sf::Time& dt) noexcept
{

}

void Creature::tileCollision(const Tile& tile, const Tile::Sides side) noexcept
{

}

void Creature::entityCollision(Creature& entity, Entity& collider) noexcept
{

}

void Creature::falling() noexcept
{

}

Animation& Creature::getMoveAnimation() noexcept
{
	return mMoveAnimation;
}

bool Creature::isJumping() const noexcept
{
	return false;
}

bool Creature::isFalling() const noexcept
{
	return false;
}
