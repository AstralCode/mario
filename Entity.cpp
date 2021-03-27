#include "Entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "Sprite.hpp"

Entity::Entity() noexcept :
    mSprite{addItem<Sprite>()},
    mDirection{Directions::Right},
    mBoundsColor{sf::Color::Transparent},
    mIsBoundsVisible{false},
    mIsDestroyed{false}
{

}

FloatPoint Entity::centerOrigin(const Entity& entity) noexcept
{
    const auto origin = entity.getOrigin();
    auto size = entity.getLocalArea();

    return {origin.getX() + size.getWidth() / 2.0f, origin.getY() + size.getHeight() / 2.0f};
}

void Entity::setComponent(const ComponentType component) noexcept
{
    mComponents.set(component);
}

void Entity::unsetComponent(const ComponentType component) noexcept
{
    mComponents.unset(component);
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

bool Entity::hasComponent(const ComponentType component) const noexcept
{
    return mComponents.isSet(component);
}

const Entity::Components& Entity::getComponents() const noexcept
{
    return mComponents;
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
    GraphicsItem::remove();
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

    sf::RectangleShape bounds{};
    bounds.setPosition(area.getLeft() + 1.0f, area.getTop() + 1.0f);
    bounds.setSize({area.getWidth() - 2.0f, area.getHeight() - 2.0f});
    bounds.setFillColor(sf::Color::Transparent);
    bounds.setOutlineColor(mBoundsColor);
    bounds.setOutlineThickness(1.0f);

    target.draw(bounds);
}
