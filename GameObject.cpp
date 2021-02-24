#include "GameObject.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "GraphicsSpriteItem.hpp"

GameObject::GameObject(const GameObjectIdentifiers identifier) :
	mIdentifier{identifier},
	mSprite{addItem<GraphicsSpriteItem>()},
	mDirection{Directions::Right},
	mBoundsColor{sf::Color::Red},
	mBoundsVisible{false},
	mMouseOver{false}
{

}

void GameObject::setState(std::unique_ptr<GameObjectState> state)
{
	if (mState)
	{
		mState->onUnset(*this);
	}

	mState = std::move(state);
	mState->onSet(*this);
}

void GameObject::setPositionX(const float x)
{
	setPosition(x, getPosition().y);
}

void GameObject::setPositionY(const float y)
{
	setPosition(getPosition().x, y);
}

void GameObject::setTexture(const sf::Texture& texture)
{
	mSprite->setTexture(texture);
}

void GameObject::setTextureArea(const SpriteArea& spriteArea)
{
	mSprite->setTextureArea(spriteArea.getArea());

	setOrigin(spriteArea.getOrigin());
}

void GameObject::setMaxAcceleration(const sf::Vector2f& acceleration)
{
	mMaxAcceleration = acceleration;
}

void GameObject::setMaxVelocity(const sf::Vector2f& velocity)
{
	mMaxVelocity = velocity;
}

void GameObject::setAcceleration(const sf::Vector2f& acceleration)
{
	switch (mDirection)
	{
	case Directions::Right:
		mAcceleration.x = std::min(+acceleration.x, +mMaxAcceleration.x);
		mAcceleration.y = std::min(+acceleration.y, +mMaxAcceleration.y);
		break;
	case Directions::Left:
		mAcceleration.x = std::max(-acceleration.x, -mMaxAcceleration.x);
		mAcceleration.y = std::max(-acceleration.y, -mMaxAcceleration.y);
		break;
	default:
		break;
	}
	mAcceleration = acceleration;
}

void GameObject::setAccelerationX(const float value)
{
	setAcceleration({value, mAcceleration.y});
}

void GameObject::setAccelerationY(const float value)
{
	setAcceleration({mAcceleration.x, value});
}

void GameObject::setVelocity(const sf::Vector2f& velocity)
{
	switch (mDirection)
	{
	case Directions::Right:
		mVelocity.x = std::min(velocity.x, +mMaxVelocity.x);
		mVelocity.y = std::min(velocity.y, +mMaxVelocity.y);
		break;
	case Directions::Left:
		mVelocity.x = std::max(velocity.x, -mMaxVelocity.x);
		mVelocity.y = std::max(velocity.y, -mMaxVelocity.y);
		break;
	default:
		break;
	}	
}

void GameObject::setVelocityX(const float value)
{
	setVelocity({value, mVelocity.y});
}

void GameObject::setVelocityY(const float value)
{
	setVelocity({mVelocity.x, value});
}

void GameObject::setBoundsVisible(const bool visible)
{
	mBoundsVisible = visible;
}

void GameObject::setBoundsColor(const sf::Color& color)
{
	mBoundsColor = color;
}

void GameObject::accelerateVelocity(const sf::Vector2f& acceleration)
{
	setVelocity({mVelocity.x + acceleration.x, mVelocity.y + acceleration.y});
}

void GameObject::setDirection(const Directions direction)
{
	if (direction != mDirection)
	{
		mDirection = direction;

		mSprite->flip(GraphicsSpriteItem::Orientations::Horizontal);
	}
}

void GameObject::turnAround()
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

void GameObject::destroy()
{
	mState->destroy();
}

void GameObject::moveLeft()
{
	setDirection(Directions::Left);
	setAcceleration(-getMaxAcceleration());
}

void GameObject::moveRight()
{
	setDirection(Directions::Right);
	setAcceleration(getMaxAcceleration());
}

void GameObject::onObjectCollision(GameObject& object)
{
	mState->onCollision(object);
}

void GameObject::receiveEvents(const sf::Event& event)
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

void GameObject::update(const sf::Time& frameTime)
{
	mState->update(*this, frameTime);

	if (mState->isDestroyed())
	{
		remove();
	}
}

GameObjectIdentifiers GameObject::getIdentifier() const
{
	return mIdentifier;
}

const sf::Vector2f& GameObject::getMaxVelocity() const
{
	return mMaxVelocity;
}

const sf::Vector2f& GameObject::getVelocity() const
{
	return mVelocity;
}

Directions GameObject::getDirection() const
{
	return mDirection;
}

bool GameObject::hasIdentifier(const GameObjectIdentifiers identifier) const
{
	return mIdentifier == identifier;
}

bool GameObject::hasDirection(const Directions direction) const
{
	return mDirection == direction;
}

const sf::Vector2f& GameObject::getMaxAcceleration() const
{
	return mMaxAcceleration;
}

const sf::Vector2f& GameObject::getAcceleration() const
{
	return mAcceleration;
}

bool GameObject::isBoundsVisible() const
{
	return mBoundsVisible;
}

bool GameObject::isContainsPoint(const sf::Vector2f& point) const
{
	return mSprite->isContainsPoint(point);
}

bool GameObject::isDestroyed() const
{
	return mState->isDestroyed();
}

void GameObject::drawSelf(sf::RenderTarget& target, sf::RenderStates) const
{
	if (mBoundsVisible)
	{
		drawBounds(target);
	}
}

void GameObject::drawBounds(sf::RenderTarget& target) const
{
	const auto itemBounds = getBounds();

	sf::RectangleShape bounds{};
	bounds.setPosition(itemBounds.left + 1.0f, itemBounds.top + 1.0f);
	bounds.setSize({itemBounds.width - 2.0f, itemBounds.height - 2.0f});
	bounds.setFillColor(sf::Color::Transparent);
	bounds.setOutlineColor(mBoundsColor);
	bounds.setOutlineThickness(1.0f);

	target.draw(bounds);
}

sf::FloatRect GameObject::getBounds() const
{
	return mSprite->getBounds();
}
