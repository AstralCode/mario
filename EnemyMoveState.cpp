#include "EnemyMoveState.hpp"

#include "EnemyFallState.hpp"

void EnemyMoveState::onSet(Enemy& entity) noexcept
{
    entity.setAccelerationX(Constants::World::Enemy::AccelerationX);
    entity.setAccelerationY(0.0f);
    entity.setMoveAnimation();
}

void EnemyMoveState::update(Enemy& entity, const sf::Time& dt) noexcept
{
    entity.updateMoveAnimation(dt);
}

void EnemyMoveState::tileCollision(Enemy& entity, const Tile&, const CollisionSideType side) noexcept
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

void EnemyMoveState::entityCollision(Enemy& entity, const Entity& collider, const CollisionSideType) noexcept
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

void EnemyMoveState::falling(Enemy& entity) noexcept
{
    entity.setState<EnemyFallState>();
}

void EnemyMoveState::onKeyPressed(Enemy&, const sf::Event::KeyEvent&) noexcept
{

}

void EnemyMoveState::onKeyReleased(Enemy&, const sf::Event::KeyEvent&) noexcept
{

}

bool EnemyMoveState::isJumping() const noexcept
{
    return false;
}

bool EnemyMoveState::isFalling() const noexcept
{
    return false;
}
