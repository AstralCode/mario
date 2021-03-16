#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"

MarioMoveState::MarioMoveState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset},
    mAnimation{spriteset.getRegion(MarioSpritesetRegions::Move)}
{

}

void MarioMoveState::onSet(GameObject&) noexcept
{
    mAnimation.setDuration(sf::seconds(Constants::GameObjects::Mario::MoveAnimationDuration));
    mAnimation.setRepeating(true);
}

void MarioMoveState::update(GameObject& object, const sf::Time& fixedFrameTime) noexcept
{
    mAnimation.update(fixedFrameTime);

    if (std::abs(object.getAcceleration().getX()) > 32.0f)
    {
        const bool sliding =
            object.hasDirection(GameObject::Directions::Left) && object.getVelocity().getX() > 0.0f ||
            object.hasDirection(GameObject::Directions::Right) && object.getVelocity().getX() < 0.0f;

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

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.moveLeft();
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.moveRight();
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
            object.moveRight();
        }
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            object.moveLeft();
        }
    }
}
