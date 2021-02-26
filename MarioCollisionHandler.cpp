#include "MarioCollisionHandler.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{
    setTarget(GameObjectIdentifiers::Mario);
}

void MarioCollisionHandler::onTileCollision(GameObject* target, const TileIndex& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    const auto targetArea = target->getArea();
    const auto tileArea = tilemap.getTileArea(tileIndex);

    if (target->getVelocity().getX() > 0.0f)
    {
        //TileSide tileSide = tilemap.getTileSide(targetArea, tileIndex);

        const auto tilePosition = tileArea.getTopLeft();
        const auto offsetPosition = targetArea.getWidth() / 2.0f;

        target->setPositionX(tilePosition.getX() - offsetPosition);
        target->setAccelerationX(0.0f);
    }
    else
    {
        const auto tilePosition = tileArea.getTopRight();
        const auto offsetPosition = targetArea.getWidth() / 2.0f;

        target->setPositionX(tilePosition.getX() + offsetPosition);
        target->setAccelerationX(0.0f);
    }
}

void MarioCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    if (object->hasIdentifier(GameObjectIdentifiers::Goomba))
    {
        static_cast<void*>(target);
    }
}
