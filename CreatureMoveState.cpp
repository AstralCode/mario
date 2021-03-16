#include "CreatureMoveState.hpp"

#include "GameObject.hpp"

CreatureMoveState::CreatureMoveState(const SpritesetRegion& moveSpritesetRegion, const SpritesetRegion& deadSpritesetRegion) noexcept :
    mMoveAnimation{moveSpritesetRegion},
    mDeadSpritesetRegion{deadSpritesetRegion}
{

}

void CreatureMoveState::onSet(GameObject& object) noexcept
{
    object.setMaxVelocity({Constants::GameObjects::Creature::MaxVelocityX, Constants::GameObjects::Creature::MaxVelocityY});
    object.setAccelerationX(Constants::GameObjects::Creature::MaxVelocityX);
    object.setTextureArea(mMoveAnimation.getCurrentSpriteArea());

    mMoveAnimation.setDuration(sf::seconds(Constants::GameObjects::Creature::MoveAnimationDuration));
    mMoveAnimation.setRepeating(true);
    mMoveAnimation.play();
}

void CreatureMoveState::update(GameObject&, const sf::Time& fixedFrameTime) noexcept
{
    mMoveAnimation.update(fixedFrameTime);
}
