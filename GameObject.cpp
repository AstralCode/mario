#include "GameObject.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "GraphicsSpriteItem.hpp"

GameObject::GameObject(const GameObjectIdentifiers identifier) :
	mIdentifier{identifier},
	mSprite{addItem<GraphicsSpriteItem>()},
	mDirection{Directions::Right},
	mDirectionFactor{+1.0f, 0.0f},
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

void GameObject::setTexture(const sf::Texture& texture)
{
	mSprite->setTexture(texture);
}

void GameObject::setTextureArea(const SpriteArea& spriteArea)
{
	mSprite->setTextureArea(spriteArea.getArea());
	mSprite->setOrigin(spriteArea.getOrigin());
}

void GameObject::setMaxAcceleration(const sf::Vector2f& acceleration)
{
	mMaxAcceleration = acceleration;
}

void GameObject::setAcceleration(const sf::Vector2f& acceleration)
{
	mAcceleration = acceleration;
}

void GameObject::setMaxVelocity(const sf::Vector2f& velocity)
{
	mMaxVelocity = velocity;
}

void GameObject::setVelocity(const sf::Vector2f& velocity)
{
	mVelocity.x = std::min(velocity.x, mMaxVelocity.x);
	mVelocity.y = std::min(velocity.y, mMaxVelocity.y);
}

void GameObject::setBoundsVisible(const bool visible)
{
	mBoundsVisible = visible;
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

void GameObject::destroy()
{
	mState->destroy();
}

void GameObject::onCollision(GameObject& object)
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

const sf::Vector2f& GameObject::getDirectionFactor() const
{
	return mDirectionFactor;
}

GameObject::Directions GameObject::getDirection() const
{
	return mDirection;
}

bool GameObject::hasIdentifier(const GameObjectIdentifiers identifier) const
{
	return mIdentifier == identifier;
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
	bounds.setPosition(itemBounds.left, itemBounds.top);
	bounds.setSize({itemBounds.width, itemBounds.height});
	bounds.setFillColor(sf::Color::Transparent);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setOutlineThickness(1.0f);

	target.draw(bounds);
}

sf::FloatRect GameObject::getBounds() const
{
	return mSprite->getBounds();
}
