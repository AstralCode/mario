#include "GraphicsGameObject.hpp"

#include "GraphicsSpriteItem.hpp"

GraphicsGameObject::GraphicsGameObject() :
	mSprite{addItem<GraphicsSpriteItem>()},
	mDirection{Directions::Right},
	mDirectionFactor{+1.0f, 0.0f},
	mMouseOver{false}
{

}

void GraphicsGameObject::setState(std::unique_ptr<GameObjectState> state)
{
	if (mState)
	{
		mState->onUnset(*this);
	}

	mState = std::move(state);
	mState->onSet(*this);
}

void GraphicsGameObject::setPosition(const sf::Vector2f& position)
{
	mSprite->setPosition(position);
}

void GraphicsGameObject::setTexture(const sf::Texture& texture)
{
	mSprite->setTexture(texture);
}

void GraphicsGameObject::setTextureArea(const sf::IntRect& area)
{
	mSprite->setTextureArea(area);
}

void GraphicsGameObject::setMaxAcceleration(const sf::Vector2f& acceleration)
{
	mMaxAcceleration = acceleration;
}

void GraphicsGameObject::setAcceleration(const sf::Vector2f& acceleration)
{
	mAcceleration = acceleration;
}

void GraphicsGameObject::setMaxVelocity(const sf::Vector2f& velocity)
{
	mMaxVelocity = velocity;
}

void GraphicsGameObject::setVelocity(const sf::Vector2f& velocity)
{
	mVelocity.x = std::min(velocity.x, mMaxVelocity.x);
	mVelocity.y = std::min(velocity.y, mMaxVelocity.y);
}

void GraphicsGameObject::accelerateVelocity(const sf::Vector2f& acceleration)
{
	setVelocity({mVelocity.x + acceleration.x, mVelocity.y + acceleration.y});
}

void GraphicsGameObject::move(const sf::Vector2f& offset)
{
	mSprite->move(offset);
}

void GraphicsGameObject::setDirectionFactor(const sf::Vector2f& factor)
{
	mDirectionFactor = factor;
}

void GraphicsGameObject::setDirection(const Directions direction)
{
	if (direction != mDirection)
	{
		mDirectionFactor.x = (mDirection == Directions::Right) ? -1.0f : +1.0f;
		mDirection = direction;

		mSprite->flip(GraphicsSpriteItem::Orientations::Horizontal);
	}
}

void GraphicsGameObject::turnAround()
{
	if (mDirection == Directions::Right)
	{
		setDirection(Directions::Left);
	}
	else
	{
		setDirection(Directions::Right);
	}
}

void GraphicsGameObject::destroy()
{
	remove();

	mState->destroy();
}

void GraphicsGameObject::receiveEvents(const sf::Event& event)
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

void GraphicsGameObject::update(const sf::Time& frameTime)
{
	mState->update(*this, frameTime);
}

sf::Vector2f GraphicsGameObject::getPosition() const
{
	return mSprite->getGlobalPosition();
}

const sf::Vector2f& GraphicsGameObject::getMaxVelocity() const
{
	return mMaxVelocity;
}

const sf::Vector2f& GraphicsGameObject::getVelocity() const
{
	return mVelocity;
}

const sf::Vector2f& GraphicsGameObject::getDirectionFactor() const
{
	return mDirectionFactor;
}

GraphicsGameObject::Directions GraphicsGameObject::getDirection() const
{
	return mDirection;
}

const sf::Vector2f& GraphicsGameObject::getMaxAcceleration() const
{
	return mMaxAcceleration;
}

const sf::Vector2f& GraphicsGameObject::getAcceleration() const
{
	return mAcceleration;
}

bool GraphicsGameObject::hasCollision(const GraphicsItem& item) const
{
	return mSprite->isIntersectsItem(item);
}

bool GraphicsGameObject::isContainsPoint(const sf::Vector2f& point) const
{
	return mSprite->isContainsPoint(point);
}

bool GraphicsGameObject::isDestroyed() const
{
	return isWreck();
}

bool GraphicsGameObject::isWreck() const
{
	return mState->isDestroyed();
}

sf::FloatRect GraphicsGameObject::getBounds() const
{
	return mSprite->getBounds();
}
