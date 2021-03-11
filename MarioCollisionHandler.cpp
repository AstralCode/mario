#include "MarioCollisionHandler.hpp"

#include "TilemapView.hpp"

MarioCollisionHandler::MarioCollisionHandler(TilemapView& tilemapView) noexcept :
    CollisionHandler{tilemapView}
{
    setTarget(GameObjectIdentifiers::Mario);
}

void MarioCollisionHandler::onTileCollision(GameObject*, const TileIndex&) noexcept
{

}

void MarioCollisionHandler::onObjectCollision(GameObject* objectA, GameObject*) noexcept
{
    if (objectA->hasIdentifier(GameObjectIdentifiers::Goomba))
    {

    }
}
