#include "CreatureFallState.hpp"

void CreatureFallState::onSet(Creature& entity) noexcept
{
    entity.setAccelerationX(0.0f);
}

void CreatureFallState::update(Creature&, const sf::Time&) noexcept
{

}

void CreatureFallState::tileCollision(Creature& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Top)
    {
        entity.setState(Creature::States::Move);
    }
    else if (side == CollisionSideType::Left || side == CollisionSideType::Right)
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

void CreatureFallState::entityCollision(Creature& entity, const Entity& collider, const CollisionSideType) noexcept
{
    if (!collider.hasAttribute(Entity::Attributes::Controlablle))
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
