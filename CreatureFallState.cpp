#include "CreatureFallState.hpp"

void CreatureFallState::onSet(Creature& entity) noexcept
{
    entity.setAccelerationX(0.0f);
}

void CreatureFallState::update(Creature&, const sf::Time&) noexcept
{

}

void CreatureFallState::tileCollision(Creature& entity, const Tile&, const Sides side) noexcept
{
    if (side == Sides::Top)
    {
        entity.setState(Creature::States::Move);
    }
    else if (side == Sides::Left || side == Sides::Right)
    {
        if (entity.hasDirection(Entity::Directions::Right))
        {
            entity.setDirection(Entity::Directions::Left);
        }
        else
        {
            entity.setDirection(Entity::Directions::Right);
        }

        entity.setVelocityX(-entity.getVelocity().getX());
    }
}

void CreatureFallState::entityCollision(Creature& entity, const Entity&, const Sides) noexcept
{
    if (entity.hasDirection(Entity::Directions::Right))
    {
        entity.setDirection(Entity::Directions::Left);
    }
    else
    {
        entity.setDirection(Entity::Directions::Right);
    }

    entity.setVelocityX(-entity.getVelocity().getX());
}

void CreatureFallState::falling(Creature&) noexcept
{

}

void CreatureFallState::onKeyPressed(Creature&, const sf::Event::KeyEvent&) noexcept
{

}

void CreatureFallState::onKeyReleased(Creature&, const sf::Event::KeyEvent&) noexcept
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
