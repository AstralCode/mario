#include "EnemyLoseState.hpp"

void EnemyLoseState::onSet(Enemy& entity) noexcept
{
    entity.setComponent(Entity::ComponentType::Transparency);
    entity.unsetComponent(Entity::ComponentType::Movement);
    entity.setAccelerationX(0.0f);
    entity.setAccelerationY(0.0f);
    entity.setLoseAnimation();
}

void EnemyLoseState::update(Enemy& entity, const sf::Time& dt) noexcept
{
    entity.updateLoseAnimation(dt);

    if (entity.getLoseTime() >= sf::seconds(Constants::World::Enemy::LoseAnimationDuration))
    {
        entity.destroy();
    }
}

void EnemyLoseState::collision(Enemy&, const Tile&, const CollisionSideType) noexcept
{

}

void EnemyLoseState::collision(Enemy&, const Hero&, const CollisionSideType) noexcept
{

}

void EnemyLoseState::collision(Enemy&, const Enemy&, const CollisionSideType) noexcept
{

}

void EnemyLoseState::collision(Enemy&, const Item&, const CollisionSideType) noexcept
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
