#include "MarioStandState.hpp"

#include "MarioMoveState.hpp"
#include "MarioFallState.hpp"
#include "MarioJumpState.hpp"
#include "MarioLoseState.hpp"

void MarioStandState::onSet(Mario& entity) noexcept
{
    entity.setAccelerationX(0.0f);
    entity.playStandAnimation();
}

void MarioStandState::update(Mario& entity, const sf::Time& dt) noexcept
{
    entity.updateStandAnimation(dt);
}

void MarioStandState::collision(Mario&, const Tile&, const CollisionSideType) noexcept
{

}

void MarioStandState::collision(Mario& entity, const Entity& collider, const CollisionSideType) noexcept
{
    if (!collider.hasComponent(Entity::ComponentType::Transparency))
    {
        if (collider.hasType(EntityType::Enemy))
        {
            entity.setState<MarioLoseState>();
        }
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
        entity.setJumpVelocity(Constants::World::Mario::MaxVelocityY);
        entity.setState<MarioJumpState>();
    }
}

void MarioStandState::onKeyReleased(Mario&, const sf::Event::KeyEvent&) noexcept
{

}
