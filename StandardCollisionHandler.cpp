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

    const auto objectPosition = objectArea.getCenter();
    const auto tilePosition = tileArea.getCenter();

    auto colliderPosition = object->getPosition();

    if (objectPosition.getX() < tilePosition.getX() &&
        objectPosition.getY() > tileArea.getTop() )
    {
        colliderPosition.setX(tileArea.getLeft() - objectArea.getWidth());
        object->onTileLeftCollision(tileIndex);
    }
    else if (objectPosition.getY() > tileArea.getTop() &&
             objectPosition.getY() < tileArea.getBottom())
    {
        colliderPosition.setX(tileArea.getRight() + 1.0f);
        object->onTileRightCollision(tileIndex);
    }

    if (objectPosition.getY() < tilePosition.getY() &&
        objectPosition.getY() < tileArea.getTop())
    {
        colliderPosition.setY(tileArea.getTop() - objectArea.getHeight());
        object->onTileTopCollision(tileIndex);
    }
    else if(objectPosition.getY() > tileArea.getBottom())
    {
        colliderPosition.setY(tileArea.getBottom() - 1.0f);
        object->onTileBottomCollision(tileIndex);
    }

    object->setPosition(colliderPosition);
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

    const auto colliderPositionX = objectBArea.getLeft();
    objectA->setPositionX(colliderPositionX + offsetPosition);
}
