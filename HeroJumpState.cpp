#include "HeroJumpState.hpp"

#include "HeroStandState.hpp"
#include "HeroMoveState.hpp"
#include "HeroFallState.hpp"
#include "HeroLoseState.hpp"
#include "Enemy.hpp"

void HeroJumpState::onSet(Hero& entity) noexcept
{
    entity.setVelocityY(-entity.getJumpVelocity());
    entity.setJumpSprite();
}

void HeroJumpState::update(Hero& entity, const sf::Time&) noexcept
{
    if (entity.getVelocity().getX() > 0.0f)
    {
        entity.setState<HeroFallState>();
    }
}

void HeroJumpState::collision(Hero& entity, const Tile&, const CollisionSideType side) noexcept
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
    else if (side == CollisionSideType::Bottom)
    {
        entity.setVelocityY(entity.getVelocity().getY() + Constants::World::Hero::MaxVelocityY * 0.2f);
    }

}

void HeroJumpState::collision(Hero&, const Hero&, const CollisionSideType) noexcept
{

}

void HeroJumpState::collision(Hero& entity, const Enemy& enemy, const CollisionSideType side) noexcept
{
    if (!enemy.hasComponent(Entity::ComponentType::Transparency))
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

void HeroJumpState::collision(Hero&, const Item&, const CollisionSideType) noexcept
{

}

void HeroJumpState::falling(Hero&) noexcept
{

}

void HeroJumpState::onKeyPressed(Hero& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Hero::Left)
    {
        object.setAccelerationX(Constants::World::Hero::AccelerationX);
        object.setDirection(Entity::Directions::Left);
    }
    else if (keyEvent.code == Constants::World::Hero::Right)
    {
        object.setAccelerationX(Constants::World::Hero::AccelerationX);
        object.setDirection(Entity::Directions::Right);
    }
}

void HeroJumpState::onKeyReleased(Hero&, const sf::Event::KeyEvent&) noexcept
{

}
