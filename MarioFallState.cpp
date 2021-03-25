#include "MarioFallState.hpp"

#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"

void MarioFallState::onSet(Mario& entity) noexcept
{
    entity.setJumpSprite();
}

void MarioFallState::update(Mario&, const sf::Time&) noexcept
{

}

void MarioFallState::tileCollision(Mario& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Top)
    {
        if (std::fabs(entity.getVelocity().getX()) > Constants::World::Mario::StopVelocityX)
        {
            entity.setState<MarioMoveState>();
        }
        else
        {
            entity.setState<MarioStandState>();
        }
    }
}

void MarioFallState::entityCollision(Mario& entity, const Entity& collider, const CollisionSideType) noexcept
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

void MarioFallState::falling(Mario&) noexcept
{

}

void MarioFallState::onKeyPressed(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left)
    {
        entity.setAccelerationX(Constants::World::Mario::AccelerationX);
        entity.setDirection(Entity::Directions::Left);
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        entity.setAccelerationX(Constants::World::Mario::AccelerationX);
        entity.setDirection(Entity::Directions::Right);
    }
}

void MarioFallState::onKeyReleased(Mario&, const sf::Event::KeyEvent&) noexcept
{

}

bool MarioFallState::isJumping() const noexcept
{
    return false;
}

bool MarioFallState::isFalling() const noexcept
{
    return true;
}
