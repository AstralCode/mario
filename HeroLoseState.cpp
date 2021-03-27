#include "HeroLoseState.hpp"

void HeroLoseState::onSet(Hero& entity) noexcept
{
    entity.setComponent(Entity::ComponentType::Transparent);
    entity.unsetComponent(Entity::ComponentType::Movement);
    entity.setAccelerationX(0.0f);
    entity.setVelocityX(0.0f);
    entity.setAccelerationY(0.0f);
    entity.setVelocityY(0.0f);
    entity.setLoseSprite();
}

void HeroLoseState::update(Hero& entity, const sf::Time& dt) noexcept
{
    entity.updateLoseAnimation(dt);
    
    if (entity.getLoseTime() >= sf::seconds(Constants::World::Hero::LoseAnimationEnd))
    {
        entity.destroy();
    }
    else if (!entity.hasComponent(Entity::ComponentType::Movement))
    {
        if (entity.getLoseTime() >= sf::seconds(Constants::World::Hero::LoseAnimationStart))
        {
            entity.setComponent(Entity::ComponentType::Movement);
            entity.setVelocityY(-Constants::World::Hero::MaxVelocityY);
        }
    }
}

void HeroLoseState::collision(Hero&, const Tile&, const CollisionSideType) noexcept
{

}

void HeroLoseState::collision(Hero&, const Hero&, const CollisionSideType) noexcept
{

}

void HeroLoseState::collision(Hero&, const Enemy&, const CollisionSideType) noexcept
{

}

void HeroLoseState::collision(Hero&, const Item&, const CollisionSideType) noexcept
{

}

void HeroLoseState::falling(Hero&) noexcept
{

}

void HeroLoseState::onKeyPressed(Hero&, const sf::Event::KeyEvent&) noexcept
{

}

void HeroLoseState::onKeyReleased(Hero&, const sf::Event::KeyEvent&) noexcept
{

}

bool HeroLoseState::isJumping() const noexcept
{
    return false;
}

bool HeroLoseState::isFalling() const noexcept
{
    return false;
}
