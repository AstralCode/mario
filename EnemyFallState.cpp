#include "EnemyFallState.hpp"

#include "EnemyMoveState.hpp"
#include "EnemyLoseState.hpp"
#include "Hero.hpp"

void EnemyFallState::onSet(Enemy& entity) noexcept
{
    entity.setAccelerationX(0.0f);
}

void EnemyFallState::update(Enemy&, const sf::Time&) noexcept
{

}

void EnemyFallState::collision(Enemy& entity, const Tile&, const CollisionSideType side) noexcept
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

void EnemyFallState::collision(Enemy& entity, const Hero& hero, const CollisionSideType side) noexcept
{
    if (!hero.hasComponent(Entity::ComponentType::Transparency))
    {
        if (side == CollisionSideType::Bottom)
        {
            entity.setState<EnemyLoseState>();
        }
    }
}

void EnemyFallState::collision(Enemy& entity, const Enemy& enemy, const CollisionSideType) noexcept
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

void EnemyFallState::collision(Enemy&, const Item&, const CollisionSideType) noexcept
{

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
