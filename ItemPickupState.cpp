#include "ItemPickupState.hpp"

void ItemPickupState::onSet(Item& entity) noexcept
{
    entity.setActiveAnimation();
}

void ItemPickupState::update(Item& entity, const sf::Time& dt) noexcept
{
    entity.updateActiveAnimation(dt);
}

void ItemPickupState::tileCollision(Item&, const Tile&, const CollisionSideType) noexcept
{

}

void ItemPickupState::entityCollision(Item& entity, const Entity&, const CollisionSideType) noexcept
{
    entity.destroy();
}

void ItemPickupState::falling(Item&) noexcept
{

}

void ItemPickupState::onKeyPressed(Item&, const sf::Event::KeyEvent&) noexcept
{

}

void ItemPickupState::onKeyReleased(Item&, const sf::Event::KeyEvent&) noexcept
{

}

bool ItemPickupState::isJumping() const noexcept
{
    return false;
}

bool ItemPickupState::isFalling() const noexcept
{
    return false;
}
