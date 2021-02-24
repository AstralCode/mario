#include "EnemyCollisionHandler.hpp"

EnemyCollisionHandler::EnemyCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
	CollisionHandler{tilemap, spritesetContainer}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void EnemyCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    const auto targetBounds = target->getBounds();

    if (target->getVelocity().x > 0.0f)
    {
        const auto tilePosition = tilemap.getTileTopLeftPosition(tileIndex);
        const auto offsetPosition = targetBounds.width / 2.0f;

        target->setPositionX(tilePosition.x - offsetPosition);
        target->turnAround();
    }
    else
    {
        const auto tilePosition = tilemap.getTileTopRightPosition(tileIndex);
        const auto offsetPosition = targetBounds.width / 2.0f;

        target->setPositionX(tilePosition.x + offsetPosition);
        target->turnAround();
    }
}

void EnemyCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    const auto targetBounds = target->getBounds();
    const auto objectBounds = object->getBounds();

    if (target->getVelocity().x > 0.0f)
    {
        const auto objectPosition = objectBounds.left;
        const auto offsetPosition = targetBounds.width / 2.0f;

        target->setPositionX(objectPosition - offsetPosition);
        target->turnAround();
    }
    else
    {
        const auto objectPosition = objectBounds.left + objectBounds.width;
        const auto offsetPosition = targetBounds.width / 2.0f;

        target->setPositionX(objectPosition + offsetPosition);
        target->turnAround();
    }

    if (object->getVelocity().x > 0.0f)
    {
        const auto targetPosition = targetBounds.left;
        const auto offsetPosition = objectBounds.width / 2.0f;

        object->setPositionX(targetPosition - offsetPosition);
        object->turnAround();
    }
    else
    {
        const auto targetPosition = targetBounds.left + targetBounds.width;
        const auto offsetPosition = objectBounds.width / 2.0f;

        object->setPositionX(targetPosition + offsetPosition);
        object->turnAround();
    }
}
