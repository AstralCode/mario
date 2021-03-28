#include "HeroMoveState.hpp"

#include "HeroStandState.hpp"
#include "HeroFallState.hpp"
#include "HeroJumpState.hpp"
#include "HeroLoseState.hpp"
#include "Enemy.hpp"

void HeroMoveState::onSet(Hero& entity) noexcept
{
    if (sf::Keyboard::isKeyPressed(Constants::World::Hero::Left) ||
        sf::Keyboard::isKeyPressed(Constants::World::Hero::Right))
    {
        entity.setAccelerationX(Constants::World::Hero::AccelerationX);
    }
    else
    {
        entity.setAccelerationX(0.0f);
    }

    entity.setMoveAnimation();
}

void HeroMoveState::update(Hero& entity, const sf::Time& dt) noexcept
{
    entity.updateMoveAnimation(dt);

    if (entity.getAcceleration().getX() > 0.0f)
    {
        if (entity.getVelocity().getX() > Constants::World::Hero::StopVelocityX)
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
    else if (std::fabs(entity.getVelocity().getX()) < Constants::World::Hero::StopVelocityX)
    {
        entity.setState<HeroStandState>();
    }
}

void HeroMoveState::collision(Hero&, const Tile&, const CollisionSideType) noexcept
{

}

void HeroMoveState::collision(Hero&, const Hero&, const CollisionSideType) noexcept
{

}

void HeroMoveState::collision(Hero& entity, const Enemy& enemy, const CollisionSideType) noexcept
{
    if (!enemy.hasComponent(Entity::ComponentType::Transparency))
    {
        entity.setState<HeroLoseState>();
    }
}

void HeroMoveState::collision(Hero&, const Item&, const CollisionSideType) noexcept
{

}

void HeroMoveState::falling(Hero& entity) noexcept
{
    entity.setState<HeroFallState>();
}

void HeroMoveState::onKeyPressed(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept
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
    else if (keyEvent.code == Constants::World::Hero::Up)
    {
        entity.setJumpVelocity(Constants::World::Hero::MaxVelocityY);
        entity.setState<HeroJumpState>();
    }
}

void HeroMoveState::onKeyReleased(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Hero::Left ||
        keyEvent.code == Constants::World::Hero::Right)
    {
        entity.setAccelerationX(0.0f);
    }

    if (keyEvent.code == Constants::World::Hero::Left)
    {
        if (sf::Keyboard::isKeyPressed(Constants::World::Hero::Right))
        {
            entity.setAccelerationX(Constants::World::Hero::AccelerationX);
            entity.setDirection(Entity::Directions::Right);
        }
    }
    else if (keyEvent.code == Constants::World::Hero::Right)
    {
        if (sf::Keyboard::isKeyPressed(Constants::World::Hero::Left))
        {
            entity.setAccelerationX(Constants::World::Hero::AccelerationX);
            entity.setDirection(Entity::Directions::Left);
        }
    }
}
