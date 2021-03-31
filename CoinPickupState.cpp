#include "CoinPickupState.hpp"

void CoinPickupState::onSet(Coin& entity) noexcept
{
    entity.setVelocityY(-Constants::World::Tilemap::TileSize * 15.0f);
    entity.setComponent(Entity::ComponentType::Transparency);
    entity.setComponent(Entity::ComponentType::Movement);
    entity.setComponent(Entity::ComponentType::Mass);
    entity.playPickupAnimation();
}

void CoinPickupState::update(Coin& entity, const sf::Time& dt) noexcept
{
    entity.updatePickupAnimation(dt);

    if (entity.getPickupTime() >= sf::seconds(0.5f))
    {
        entity.destroy();
    }
}

void CoinPickupState::collision(Coin&, const Tile&, const CollisionSideType) noexcept
{

}

void CoinPickupState::collision(Coin&, const Entity&, const CollisionSideType) noexcept
{

}

void CoinPickupState::falling(Coin&) noexcept
{

}

void CoinPickupState::onKeyPressed(Coin&, const sf::Event::KeyEvent&) noexcept
{

}

void CoinPickupState::onKeyReleased(Coin&, const sf::Event::KeyEvent&) noexcept
{

}
