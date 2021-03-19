#include "CreatureFallState.hpp"

#include "GameObject.hpp"
#include "CreatureMoveState.hpp"

CreatureFallState::CreatureFallState(const SpritesetRegion& moveSpritesetRegion) noexcept :
    mMoveSpritesetRegion{moveSpritesetRegion}
{

}

void CreatureFallState::onSet(GameObject& object) noexcept
{
    object.setAccelerationX(0.0f);
    object.setAccelerationY(1500.0f);
}

void CreatureFallState::update(GameObject&, const sf::Time&) noexcept
{

}

void CreatureFallState::onTileLeftCollision(GameObject& object, const Tile&) noexcept
{
    if (object.hasDirection(GameObjectDirections::Right))
    {
        object.setDirection(GameObjectDirections::Left);
    }
    else
    {
        object.setDirection(GameObjectDirections::Right);
    }

    object.setVelocityX(-object.getVelocity().getX());
}

void CreatureFallState::onTileRightCollision(GameObject& object, const Tile&) noexcept
{
    if (object.hasDirection(GameObjectDirections::Right))
    {
        object.setDirection(GameObjectDirections::Left);
    }
    else
    {
        object.setDirection(GameObjectDirections::Right);
    }

    object.setVelocityX(-object.getVelocity().getX());
}

void CreatureFallState::onTileTopCollision(GameObject& object, const Tile&) noexcept
{
    object.setState<CreatureMoveState>(mMoveSpritesetRegion);
}

void CreatureFallState::onObjectCollision(GameObject& objectA, GameObject& objectB) noexcept
{
    if (objectA.hasDirection(GameObjectDirections::Right))
    {
        objectA.setDirection(GameObjectDirections::Left);
        objectB.setDirection(GameObjectDirections::Right);
    }
    else
    {
        objectA.setDirection(GameObjectDirections::Right);
        objectB.setDirection(GameObjectDirections::Left);
    }

    objectA.setVelocityX(-objectA.getVelocity().getX());
    objectB.setVelocityX(-objectB.getVelocity().getX());
}

bool CreatureFallState::isJumping() const noexcept
{
    return false;
}

bool CreatureFallState::isFalling() const noexcept
{
    return true;
}
