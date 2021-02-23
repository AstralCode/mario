#include "MarioCollisionHandler.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{
    setTarget(GameObjectIdentifiers::Mario);
}

void MarioCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    sf::Vector2u newTileIndex{tileIndex};
    newTileIndex.x += (target->getVelocity().x >= 0.0f) ? -1 : +1;

    target->setPosition(tilemap.getTileCenterPosition(newTileIndex));
    target->setAcceleration({});
    target->setVelocity({});
}

void MarioCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    if (object->hasIdentifier(GameObjectIdentifiers::Goomba))
    {

    }
}
