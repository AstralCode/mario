#include "CoinActiveState.hpp"

void CoinActiveState::onSet(Coin& entity) noexcept
{
    entity.playActiveAnimation();
}

void CoinActiveState::update(Coin& entity, const sf::Time& dt) noexcept
{
    entity.updateActiveAnimation(dt);
}

void CoinActiveState::collision(Coin&, const Tile&, const CollisionSideType) noexcept
{

}

void CoinActiveState::collision(Coin& entity, const Entity& collider, const CollisionSideType) noexcept
{
    if (!collider.hasComponent(Entity::ComponentType::Transparency))
    {
        if (collider.hasType(EntityType::Hero))
        {
            entity.destroy();
        }
    }
}

void CoinActiveState::falling(Coin&) noexcept
{

}

void CoinActiveState::onKeyPressed(Coin&, const sf::Event::KeyEvent&) noexcept
{

}

void CoinActiveState::onKeyReleased(Coin&, const sf::Event::KeyEvent&) noexcept
{

}
