#include "ItemActiveState.hpp"

void ItemActiveState::onSet(Item& entity) noexcept
{
    entity.setActiveAnimation();
}

void ItemActiveState::update(Item& entity, const sf::Time& dt) noexcept
{
    entity.updateActiveAnimation(dt);
}

void ItemActiveState::tileCollision(Item&, const Tile&, const Sides) noexcept
{

}

void ItemActiveState::entityCollision(Item& entity, const Entity&, const Sides) noexcept
{
    entity.destroy();
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
