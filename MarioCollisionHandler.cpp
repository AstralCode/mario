#include "MarioCollisionHandler.hpp"

#include "MathCalculator.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{
    setTarget(GameObjectIdentifiers::Mario);
}

void MarioCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    const auto targetBounds = target->getBounds();

    if (target->getVelocity().x > 0.0f)
    {
        const auto tilePosition = tilemap.getTileTopLeftPosition(tileIndex);
        const auto offsetPosition = targetBounds.width / 2.0f;

        target->setPositionX(tilePosition.x - offsetPosition);
        target->setAccelerationX(0.0f);
    }
    else
    {
        const auto tilePosition = tilemap.getTileTopRightPosition(tileIndex);
        const auto offsetPosition = targetBounds.width / 2.0f;

        target->setPositionX(tilePosition.x + offsetPosition);
        target->setAccelerationX(0.0f);
    }
}

void MarioCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    if (object->hasIdentifier(GameObjectIdentifiers::Goomba))
    {

    }
}
