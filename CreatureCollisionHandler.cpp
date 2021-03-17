#include "CreatureCollisionHandler.hpp"

CreatureCollisionHandler::CreatureCollisionHandler() noexcept
{
	setTargets({GameObjectIdentifiers::Goomba});
}

void CreatureCollisionHandler::onTileCollision(GameObject* object, const Tile&) noexcept
{
    object->turnAround();
}

void CreatureCollisionHandler::onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept
{
    objectA->turnAround();
    objectB->turnAround();
}
