#include "GameObject.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "Sprite.hpp"

GameObject::GameObject(const GameObjectIdentifiers identifier) noexcept :
	mIdentifier{identifier},
	mSprite{addItem<Sprite>()},
	mDirection{GameObjectDirections::Right},
	mAreaBoundsColor{sf::Color::Red},
	mAreaBoundsVisible{false},
	mMouseOver{false}
{
	
}

void GameObject::setTexture(const sf::Texture& texture) noexcept
{
	mSprite->setTexture(texture);
}

void GameObject::setSpriteArea(const IntArea& area) noexcept
{
	mSprite->setSpriteArea(area);
}

void GameObject::setAreaBoundsVisible(const bool visible) noexcept
{
	mAreaBoundsVisible = visible;
}

void GameObject::setAreaBoundsColor(const sf::Color& color) noexcept
{
	mAreaBoundsColor = color;
}

void GameObject::setAccelerationX(const float value) noexcept
{
	mAcceleration.setX(value);
}

void GameObject::setAccelerationY(const float value) noexcept
{
	mAcceleration.setY(value);
}

void GameObject::setVelocityX(const float value) noexcept
{
	if (hasDirection(GameObjectDirections::Right))
	{
		mVelocity.setX(std::min(value, +mMaxVelocity.getX()));
	}
	else
	{
		mVelocity.setX(std::max(value, -mMaxVelocity.getX()));
	}
}

void GameObject::setVelocityY(const float value) noexcept
{
	mVelocity.setY(std::min(value, mMaxVelocity.getY()));
}

void GameObject::setMaxVelocityX(const float value) noexcept
{
	mMaxVelocity.setX(value);
}

void GameObject::setMaxVelocityY(const float value) noexcept
{
	mMaxVelocity.setY(value);
}

void GameObject::setDirection(const GameObjectDirections direction) noexcept
{
	if (direction != mDirection)
	{
		mDirection = direction;
		mSprite->flip(Sprite::Orientations::Horizontal);
	}
}

void GameObject::destroy() noexcept
{
	mState->destroy();
}

void GameObject::onTileTopCollision(const Tile& tile) noexcept
{
	mState->onTileTopCollision(*this, tile);
}

void GameObject::onTileBottomCollision(const Tile& tile) noexcept
{
	mState->onTileBottomCollision(*this, tile);
}

void GameObject::onTileLeftCollision(const Tile& tile) noexcept
{
	mState->onTileLeftCollision(*this, tile);
}

void GameObject::onTileRightCollision(const Tile& tile) noexcept
{
	mState->onTileRightCollision(*this, tile);
}

void GameObject::onObjectCollision(GameObject& object) noexcept
{
	mState->onObjectCollision(*this, object);
}

void GameObject::onFalling() noexcept
{
	mState->onFalling(*this);
}

void GameObject::update(const sf::Time& dt) noexcept
{
	mState->update(*this, dt);

	if (mState->isDestroyed())
	{
		remove();
	}
}

GameObjectIdentifiers GameObject::getIdentifier() const noexcept
{
	return mIdentifier;
}

const FloatPoint& GameObject::getMaxVelocity() const noexcept
{
	return mMaxVelocity;
}

const FloatPoint& GameObject::getVelocity() const noexcept
{
	return mVelocity;
}

FloatArea GameObject::getLocalArea() const noexcept
{
	return mSprite->getLocalArea();
}

GameObjectDirections GameObject::getDirection() const noexcept
{
	return mDirection;
}

bool GameObject::hasIdentifier(const GameObjectIdentifiers identifier) const noexcept
{
	return mIdentifier == identifier;
}

bool GameObject::isJumping() const noexcept
{
	return mState->isJumping();
}

bool GameObject::hasDirection(const GameObjectDirections direction) const noexcept
{
	return mDirection == direction;
}

const FloatPoint& GameObject::getAcceleration() const noexcept
{
	return mAcceleration;
}

bool GameObject::isAreaBoundsVisible() const noexcept
{
	return mAreaBoundsVisible;
}

bool GameObject::isContainsPoint(const FloatPoint& point) const noexcept
{
	return mSprite->isContainsPoint(point);
}

bool GameObject::isDestroyed() const noexcept
{
	return mState->isDestroyed();
}

void GameObject::drawSelf(sf::RenderTarget& target, sf::RenderStates) const noexcept
{
	if (mAreaBoundsVisible)
	{
		drawAreaBounds(target);
	}
}

void GameObject::receiveEventsSelf(const sf::Event& event) noexcept
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		mState->onKeyPressed(*this, event.key);
		break;

	case sf::Event::KeyReleased:
		mState->onKeyReleased(*this, event.key);
		break;

	case sf::Event::MouseButtonPressed:
		if (isContainsPoint({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
		{
			mState->onMouseClick(*this, event.mouseButton);
		}
		break;

	case sf::Event::MouseMoved:
	{
		const bool mouseOver = isContainsPoint({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)});

		if (mouseOver)
		{
			if (mMouseOver)
			{
				mState->onMouseOver(*this, event.mouseMove);
			}
			else
			{
				mState->onMouseEnter(*this, event.mouseMove);
				mState->onMouseOver(*this, event.mouseMove);
				mMouseOver = true;
			}
		}
		else
		{
			if (mMouseOver)
			{
				mState->onMouseLeave(*this, event.mouseMove);
				mMouseOver = false;
			}
		}
		break;
	}

	default:
		break;
	}
}

void GameObject::drawAreaBounds(sf::RenderTarget& target) const noexcept
{
	const auto area = getArea();

	sf::RectangleShape areaBounds{};
	areaBounds.setPosition(area.getLeft() + 1.0f, area.getTop() + 1.0f);
	areaBounds.setSize({area.getWidth() - 2.0f, area.getHeight() - 2.0f});
	areaBounds.setFillColor(sf::Color::Transparent);
	areaBounds.setOutlineColor(mAreaBoundsColor);
	areaBounds.setOutlineThickness(1.0f);

	target.draw(areaBounds);
}
