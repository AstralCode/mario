#include "EnemyLoseState.hpp"

void EnemyLoseState::onSet(Enemy& entity) noexcept
{
    entity.setAttribute(Entity::Attributes::Transparent);
    entity.unsetAttribute(Entity::Attributes::Movable);
    entity.setAccelerationX(0.0f);
    entity.setAccelerationY(0.0f);
    entity.setLoseSprite();
}

void EnemyLoseState::update(Enemy& entity, const sf::Time& dt) noexcept
{
    entity.updateLoseTime(dt);

    if (entity.getLoseTime() >= sf::seconds(Constants::World::Enemy::LoseAnimationDuration))
    {
        entity.destroy();
    }
}

void EnemyLoseState::tileCollision(Enemy&, const Tile&, const CollisionSideType) noexcept
{

}

void EnemyLoseState::entityCollision(Enemy&, const Entity&, const CollisionSideType) noexcept
{

}

void EnemyLoseState::falling(Enemy&) noexcept
{

}

void EnemyLoseState::onKeyPressed(Enemy&, const sf::Event::KeyEvent&) noexcept
{

}

void EnemyLoseState::onKeyReleased(Enemy&, const sf::Event::KeyEvent&) noexcept
{

}

bool EnemyLoseState::isJumping() const noexcept
{
    return false;
}

bool EnemyLoseState::isFalling() const noexcept
{
    return false;
}
