#include "HeroStandState.hpp"

#include "HeroMoveState.hpp"
#include "HeroFallState.hpp"
#include "HeroJumpState.hpp"
#include "HeroLoseState.hpp"
#include "Enemy.hpp"

void HeroStandState::onSet(Hero& entity) noexcept
{
    entity.setAccelerationX(0.0f);
    entity.setStandSprite();
}

void HeroStandState::update(Hero&, const sf::Time&) noexcept
{

}

void HeroStandState::collision(Hero&, const Tile&, const CollisionSideType) noexcept
{

}

void HeroStandState::collision(Hero&, const Hero&, const CollisionSideType) noexcept
{

}

void HeroStandState::collision(Hero& entity, const Enemy& enemy, const CollisionSideType) noexcept
{
    if (!enemy.hasComponent(Entity::ComponentType::Transparent))
    {
        entity.setState<HeroLoseState>();
    }
}

void HeroStandState::collision(Hero&, const Item&, const CollisionSideType) noexcept
{

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
