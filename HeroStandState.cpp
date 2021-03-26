#include "HeroStandState.hpp"

#include "HeroMoveState.hpp"
#include "HeroFallState.hpp"
#include "HeroJumpState.hpp"
#include "HeroLoseState.hpp"

void HeroStandState::onSet(Hero& entity) noexcept
{
    entity.setAccelerationX(0.0f);
    entity.setStandSprite();
}

void HeroStandState::update(Hero&, const sf::Time&) noexcept
{

}

void HeroStandState::tileCollision(Hero&, const Tile&, const CollisionSideType) noexcept
{

}

void HeroStandState::entityCollision(Hero& entity, const Entity& collider, const CollisionSideType side) noexcept
{
    if (!collider.hasTrait(Entity::TraitType::Transparent))
    {
        if (collider.hasTrait(Entity::TraitType::Enemy))
        {
            if (side == CollisionSideType::Top)
            {
                entity.setJumpVelocity(Constants::World::Hero::MaxVelocityY / 2.0f);
                entity.setState<HeroJumpState>();
            }
            else if (collider.hasTrait(Entity::TraitType::Enemy))
            {
                entity.setState<HeroLoseState>();
            }
        }
        else if (collider.hasTrait(Entity::TraitType::Item))
        {
            // collect item...
        }
    }
}

void HeroStandState::falling(Hero& entity) noexcept
{
    entity.setState<HeroFallState>();
}

void HeroStandState::onKeyPressed(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Hero::Left)
    {
        entity.setDirection(Entity::Directions::Left);
        entity.setState<HeroMoveState>();
    }
    else if (keyEvent.code == Constants::World::Hero::Right)
    {
        entity.setDirection(Entity::Directions::Right);
        entity.setState<HeroMoveState>();
    }
    else if (keyEvent.code == Constants::World::Hero::Up)
    {
        entity.setJumpVelocity(Constants::World::Hero::MaxVelocityY);
        entity.setState<HeroJumpState>();
    }
}

void HeroStandState::onKeyReleased(Hero&, const sf::Event::KeyEvent&) noexcept
{

}

bool HeroStandState::isJumping() const noexcept
{
    return false;
}

bool HeroStandState::isFalling() const noexcept
{
    return false;
}
