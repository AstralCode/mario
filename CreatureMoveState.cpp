#include "CreatureMoveState.hpp"

#include "GameObject.hpp"
#include "CreatureFallState.hpp"

CreatureMoveState::CreatureMoveState(const SpritesetRegion& moveSpritesetRegion) noexcept :
    mMoveAnimation{moveSpritesetRegion}
{

}

void CreatureMoveState::onSet(GameObject& object) noexcept
{
    object.setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
    object.setAccelerationX(Constants::World::Creature::AccelerationX);
    object.setAccelerationY(0.0f);

    mMoveAnimation.setDuration(sf::seconds(Constants::World::Creature::MoveAnimationDuration));
    mMoveAnimation.setRepeating(true);
    mMoveAnimation.play();
}

void CreatureMoveState::update(GameObject& object, const sf::Time& dt) noexcept
{
    mMoveAnimation.update(dt);
    object.setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void CreatureMoveState::onFalling(GameObject& object) noexcept
{
    object.setState<CreatureFallState>(mMoveAnimation.getSpritesetRegion());
}

void CreatureMoveState::onTileLeftCollision(GameObject& object, const Tile&) noexcept
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

void CreatureMoveState::onTileRightCollision(GameObject& object, const Tile&) noexcept
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

void CreatureMoveState::onObjectCollision(GameObject& objectA, GameObject& objectB) noexcept
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
