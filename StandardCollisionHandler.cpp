#include "StandardCollisionHandler.hpp"

StandardCollisionHandler::StandardCollisionHandler() noexcept
{
    setTargets({GameObjectIdentifiers::Mario, GameObjectIdentifiers::Goomba});
}

void StandardCollisionHandler::onTileCollision(GameObject* object, const Tile& tile) noexcept
{
    const auto objectArea = object->getArea();

    const auto objectPosition = objectArea.getCenter();
    const auto tilePosition = tile.area.getCenter();

    auto colliderPosition = object->getPosition();

    if (objectPosition.getX() < tilePosition.getX() &&
        objectPosition.getY() > tile.area.getTop())
    {
        colliderPosition.setX(tile.area.getLeft() - objectArea.getWidth());
        object->onTileLeftCollision(tile);
    }
    else if (objectPosition.getY() > tile.area.getTop() &&
             objectPosition.getY() < tile.area.getBottom())
    {
        colliderPosition.setX(tile.area.getRight() + 1.0f);
        object->onTileRightCollision(tile);
    }

    if (objectPosition.getY() < tilePosition.getY() &&
        objectPosition.getY() < tile.area.getTop())
    {
        colliderPosition.setY( tile.area.getTop() - objectArea.getHeight());
        object->onTileTopCollision(tile);
    }
    else if(objectPosition.getY() > tile.area.getBottom())
    {
        colliderPosition.setY(tile.area.getBottom() - 1.0f);
        object->onTileBottomCollision(tile);
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
