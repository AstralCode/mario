#include "ItemPickupState.hpp"

void ItemPickupState::onSet(Item& entity) noexcept
{
    entity.setVelocityY(-Constants::World::Items::PickupVelocityY);
    entity.setAttribute(Entity::Attributes::Transparent);
    entity.setAttribute(Entity::Attributes::Movable);
    entity.setPickupAnimation();
}

void ItemPickupState::update(Item& entity, const sf::Time& dt) noexcept
{
    entity.updatePickupAnimation(dt);

    if (entity.getPickupTime() >= sf::seconds(Constants::World::Items::PickupAnimationEnd))
    {
        entity.destroy();
    }
}

void ItemPickupState::tileCollision(Item&, const Tile&, const CollisionSideType) noexcept
{

}

void ItemPickupState::entityCollision(Item&, const Entity&, const CollisionSideType) noexcept
{

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
