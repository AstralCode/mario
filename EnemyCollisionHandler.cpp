#include "EnemyCollisionHandler.hpp"

EnemyCollisionHandler::EnemyCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
	CollisionHandler{tilemap, spritesetContainer}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void EnemyCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
	auto& tilemap = getTilemap();

    sf::Vector2u newTileIndex{tileIndex};
    newTileIndex.x += (target->getVelocity().x >= 0.0f) ? -1 : +1;

    target->setPosition(tilemap.getTileCenterPosition(newTileIndex));
    target->setVelocity({});
    target->turnAround();
}

void EnemyCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
{

}
