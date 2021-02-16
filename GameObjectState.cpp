#include "GameObjectState.hpp"

#include "GameObject.hpp"
#include "Spriteset.hpp"

GameObjectState::GameObjectState(const Spriteset& spriteset) :
    mSpriteset{spriteset},
    mRemoved{false}
{

}

void GameObjectState::setAnimation(std::unique_ptr<Animation> animation)
{
    mAnimation = std::move(animation);
    mAnimation->stop();
    mAnimation->play();
}


void GameObjectState::onSet(GameObject&)
{

}

void GameObjectState::onUnset(GameObject&)
{

}

void GameObjectState::destroy()
{
    mRemoved = true;
}

void GameObjectState::update(GameObject& object, const sf::Time& frameTime)
{
    if (mAnimation)
    {
        mAnimation->update(frameTime);

        object.setTextureArea(mAnimation->getCurrentSprite());
    }

    updateSelf(object, frameTime);
}

void GameObjectState::onKeyPressed(GameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onKeyReleased(GameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onMouseClick(GameObject&, const sf::Event::MouseButtonEvent&)
{

}

void GameObjectState::onMouseEnter(GameObject&, const sf::Event::MouseMoveEvent&)
{

}

void GameObjectState::onMouseLeave(GameObject&, const sf::Event::MouseMoveEvent&)
{

}

void GameObjectState::onMouseOver(GameObject&, const sf::Event::MouseMoveEvent&)
{

}

const sf::IntRect& GameObjectState::getSprite(const std::string& spritesetRegionidentifier) const
{
    return mSpriteset.getRegion(spritesetRegionidentifier).getSprite(0);
}

bool GameObjectState::isWreck() const
{
    return true;
}

bool GameObjectState::isDestroyed() const
{
    return mRemoved && isWreck();
}

std::unique_ptr<Animation> GameObjectState::createAnimation(const std::string& spritesetRegionIdentifier) const
{
    return std::make_unique<Animation>(mSpriteset.getRegion(spritesetRegionIdentifier));
}

void GameObjectState::updateSelf(GameObject&, const sf::Time&)
{

}
