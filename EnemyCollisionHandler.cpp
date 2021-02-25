#include "EnemyCollisionHandler.hpp"

EnemyCollisionHandler::EnemyCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
	CollisionHandler{tilemap, spritesetContainer}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void EnemyCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    const auto targetArea = target->getArea();

    if (target->getVelocity().x > 0.0f)
    {
        const auto tilePosition = tilemap.getTileArea(tileIndex).getTopLeft();
        const auto offsetPosition = targetArea.getWidth() / 2.0f;

        target->setPositionX(tilePosition.x - offsetPosition);
        target->turnAround();
    }
    else
    {
        const auto tilePosition = tilemap.getTileArea(tileIndex).getTopRight();
        const auto offsetPosition = targetArea.getWidth() / 2.0f;

        target->setPositionX(tilePosition.x + offsetPosition);
        target->turnAround();
    }
}

void EnemyCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    const auto targetArea = target->getArea();
    const auto objectArea = object->getArea();

    if (target->getVelocity().x > 0.0f)
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

    if (object->getVelocity().x > 0.0f)
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
