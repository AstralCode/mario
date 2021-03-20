#include "CreatureFallState.hpp"

#include "CreatureMoveState.hpp"

void CreatureFallState::onSet(Creature& entity) noexcept
{
    entity.setAccelerationX(0.0f);
    entity.setAccelerationY(3500.0f);
}

void CreatureFallState::update(Creature&, const sf::Time&) noexcept
{

}

void CreatureFallState::tileCollision(Creature& entity, const Tile&, const Tile::Sides side) noexcept
{
    if (side == Tile::Sides::Top)
    {
        //entity.setState<CreatureMoveState>();
    }
    else if (side == Tile::Sides::Left || side == Tile::Sides::Right)
    {
        if (entity.hasDirection(Entity::Direction::Right))
        {
            entity.setDirection(Entity::Direction::Left);
        }
        else
        {
            entity.setDirection(Entity::Direction::Right);
        }

        entity.setVelocityX(-entity.getVelocity().getX());
    }
}

void CreatureFallState::entityCollision(Creature& entity, Creature& collider) noexcept
{
    if (entity.hasDirection(Entity::Direction::Right))
    {
        entity.setDirection(Entity::Direction::Left);
        collider.setDirection(Entity::Direction::Right);
    }
    else
    {
        entity.setDirection(Entity::Direction::Right);
        collider.setDirection(Entity::Direction::Left);
    }

    entity.setVelocityX(-entity.getVelocity().getX());
    collider.setVelocityX(-collider.getVelocity().getX());
}

void CreatureFallState::falling() noexcept
{

}

bool CreatureFallState::isJumping() const noexcept
{
    return false;
}

bool CreatureFallState::isFalling() const noexcept
{
    return true;
}
