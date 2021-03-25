#include "MarioLoseState.hpp"

void MarioLoseState::onSet(Mario& entity) noexcept
{
    entity.setAttribute(Entity::Attributes::Transparent);
    entity.unsetAttribute(Entity::Attributes::Movable);
    entity.setAccelerationX(0.0f);
    entity.setVelocityX(0.0f);
    entity.setAccelerationY(0.0f);
    entity.setVelocityY(0.0f);
    entity.setLoseSprite();
}

void MarioLoseState::update(Mario& entity, const sf::Time& dt) noexcept
{
    entity.updateLoseAnimation(dt);
    
    if (entity.getLoseTime() >= sf::seconds(Constants::World::Mario::LoseAnimationEnd))
    {
        entity.destroy();
    }
    else if (!entity.hasAttribute(Entity::Attributes::Movable))
    {
        if (entity.getLoseTime() >= sf::seconds(Constants::World::Mario::LoseAnimationStart))
        {
            entity.setAttribute(Entity::Attributes::Movable);
            entity.setVelocityY(-Constants::World::Mario::MaxVelocityY);
        }
    }
}

void MarioLoseState::tileCollision(Mario&, const Tile&, const CollisionSideType) noexcept
{

}

void MarioLoseState::entityCollision(Mario&, const Entity&, const CollisionSideType) noexcept
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

bool MarioLoseState::isJumping() const noexcept
{
    return false;
}

bool MarioLoseState::isFalling() const noexcept
{
    return false;
}
