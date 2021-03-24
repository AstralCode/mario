#include "MarioJumpState.hpp"

void MarioJumpState::onSet(Mario& entity) noexcept
{
    entity.setVelocityY(-Constants::World::Mario::MaxVelocityY);
    entity.setJumpSprite();
}

void MarioJumpState::update(Mario& entity, const sf::Time&) noexcept
{
    if (entity.getVelocity().getX() > 0.0f)
    {
        entity.setState(Mario::States::Fall);
    }
}

void MarioJumpState::tileCollision(Mario& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Top)
    {
        if (std::fabs(entity.getVelocity().getX()) > Constants::World::Mario::StopVelocityX)
        {
            entity.setState(Mario::States::Move);
        }
        else
        {
            entity.setState(Mario::States::Stand);
        }
    }
    else if (side == CollisionSideType::Bottom)
    {
        entity.setVelocityY(entity.getVelocity().getY() + Constants::World::Mario::MaxVelocityY * 0.2f);
    }

}

void MarioJumpState::entityCollision(Mario& entity, const Entity& collider, const CollisionSideType) noexcept
{
    if (collider.hasAttribute(Entity::Attributes::Deadly))
    {
        entity.destroy();
    }
    else if (collider.hasAttribute(Entity::Attributes::Collectable))
    {
        // collect item...
    }
}

void MarioJumpState::falling(Mario&) noexcept
{

}

void MarioJumpState::onKeyPressed(Mario& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left)
    {
        object.setAccelerationX(Constants::World::Mario::AccelerationX);
        object.setDirection(Entity::Directions::Left);
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        object.setAccelerationX(Constants::World::Mario::AccelerationX);
        object.setDirection(Entity::Directions::Right);
    }
}

void MarioJumpState::onKeyReleased(Mario&, const sf::Event::KeyEvent&) noexcept
{

}

bool MarioJumpState::isJumping() const noexcept
{
    return true;
}

bool MarioJumpState::isFalling() const noexcept
{
    return false;
}
