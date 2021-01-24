#include "GameObject.hpp"

GameObject::GameObject(GraphicsSpriteItem* sprite) :
    mSprite{sprite},
    mIsDestroyed{false}
{

}

void GameObject::setTexture(const sf::Texture& texture)
{
    mSprite->setTexture(texture);
}

void GameObject::setTextureArea(const sf::IntRect& area)
{
    mSprite->setTextureArea(area);
}

void GameObject::setDestroyed(const bool destroyed)
{
    mIsDestroyed = destroyed;
    mSprite->setToRemove(destroyed);
}

void GameObject::setWorldPosition(const sf::Vector2f& position)
{
    mSprite->setPosition(position);
}

void GameObject::update(const sf::Time& frameTime)
{
    
}

const sf::Vector2f& GameObject::getWorldPosition() const
{
    return mSprite->getGlobalPosition();
}

bool GameObject::hasCollision(const GameObject& object) const
{
    return mSprite->isIntersectsItem(*mSprite);
}

bool GameObject::isContainsPoint(const sf::Vector2f& point) const
{
    return mSprite->isContainsPoint(point);
}

bool GameObject::isDestroyed() const
{
    return mIsDestroyed;
}
