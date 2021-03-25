#include "ItemActiveState.hpp"

#include "ItemPickupState.hpp"

void ItemActiveState::onSet(Item& entity) noexcept
{
    entity.setActiveAnimation();
}

void ItemActiveState::update(Item& entity, const sf::Time& dt) noexcept
{
    entity.updateActiveAnimation(dt);
}

void ItemActiveState::tileCollision(Item&, const Tile&, const CollisionSideType) noexcept
{

}

void ItemActiveState::entityCollision(Item& entity, const Entity&, const CollisionSideType) noexcept
{
    entity.setState<ItemPickupState>();
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

bool ItemActiveState::isJumping() const noexcept
{
    return false;
}

bool ItemActiveState::isFalling() const noexcept
{
    return false;
}
