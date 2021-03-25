#include "MarioStandState.hpp"

#include "MarioMoveState.hpp"
#include "MarioFallState.hpp"
#include "MarioJumpState.hpp"

void MarioStandState::onSet(Mario& entity) noexcept
{
    entity.setAccelerationX(0.0f);
    entity.setStandSprite();
}

void MarioStandState::update(Mario&, const sf::Time&) noexcept
{

}

void MarioStandState::tileCollision(Mario&, const Tile&, const CollisionSideType) noexcept
{

}

void MarioStandState::entityCollision(Mario& entity, const Entity& collider, const CollisionSideType) noexcept
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

void MarioStandState::falling(Mario& entity) noexcept
{
    entity.setState<MarioFallState>();
}

void MarioStandState::onKeyPressed(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left)
    {
        entity.setDirection(Entity::Directions::Left);
        entity.setState<MarioMoveState>();
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        entity.setDirection(Entity::Directions::Right);
        entity.setState<MarioMoveState>();
    }
    else if (keyEvent.code == Constants::World::Mario::Up)
    {
        entity.setState<MarioJumpState>();
    }
}

void MarioStandState::onKeyReleased(Mario&, const sf::Event::KeyEvent&) noexcept
{

}

bool MarioStandState::isJumping() const noexcept
{
    return false;
}

bool MarioStandState::isFalling() const noexcept
{
    return false;
}
