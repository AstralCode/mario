#include "CreatureMoveState.hpp"

#include "CreatureFallState.hpp"

void CreatureMoveState::onSet(Creature& entity) noexcept
{
    entity.setAccelerationX(Constants::World::Creature::AccelerationX);
    entity.setAccelerationY(0.0f);
    entity.setMoveAnimation();
}

void CreatureMoveState::update(Creature& entity, const sf::Time& dt) noexcept
{
    entity.updateMoveAnimation(dt);
}

void CreatureMoveState::tileCollision(Creature& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Left || side == CollisionSideType::Right)
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

void CreatureMoveState::entityCollision(Creature& entity, const Entity& collider, const CollisionSideType) noexcept
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

void CreatureMoveState::falling(Creature& entity) noexcept
{
    entity.setState<CreatureFallState>();
}

void CreatureMoveState::onKeyPressed(Creature&, const sf::Event::KeyEvent&) noexcept
{

}

void CreatureMoveState::onKeyReleased(Creature&, const sf::Event::KeyEvent&) noexcept
{

}

bool CreatureMoveState::isJumping() const noexcept
{
    return false;
}

bool CreatureMoveState::isFalling() const noexcept
{
    return false;
}
