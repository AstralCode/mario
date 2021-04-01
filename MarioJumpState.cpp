#include "MarioJumpState.hpp"

#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"
#include "MarioFallState.hpp"
#include "MarioLoseState.hpp"

void MarioJumpState::onSet(Mario& entity) noexcept
{
    entity.setVelocityY(-entity.getJumpVelocity());
    entity.playJumpAnimation();
}

void MarioJumpState::update(Mario& entity, const sf::Time& dt) noexcept
{
    entity.updateJumpAnimation(dt);

    if (entity.getVelocity().getX() > 0.0f)
    {
        entity.setState<MarioFallState>();
    }
}

void MarioJumpState::collision(Mario& entity, const Tile&, const CollisionSideType side) noexcept
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
    else if (side == CollisionSideType::Bottom)
    {
        entity.setVelocityY(entity.getVelocity().getY() + Constants::World::Mario::MaxVelocityY * 0.2f);
    }
}

void MarioJumpState::collision(Mario& entity, const Entity& collider, const CollisionSideType side) noexcept
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
        else if (collider.hasType(EntityType::Item))
        {
            if (collider.hasComponent(Entity::ComponentType::Solid))
            {
                if (side == CollisionSideType::Top)
                {
                    entity.setVelocityY(entity.getVelocity().getY() + Constants::World::Mario::MaxVelocityY * 0.2f);
                }
            }
        }
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
