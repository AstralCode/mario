#include "Entity.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Sprite.hpp"

Entity::Entity() noexcept :
    mSprite{addItem<Sprite>()},
    mDirection{Directions::Right},
    mBoundsColor{sf::Color::Transparent},
    mIsBoundsVisible{false},
    mIsDestroyed{false}
{

}

void Entity::setTexture(const sf::Texture& texture) noexcept
{
    mSprite->setTexture(texture);
}

void Entity::setSpriteArea(const IntArea& area) noexcept
{
    mSprite->setSpriteArea(area);
}

void Entity::setBoundsColor(const sf::Color& color) noexcept
{
    mBoundsColor = color;
}

void Entity::setBoundsVisible(const bool visible) noexcept
{
    mIsBoundsVisible = visible;
}

void Entity::setDirection(const Directions direction) noexcept
{
    if (mDirection != direction)
    {
        mSprite->flip(Sprite::Orientations::Horizontal);

        mDirection = direction;
    }
}

void Entity::setAccelerationX(const float value) noexcept
{
    mAcceleration.setX(value);
}

void Entity::setAccelerationY(const float value) noexcept
{
    mAcceleration.setY(value);
}

void Entity::setVelocityX(const float value) noexcept
{
    mVelocity.setX(value);
}

void Entity::setVelocityY(const float value) noexcept
{
    mVelocity.setY(value);
}

const Entity::Directions& Entity::getDirection() const noexcept
{
    return mDirection;
}

const FloatPoint& Entity::getAcceleration() const noexcept
{
    return mAcceleration;
}

const FloatPoint& Entity::getVelocity() const noexcept
{
    return mVelocity;
}

FloatArea Entity::getLocalArea() const noexcept
{
    return mSprite->getLocalArea();
}

bool Entity::hasDirection(const Directions direction) const noexcept
{
    return mDirection == direction;
}

bool Entity::isBoundsVisible() const noexcept
{
    return mIsBoundsVisible;
}

void Entity::destroy() noexcept
{
    mIsDestroyed = true;
}

bool Entity::isDestroyed() const noexcept
{
    return mIsDestroyed;
}

void Entity::drawSelf(sf::RenderTarget& target, sf::RenderStates) const noexcept
{
    if (mIsBoundsVisible)
    {
        drawAreaBounds(target);
    }
}

void Entity::drawAreaBounds(sf::RenderTarget& target) const noexcept
{
    const auto area = getArea();

    sf::RectangleShape areaBounds{};
    areaBounds.setPosition(area.getLeft() + 1.0f, area.getTop() + 1.0f);
    areaBounds.setSize({area.getWidth() - 2.0f, area.getHeight() - 2.0f});
    areaBounds.setFillColor(sf::Color::Transparent);
    areaBounds.setOutlineColor(mBoundsColor);
    areaBounds.setOutlineThickness(1.0f);

    target.draw(areaBounds);
}
