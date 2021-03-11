#include "StandardCollisionHandler.hpp"

#include "TilemapView.hpp"

StandardCollisionHandler::StandardCollisionHandler(TilemapView& tilemapView) noexcept :
    CollisionHandler{tilemapView}
{
    setTargets({GameObjectIdentifiers::Mario, GameObjectIdentifiers::Goomba});
}

void StandardCollisionHandler::onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept
{
    const auto objectArea = object->getArea();
    const auto tileArea = mTilemapView.getTileArea(tileIndex);

    auto offsetPosition = objectArea.getWidth();

    if (objectArea.getCenter().getX() < tileArea.getCenter().getX())
    {
        offsetPosition = -offsetPosition;
    }
    else
    {
        offsetPosition = +offsetPosition;
    }

    const auto colliderPositionX = tileArea.getLeft();
    object->setPositionX(colliderPositionX + offsetPosition);
}

void StandardCollisionHandler::onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept
{
    const auto objectAArea = objectA->getArea();
    const auto objectBArea = objectB->getArea();

    auto offsetPosition = objectAArea.getWidth();

    if (objectA->isMovingRight())
    {
        offsetPosition = -offsetPosition;
    }
    else
    {
        offsetPosition = +offsetPosition;
    }

    const auto colliderPositionX = objectBArea.getLeft();
    objectA->setPositionX(colliderPositionX + offsetPosition);
}
