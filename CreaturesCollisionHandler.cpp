#include "CreaturesCollisionHandler.hpp"

#include "TilemapView.hpp"

CreaturesCollisionHandler::CreaturesCollisionHandler(TilemapView& tilemapView) noexcept :
	CollisionHandler{tilemapView}
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void CreaturesCollisionHandler::onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept
{
    object->turnAround();
}

void CreaturesCollisionHandler::onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept
{
    objectA->turnAround();
    objectB->turnAround();
}
