#include "MarioMoveState.hpp"

#include "MarioStandState.hpp"
#include "MarioFallState.hpp"
#include "MarioJumpState.hpp"
#include "MarioLoseState.hpp"

void MarioMoveState::onSet(Mario& entity) noexcept
{
    if (sf::Keyboard::isKeyPressed(Constants::World::Mario::Left) ||
        sf::Keyboard::isKeyPressed(Constants::World::Mario::Right))
    {
        entity.setAccelerationX(Constants::World::Mario::AccelerationX);
    }
    else
    {
        entity.setAccelerationX(0.0f);
    }

    entity.setMoveAnimation();
}

void MarioMoveState::update(Mario& entity, const sf::Time& dt) noexcept
{
    entity.updateMoveAnimation(dt);

    if (entity.getAcceleration().getX() > 0.0f)
    {
        if (entity.getVelocity().getX() > Constants::World::Mario::StopVelocityX)
        {
            if (entity.hasDirection(Entity::Directions::Left))
            {
                entity.setSlideSprite();
            }
        }
        else if (entity.hasDirection(Entity::Directions::Right))
        {
            entity.setSlideSprite();
        }
    }
    else if (std::fabs(entity.getVelocity().getX()) < Constants::World::Mario::StopVelocityX)
    {
        entity.setState<MarioStandState>();
    }
}

void MarioMoveState::tileCollision(Mario&, const Tile&, const CollisionSideType) noexcept
{

}

void MarioMoveState::entityCollision(Mario& entity, const Entity& collider, const CollisionSideType side) noexcept
{
    if (!collider.hasAttribute(Entity::Attributes::Transparent))
    {
        if (collider.hasAttribute(Entity::Attributes::Deadly))
        {
            if (side == CollisionSideType::Top)
            {
                entity.setJumpVelocity(Constants::World::Mario::MaxVelocityY / 2.0f);
                entity.setState<MarioJumpState>();
            }
            else if (collider.hasAttribute(Entity::Attributes::Deadly))
            {
                entity.setState<MarioLoseState>();
            }
        }
        else if (collider.hasAttribute(Entity::Attributes::Collectable))
        {
            // collect item...
        }
    }
}

void MarioMoveState::falling(Mario& entity) noexcept
{
    entity.setState<MarioFallState>();
}

void MarioMoveState::onKeyPressed(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept
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
    else if (keyEvent.code == Constants::World::Mario::Up)
    {
        entity.setJumpVelocity(Constants::World::Mario::MaxVelocityY);
        entity.setState<MarioJumpState>();
    }
}

void MarioMoveState::onKeyReleased(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left ||
        keyEvent.code == Constants::World::Mario::Right)
    {
        entity.setAccelerationX(0.0f);
    }

    if (keyEvent.code == Constants::World::Mario::Left)
    {
        if (sf::Keyboard::isKeyPressed(Constants::World::Mario::Right))
        {
            entity.setAccelerationX(Constants::World::Mario::AccelerationX);
            entity.setDirection(Entity::Directions::Right);
        }
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        if (sf::Keyboard::isKeyPressed(Constants::World::Mario::Left))
        {
            entity.setAccelerationX(Constants::World::Mario::AccelerationX);
            entity.setDirection(Entity::Directions::Left);
        }
    }
}

bool MarioMoveState::isJumping() const noexcept
{
    return false;
}

bool MarioMoveState::isFalling() const noexcept
{
    return false;
}
