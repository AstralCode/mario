#include "StandardCollisionHandler.hpp"

#include "TilemapView.hpp"

StandardCollisionHandler::StandardCollisionHandler(TilemapView& tilemapView) noexcept :
    CollisionHandler{tilemapView}
{
    setTargets({GameObjectIdentifiers::Mario, GameObjectIdentifiers::Goomba});
}

void StandardCollisionHandler::onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept
{
    auto offsetPosition = std::ceil(object->getArea().getWidth());
    auto colliderPositionX{0.0f};

    if (object->getArea().getCenter().getX() < mTilemapView.getTileArea(tileIndex).getCenter().getX())
    {
        offsetPosition = -offsetPosition;
        colliderPositionX = mTilemapView.getTileArea(tileIndex).getLeft();
    }
    else
    {
        offsetPosition = +offsetPosition;
        colliderPositionX = mTilemapView.getTileArea(tileIndex).getRight();
    }

    object->setPositionX(colliderPositionX + offsetPosition);
}

void StandardCollisionHandler::onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept
{
    auto offsetPosition = std::ceil(objectA->getArea().getWidth());
    auto colliderPositionX{0.0f};

    if (objectA->isMovingRight())
    {
        offsetPosition = -offsetPosition;
        colliderPositionX = objectB->getArea().getLeft();
    }
    else
    {
        colliderPositionX = objectB->getArea().getRight();
    }

    objectA->setPositionX(colliderPositionX + offsetPosition);
}
