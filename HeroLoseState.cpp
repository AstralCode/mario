#include "HeroLoseState.hpp"

void HeroLoseState::onSet(Hero& entity) noexcept
{
    entity.setTrait(Entity::TraitType::Transparent);
    entity.unsetTrait(Entity::TraitType::Movable);
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
    else if (!entity.hasTrait(Entity::TraitType::Movable))
    {
        if (entity.getLoseTime() >= sf::seconds(Constants::World::Hero::LoseAnimationStart))
        {
            entity.setTrait(Entity::TraitType::Movable);
            entity.setVelocityY(-Constants::World::Hero::MaxVelocityY);
        }
    }
}

void HeroLoseState::tileCollision(Hero&, const Tile&, const CollisionSideType) noexcept
{

}

void HeroLoseState::entityCollision(Hero&, const Entity&, const CollisionSideType) noexcept
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
