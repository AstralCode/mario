#include "EnemyCollisionHandler.hpp"

#include "GraphicsScene.hpp"

EnemyCollisionHandler::EnemyCollisionHandler(GraphicsScene& scene) noexcept :
	CollisionHandler{scene}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void EnemyCollisionHandler::onTileCollision(GameObject* target, const TileIndex& tileIndex) noexcept
{
    auto& tilemapView = getGraphicsScene().getTilemapView();

    const auto targetArea = target->getArea();

    if (target->getVelocity().getX() > 0.0f)
    {
        const auto tilePosition = tilemapView.getTileArea(tileIndex).getTopLeft();
        const auto offsetPosition = targetArea.getWidth() / 2.0f;

        target->setPositionX(tilePosition.getX() - offsetPosition);
        target->turnAround();
    }
    else
    {
        const auto tilePosition = tilemapView.getTileArea(tileIndex).getTopRight();
        const auto offsetPosition = targetArea.getWidth() / 2.0f;

        target->setPositionX(tilePosition.getX() + offsetPosition);
        target->turnAround();
    }
}

void EnemyCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    const auto targetArea = target->getArea();
    const auto objectArea = object->getArea();

    if (target->getVelocity().getX() > 0.0f)
    {
        const auto objectLeft = objectArea.getLeft();
        const auto offset = targetArea.getWidth() / 2.0f;

        target->setPositionX(objectLeft - offset);
        target->turnAround();
    }
    else
    {
        const auto objectRight = objectArea.getRight();
        const auto offset = targetArea.getWidth() / 2.0f;

        target->setPositionX(objectRight + offset);
        target->turnAround();
    }

    if (object->getVelocity().getX() > 0.0f)
    {
        const auto targetLeft = targetArea.getLeft();
        const auto offset = objectArea.getWidth() / 2.0f;

        object->setPositionX(targetLeft - offset);
        object->turnAround();
    }
    else
    {
        const auto targetRight = targetArea.getRight();
        const auto offset = objectArea.getWidth() / 2.0f;

        object->setPositionX(targetRight + offset);
        object->turnAround();
    }
}
