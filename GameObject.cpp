#include "GameObject.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "Sprite.hpp"

GameObject::GameObject(const GameObjectIdentifiers identifier) noexcept :
	mIdentifier{identifier},
	mSprite{addItem<Sprite>()},
	mDirection{Directions::Right},
	mAreaBoundsColor{sf::Color::Red},
	mAreaBoundsVisible{false},
	mMouseOver{false}
{
	
}

void GameObject::setState(std::unique_ptr<GameObjectState> state) noexcept
{
	if (mState)
	{
		mState->onUnset(*this);
	}

	mState = std::move(state);
	mState->onSet(*this);
}

void GameObject::setTexture(const sf::Texture& texture) noexcept
{
	mSprite->setTexture(texture);
}

void GameObject::setTextureArea(const IntArea& area) noexcept
{
	mSprite->setTextureArea(area);
}

void GameObject::setMaxAcceleration(const FloatPoint& acceleration) noexcept
{
	mMaxAcceleration = acceleration;
}

void GameObject::setMaxVelocity(const FloatPoint& velocity) noexcept
{
	mMaxVelocity = velocity;
}

void GameObject::setAcceleration(const FloatPoint& acceleration) noexcept
{
	switch (mDirection)
	{
	case Directions::Right:
		mAcceleration.setX(std::min(+acceleration.getX(), +mMaxAcceleration.getX()));
		mAcceleration.setY(std::min(+acceleration.getY(), +mMaxAcceleration.getY()));
		break;
	case Directions::Left:
		mAcceleration.setX(std::max(-acceleration.getX(), -mMaxAcceleration.getX()));
		mAcceleration.setY(std::max(-acceleration.getY(), -mMaxAcceleration.getY()));
		break;
	default:
		break;
	}
	mAcceleration = acceleration;
}

void GameObject::setAccelerationX(const float value) noexcept
{
	setAcceleration({value, mAcceleration.getY()});
}

void GameObject::setAccelerationY(const float value) noexcept
{
	setAcceleration({mAcceleration.getX(), value});
}

void GameObject::setVelocity(const FloatPoint& velocity) noexcept
{
	switch (mDirection)
	{
	case Directions::Right:
		mVelocity.setX(std::min(velocity.getX(), +mMaxVelocity.getX()));
		mVelocity.setY(std::min(velocity.getY(), +mMaxVelocity.getY()));
		break;
	case Directions::Left:
		mVelocity.setX(std::max(velocity.getX(), -mMaxVelocity.getX()));
		mVelocity.setY(std::max(velocity.getY(), -mMaxVelocity.getY()));
		break;
	default:
		break;
	}	
}

void GameObject::setVelocityX(const float value) noexcept
{
	setVelocity({value, mVelocity.getY()});
}

void GameObject::setVelocityY(const float value) noexcept
{
	setVelocity({mVelocity.getX(), value});
}

void GameObject::setAreaBoundsVisible(const bool visible) noexcept
{
	mAreaBoundsVisible = visible;
}

void GameObject::setAreaBoundsColor(const sf::Color& color) noexcept
{
	mAreaBoundsColor = color;
}

void GameObject::accelerateVelocity(const FloatPoint& acceleration) noexcept
{
	setVelocity({mVelocity.getX() + acceleration.getX(), mVelocity.getY() + acceleration.getY()});
}

void GameObject::setDirection(const Directions direction) noexcept
{
	if (direction != mDirection)
	{
		mDirection = direction;

		mSprite->flip(Sprite::Orientations::Horizontal);
	}
}

void GameObject::turnAround() noexcept
{
	if (mDirection == Directions::Right)
	{
		moveLeft();
		setVelocity(-getVelocity());
	}
	else
	{
		moveRight();
		setVelocity(-getVelocity());
	}
}

void GameObject::destroy() noexcept
{
	mState->destroy();
}

void GameObject::moveLeft() noexcept
{
	setDirection(Directions::Left);
	setAcceleration(-getMaxAcceleration());
}

void GameObject::moveRight() noexcept
{
	setDirection(Directions::Right);
	setAcceleration(getMaxAcceleration());
}

void GameObject::onObjectCollision(GameObject& object) noexcept
{
	mState->onCollision(object);
}

void GameObject::update(const sf::Time& fixedFrameTime) noexcept
{
	mState->update(*this, fixedFrameTime);

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

GameObject::Directions GameObject::getDirection() const noexcept
{
	return mDirection;
}

bool GameObject::hasIdentifier(const GameObjectIdentifiers identifier) const noexcept
{
	return mIdentifier == identifier;
}

bool GameObject::isMoving() const noexcept
{
	return std::abs(mVelocity.getX()) > 0.0f;
}

bool GameObject::isMovingLeft() const noexcept
{
	return mVelocity.getX() < 0.0f;
}

bool GameObject::isMovingRight() const noexcept
{
	return mVelocity.getX() > 0.0f;
}

bool GameObject::hasDirection(const Directions direction) const noexcept
{
	return mDirection == direction;
}

const FloatPoint& GameObject::getMaxAcceleration() const noexcept
{
	return mMaxAcceleration;
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

FloatArea GameObject::getArea() const noexcept
{
	return mSprite->getArea();
}
