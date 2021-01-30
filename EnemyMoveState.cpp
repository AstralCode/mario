#include "EnemyMoveState.hpp"

#include "GameObject.hpp"

EnemyMoveState EnemyMoveState::mState;

EnemyMoveState* EnemyMoveState::getInstance()
{
    return &mState;
}

void EnemyMoveState::onSet(GameObject& object)
{
    mAnimation.setSpriteAtlasRegion(&object.getSpriteAtlas().getRegion("goomba_move"));
    mAnimation.setDuration(sf::seconds(0.25f));
    mAnimation.stop();
    mAnimation.play();

    object.setAcceleration(object.getMaxAcceleration());
}

void EnemyMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);

    object.setTextureArea(mAnimation.getCurrentSprite());
}
