#include "CoinShineState.hpp"

void CoinShineState::onSet(Coin& entity) noexcept
{
    entity.playShineAnimation();
}

void CoinShineState::update(Coin& entity, const sf::Time& dt) noexcept
{
    entity.updateShineAnimation(dt);
}

void CoinShineState::collision(Coin&, const Tile&, const CollisionSideType) noexcept
{

}

void CoinShineState::collision(Coin& entity, const Entity& collider, const CollisionSideType) noexcept
{
    if (!collider.hasComponent(Entity::ComponentType::Transparency))
    {
        if (collider.hasType(EntityType::Hero))
        {
            entity.destroy();
        }
    }
}

void CoinShineState::falling(Coin&) noexcept
{

}

void CoinShineState::onKeyPressed(Coin&, const sf::Event::KeyEvent&) noexcept
{

}

void CoinShineState::onKeyReleased(Coin&, const sf::Event::KeyEvent&) noexcept
{

}
