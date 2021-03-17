#include "MarioCollisionHandler.hpp"

MarioCollisionHandler::MarioCollisionHandler() noexcept
{
    setTarget(GameObjectIdentifiers::Mario);
}

void MarioCollisionHandler::onTileCollision(GameObject*, const Tile&) noexcept
{

}

void MarioCollisionHandler::onObjectCollision(GameObject* objectA, GameObject*) noexcept
{
    if (objectA->hasIdentifier(GameObjectIdentifiers::Goomba))
    {

    }
}
