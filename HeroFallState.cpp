#include "HeroFallState.hpp"

#include "HeroStandState.hpp"
#include "HeroMoveState.hpp"
#include "HeroJumpState.hpp"
#include "HeroLoseState.hpp"
#include "Enemy.hpp"

void HeroFallState::onSet(Hero& entity) noexcept
{
    entity.setJumpSprite();
}

void HeroFallState::update(Hero&, const sf::Time&) noexcept
{

}

void HeroFallState::collision(Hero& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Top)
    {
        if (std::fabs(entity.getVelocity().getX()) > Constants::World::Hero::StopVelocityX)
        {
            entity.setState<HeroMoveState>();
        }
        else
        {
            entity.setState<HeroStandState>();
        }
    }
}

void HeroFallState::collision(Hero&, const Hero&, const CollisionSideType) noexcept
{

}

void HeroFallState::collision(Hero& entity, const Enemy& enemy, const CollisionSideType side) noexcept
{
    if (!enemy.hasComponent(Entity::ComponentType::Transparent))
    {
        if (side == CollisionSideType::Top)
        {
            entity.setJumpVelocity(Constants::World::Hero::MaxVelocityY / 2.0f);
            entity.setState<HeroJumpState>();
        }
        else
        {
            entity.setState<HeroLoseState>();
        }
    }
}

void HeroFallState::collision(Hero&, const Item&, const CollisionSideType) noexcept
{

}

void HeroFallState::falling(Hero&) noexcept
{

}

void HeroFallState::onKeyPressed(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Hero::Left)
    {
        entity.setAccelerationX(Constants::World::Hero::AccelerationX);
        entity.setDirection(Entity::Directions::Left);
    }
    else if (keyEvent.code == Constants::World::Hero::Right)
    {
        entity.setAccelerationX(Constants::World::Hero::AccelerationX);
        entity.setDirection(Entity::Directions::Right);
    }
}

void HeroFallState::onKeyReleased(Hero&, const sf::Event::KeyEvent&) noexcept
{

}

bool HeroFallState::isJumping() const noexcept
{
    return false;
}

bool HeroFallState::isFalling() const noexcept
{
    return true;
}
