#include "MarioCollisionHandler.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{
    setTarget(GameObjectIdentifiers::Mario);
}

void MarioCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    const auto targetPosition = target->getGlobalPosition();
    const auto tilePosition = tilemap.getTileCenterPosition( tileIndex );

    if ( target->getVelocity().x > 0.0f )
    {
        const auto diffPosition = tilePosition.x - targetPosition.x;
        const auto intersectPosition = (32 ) + 16 - diffPosition;

        target->move( intersectPosition, 0.0f );
    }
    else
    {
        const auto diffPosition = targetPosition.x - tilePosition.x;
        const auto intersectPosition = target->getBounds().width - target->getBounds().width / 2.0f - diffPosition;

        target->move( intersectPosition, 0.0f );
    }

    target->setAcceleration({});
    target->setVelocity({});
}

void MarioCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    if (object->hasIdentifier(GameObjectIdentifiers::Goomba))
    {

    }
}
