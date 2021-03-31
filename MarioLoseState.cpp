#include "MarioLoseState.hpp"

void MarioLoseState::onSet(Mario& entity) noexcept
{
    entity.setComponent(Entity::ComponentType::Transparency);
    entity.unsetComponent(Entity::ComponentType::Movement);
    entity.setAccelerationX(0.0f);
    entity.setVelocityX(0.0f);
    entity.setAccelerationY(0.0f);
    entity.setVelocityY(0.0f);
    entity.playLoseAnimation();
}

void MarioLoseState::update(Mario& entity, const sf::Time& dt) noexcept
{
    entity.updateLoseAnimation(dt);
    
    if (entity.getLoseTime() >= sf::seconds(Constants::World::Mario::LoseAnimationEnd))
    {
        entity.destroy();
    }
    else if (!entity.hasComponent(Entity::ComponentType::Movement))
    {
        if (entity.getLoseTime() >= sf::seconds(Constants::World::Mario::LoseAnimationStart))
        {
            entity.setComponent(Entity::ComponentType::Movement);
            entity.setVelocityY(-Constants::World::Mario::MaxVelocityY);
        }
    }
}

void MarioLoseState::collision(Mario&, const Tile&, const CollisionSideType) noexcept
{

}

void MarioLoseState::collision(Mario&, const Entity&, const CollisionSideType) noexcept
{

}

void MarioLoseState::falling(Mario&) noexcept
{

}

void MarioLoseState::onKeyPressed(Mario&, const sf::Event::KeyEvent&) noexcept
{

}

void MarioLoseState::onKeyReleased(Mario&, const sf::Event::KeyEvent&) noexcept
{

}
