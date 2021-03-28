#include "EnemyMoveState.hpp"

#include "EnemyFallState.hpp"
#include "EnemyLoseState.hpp"
#include "Hero.hpp"

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

void EnemyMoveState::collision(Enemy& entity, const Tile&, const CollisionSideType side) noexcept
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

void EnemyMoveState::collision(Enemy& entity, const Hero& hero, const CollisionSideType side) noexcept
{
    if (!hero.hasComponent(Entity::ComponentType::Transparency))
    {
        if (side == CollisionSideType::Bottom)
        {
            entity.setState<EnemyLoseState>();
        }
    }
}

void EnemyMoveState::collision(Enemy& entity, const Enemy& enemy, const CollisionSideType) noexcept
{
    if (!enemy.hasComponent(Entity::ComponentType::Transparency))
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

void EnemyMoveState::collision(Enemy&, const Item&, const CollisionSideType) noexcept
{

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
