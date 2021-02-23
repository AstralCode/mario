#include "EnemyCollisionHandler.hpp"

EnemyCollisionHandler::EnemyCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
	CollisionHandler{tilemap, spritesetContainer}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void EnemyCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    target->turnAround();
}

void EnemyCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{
    target->turnAround();
    object->turnAround();
}
