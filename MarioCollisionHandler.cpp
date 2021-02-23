#include "MarioCollisionHandler.hpp"

#include <memory>

#include "GameObject.hpp"
#include "Tilemap.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{

}

void MarioCollisionHandler::onTileCollision(GameObject* target, const unsigned int tileIdentifier) noexcept
{
    const auto tileAttributes = getTilemap().getTileAttributes(tileIdentifier);
    if (tileAttributes.has_value())
    {
        if (tileAttributes.value().isSet(TileAttributes::Solid))
        {
            target->destroy();
        }
    }
}

void MarioCollisionHandler::onObjectCollision(GameObject* target, GameObject* object) noexcept
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
