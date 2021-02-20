#include "MarioCollisionHandler.hpp"

#include <memory>

#include "GameObject.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{

}

void MarioCollisionHandler::onCollision(GameObject* target, GameObject* object) noexcept
{
    if (object->hasIdentifier(GameObjectIdentifiers::Goomba))
    {
        target->destroy();
    }
}

GameObjectIdentifiers MarioCollisionHandler::getTarget() const noexcept
{
    return GameObjectIdentifiers::Mario;
}
