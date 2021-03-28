#include "ItemActiveState.hpp"

#include "ItemPickupState.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"

void ItemActiveState::onSet(Item& entity) noexcept
{
    entity.setActiveAnimation();
}

void ItemActiveState::update(Item& entity, const sf::Time& dt) noexcept
{
    entity.updateActiveAnimation(dt);
}

void ItemActiveState::collision(Item&, const Tile&, const CollisionSideType) noexcept
{

}

void ItemActiveState::collision(Item& entity, const Hero& hero, const CollisionSideType) noexcept
{
    if (!hero.hasComponent(Entity::ComponentType::Transparency))
    {
        entity.setState<ItemPickupState>();
    }
}

void ItemActiveState::collision(Item& entity, const Enemy& enemy, const CollisionSideType) noexcept
{
    if (!enemy.hasComponent(Entity::ComponentType::Transparency))
    {
        entity.setState<ItemPickupState>();
    }
}

void ItemActiveState::collision(Item&, const Item&, const CollisionSideType) noexcept
{

}

void ItemActiveState::falling(Item&) noexcept
{

}

void ItemActiveState::onKeyPressed(Item&, const sf::Event::KeyEvent&) noexcept
{

}

void ItemActiveState::onKeyReleased(Item&, const sf::Event::KeyEvent&) noexcept
{

}
