#include "EnemyMoveState.hpp"

#include "EnemyFallState.hpp"
#include "EnemyLoseState.hpp"

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

void EnemyMoveState::entityCollision(Enemy& entity, const Entity& collider, const CollisionSideType side) noexcept
{
    if (!collider.hasTrait(Entity::TraitType::Transparent))
    {
        if (collider.hasTrait(Entity::TraitType::Hero))
        {
            if (side == CollisionSideType::Bottom)
            {
                entity.setState<EnemyLoseState>();
            }
        }

        if (!entity.hasTrait(Entity::TraitType::Transparent))
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
