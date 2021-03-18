#include "CreatureMoveState.hpp"

#include "GameObject.hpp"

CreatureMoveState::CreatureMoveState(const SpritesetRegion& moveSpritesetRegion, const SpritesetRegion& deadSpritesetRegion) noexcept :
    mMoveAnimation{moveSpritesetRegion},
    mDeadSpritesetRegion{deadSpritesetRegion}
{

}

void CreatureMoveState::onSet(GameObject& object) noexcept
{
    object.setTextureArea(mMoveAnimation.getCurrentSpriteArea());
    object.setAccelerationX(Constants::GameObjects::Creature::AccelerationX);

    mMoveAnimation.setDuration(sf::seconds(Constants::GameObjects::Creature::MoveAnimationDuration));
    mMoveAnimation.setRepeating(true);
    mMoveAnimation.play();
}

void CreatureMoveState::update(GameObject& object, const sf::Time& dt) noexcept
{
    mMoveAnimation.update(dt);
    object.setTextureArea(mMoveAnimation.getCurrentSpriteArea());
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
