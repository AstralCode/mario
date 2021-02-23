#include "MarioCollisionHandler.hpp"

#include <memory>

#include "GameObject.hpp"
#include "Tilemap.hpp"

MarioCollisionHandler::MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
    CollisionHandler{tilemap, spritesetContainer}
{

}

void MarioCollisionHandler::onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept
{
    auto& tilemap = getTilemap();

    const auto tileAttributes = tilemap.getTileAttributes(tileIndex);
    if (tileAttributes.has_value())
    {
        if (tileAttributes.value().isSet(TileAttributes::Solid))
        {
            sf::Vector2u leftTileIndex{};
            leftTileIndex.x = tileIndex.x - 1u;
            leftTileIndex.y = tileIndex.y - 0u;

            target->setPosition(tilemap.getTileCenterPosition(leftTileIndex));
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
