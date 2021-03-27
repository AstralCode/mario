#include "ItemPickupState.hpp"

void ItemPickupState::onSet(Item& entity) noexcept
{
    entity.setVelocityY(-Constants::World::Items::PickupVelocityY);
    entity.setComponent(Entity::ComponentType::Transparent);
    entity.setComponent(Entity::ComponentType::Movement);
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

void ItemPickupState::collision(Item&, const Tile&, const CollisionSideType) noexcept
{

}

void ItemPickupState::collision(Item&, const Hero&, const CollisionSideType) noexcept
{
}

void ItemPickupState::collision(Item&, const Enemy&, const CollisionSideType) noexcept
{
}

void ItemPickupState::collision(Item&, const Item&, const CollisionSideType) noexcept
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
