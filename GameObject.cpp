#include "GameObject.hpp"

#include "EmptyGameObjectState.hpp"

GameObject::GameObject(GraphicsSpriteItem* sprite) :
    mSprite{sprite},
	mState{EmptyGameObjectState::getInstance()},
	mDirectionFactor{+1.0f, 0.0f},
	mDirection{Directions::Right},
	mIsMouseOver{false}
{

}

void GameObject::setState(GameObjectState* state)
{
	if (mState)
	{
		mState->onUnset(*this);
	}

	mState = state;
	mState->onSet(*this);
}

void GameObject::setPosition(const sf::Vector2f& position)
{
    mSprite->setPosition(position);
}

void GameObject::setTexture(const sf::Texture& texture)
{
    mSprite->setTexture(texture);
}

void GameObject::setTextureArea(const sf::IntRect& area)
{
    mSprite->setTextureArea(area);
}

void GameObject::setAcceleration(const sf::Vector2f& acceleration)
{
	mAcceleration = acceleration;
}

void GameObject::setMaxVelocity(const sf::Vector2f& maxVelocity)
{
	mMaxVelocity = maxVelocity;
}

void GameObject::setVelocity(const sf::Vector2f& velocity)
{
	mVelocity.x = velocity.x;
	mVelocity.y = velocity.y;
}

void GameObject::accelerateVelocity(const sf::Vector2f& acceleration)
{
	setVelocity({mVelocity.x + acceleration.x, mVelocity.y + acceleration.y});
}

void GameObject::move(const sf::Vector2f& offset)
{
	mSprite->move(offset);
}

void GameObject::setDirectionFactor(const sf::Vector2f& factor)
{
	mDirectionFactor = factor;
}

void GameObject::setDirection(const Directions direction)
{
	if (direction != mDirection)
	{
		mDirectionFactor.x = (mDirection == Directions::Right) ? -1.0f : +1.0f;
		mDirection = direction;

		mSprite->flip(GraphicsSpriteItem::Orientations::Horizontal);
	}
}

void GameObject::turnAround()
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

void GameObject::dispose()
{
	mSprite->remove();
}

void GameObject::destroy()
{
	mState->destroy();
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
			if (mIsMouseOver)
			{
				mState->onMouseOver(*this, event.mouseMove);
			}
			else
			{
				mState->onMouseEnter(*this, event.mouseMove);
				mState->onMouseOver(*this, event.mouseMove);
				mIsMouseOver = true;
			}
		}
		else
		{
			if (mIsMouseOver)
			{
				mState->onMouseLeave(*this, event.mouseMove);
				mIsMouseOver = false;
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
}

sf::Vector2f GameObject::getPosition() const
{
    return mSprite->getGlobalPosition();
}

const sf::Vector2f& GameObject::getVelocity() const
{
	return mVelocity;
}

const sf::Vector2f& GameObject::getMaxVelocity() const
{
	return mMaxVelocity;
}

const sf::Vector2f& GameObject::getDirectionFactor() const
{
	return mDirectionFactor;
}

GameObject::Directions GameObject::getDirection() const
{
	return mDirection;
}

const sf::Vector2f& GameObject::getAcceleration() const
{
	return mAcceleration;
}

bool GameObject::hasCollision(const GameObject& object) const
{
    return mSprite->isIntersectsItem(*object.mSprite);
}

bool GameObject::isContainsPoint(const sf::Vector2f& point) const
{
    return mSprite->isContainsPoint(point);
}

bool GameObject::isDestroyed() const
{
    return mState->isDestroyed();
}
