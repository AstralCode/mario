#include "CreatureCollisionHandler.hpp"

#include "TilemapView.hpp"

CreatureCollisionHandler::CreatureCollisionHandler(TilemapView& tilemapView) noexcept :
	CollisionHandler{tilemapView}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void CreatureCollisionHandler::onTileCollision(GameObject* object, const TileIndex&) noexcept
{
    object->turnAround();
}

void CreatureCollisionHandler::onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept
{
    objectA->turnAround();
    objectB->turnAround();
}
