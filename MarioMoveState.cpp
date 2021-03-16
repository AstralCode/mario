#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"

MarioMoveState::MarioMoveState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset},
    mMoveAnimation{spriteset.getRegion(MarioSpritesetRegions::Move)}
{

}

void MarioMoveState::onSet(GameObject& object) noexcept
{
    object.setTextureArea(mMoveAnimation.getCurrentSpriteArea());

    mMoveAnimation.setDuration(sf::seconds(Constants::GameObjects::Mario::MoveAnimationDuration));
    mMoveAnimation.setRepeating(true);
    mMoveAnimation.play();
}

void MarioMoveState::update(GameObject& object, const sf::Time& fixedFrameTime) noexcept
{
    mMoveAnimation.update(fixedFrameTime);

    if (std::abs(object.getAcceleration().getX()) > 32.0f)
    {
        const bool sliding =
            object.hasDirection(GameObjectDirections::Left) && object.getVelocity().getX() > 0.0f ||
            object.hasDirection(GameObjectDirections::Right) && object.getVelocity().getX() < 0.0f;

        if (sliding)
        {
            object.setTextureArea(mSpriteset.getRegion(MarioSpritesetRegions::Slide).getSpriteArea(0));
        }

    }
    else if (std::abs(object.getVelocity().getX()) < 1.0f)
    {
        object.setState(std::make_unique<MarioStandState>(mSpriteset));
    }
}

void MarioMoveState::setDirection(GameObject& object, const GameObjectDirections direction) noexcept
{
    object.setDirection(direction);
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.setDirection(GameObjectDirections::Left);
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.setDirection(GameObjectDirections::Right);
    }
}

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q || keyEvent.code == sf::Keyboard::E)
    {
        object.setAcceleration({});
    }

    if (keyEvent.code == sf::Keyboard::Q)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            object.setDirection(GameObjectDirections::Right);
        }
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            object.setDirection(GameObjectDirections::Left);
        }
    }
}
