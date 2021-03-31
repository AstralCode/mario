#include "MarioFallState.hpp"

#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"
#include "MarioJumpState.hpp"
#include "MarioLoseState.hpp"

void MarioFallState::onSet(Mario& entity) noexcept
{
    entity.playJumpAnimation();
}

void MarioFallState::update(Mario& entity, const sf::Time& dt) noexcept
{
    entity.updateJumpAnimation(dt);
}

void MarioFallState::collision(Mario& entity, const Tile&, const CollisionSideType side) noexcept
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

void MarioFallState::collision(Mario& entity, const Entity& collider, const CollisionSideType side) noexcept
{
    if (!collider.hasComponent(Entity::ComponentType::Transparency))
    {
        if (collider.hasType(EntityType::Enemy))
        {
            if (side == CollisionSideType::Top)
            {
                entity.setJumpVelocity(Constants::World::Mario::MaxVelocityY / 2.0f);
                entity.setState<MarioJumpState>();
            }
            else
            {
                entity.setState<MarioLoseState>();
            }
        }
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
