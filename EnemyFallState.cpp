#include "EnemyFallState.hpp"

#include "EnemyMoveState.hpp"
#include "EnemyLoseState.hpp"

void EnemyFallState::onSet(Enemy& entity) noexcept
{
    entity.setAccelerationX(0.0f);
}

void EnemyFallState::update(Enemy&, const sf::Time&) noexcept
{

}

void EnemyFallState::tileCollision(Enemy& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Top)
    {
        entity.setState<EnemyMoveState>();
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

void EnemyFallState::entityCollision(Enemy& entity, const Entity& collider, const CollisionSideType side) noexcept
{
    if (!collider.hasAttribute(Entity::Attributes::Transparent))
    {
        if (collider.hasAttribute(Entity::Attributes::Destroyer))
        {
            if (side == CollisionSideType::Bottom)
            {
                entity.setState<EnemyLoseState>();
            }
        }

        if (!entity.hasAttribute(Entity::Attributes::Transparent))
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
}

void EnemyFallState::falling(Enemy&) noexcept
{

}

void EnemyFallState::onKeyPressed(Enemy&, const sf::Event::KeyEvent&) noexcept
{

}

void EnemyFallState::onKeyReleased(Enemy&, const sf::Event::KeyEvent&) noexcept
{

}

bool EnemyFallState::isJumping() const noexcept
{
    return false;
}

bool EnemyFallState::isFalling() const noexcept
{
    return true;
}
