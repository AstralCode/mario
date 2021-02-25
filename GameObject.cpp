#include "GameObject.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "GraphicsSpriteItem.hpp"

GameObject::GameObject(const GameObjectIdentifiers identifier) noexcept :
	mIdentifier{identifier},
	mSprite{addItem<GraphicsSpriteItem>()},
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

void GameObject::setPositionX(const float x) noexcept
{
	setPosition(x, getPosition().y);
}

void GameObject::setPositionY(const float y) noexcept
{
	setPosition(getPosition().x, y);
}

void GameObject::setTexture(const sf::Texture& texture) noexcept
{
	mSprite->setTexture(texture);
}

void GameObject::setTextureArea(const SpriteArea& spriteArea) noexcept
{
	mSprite->setTextureArea(spriteArea.getArea());

	setOrigin(spriteArea.getOrigin());
}

void GameObject::setMaxAcceleration(const sf::Vector2f& acceleration) noexcept
{
	mMaxAcceleration = acceleration;
}

void GameObject::setMaxVelocity(const sf::Vector2f& velocity) noexcept
{
	mMaxVelocity = velocity;
}

void GameObject::setAcceleration(const sf::Vector2f& acceleration) noexcept
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

void GameObject::setAccelerationX(const float value) noexcept
{
	setAcceleration({value, mAcceleration.y});
}

void GameObject::setAccelerationY(const float value) noexcept
{
	setAcceleration({mAcceleration.x, value});
}

void GameObject::setVelocity(const sf::Vector2f& velocity) noexcept
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

void GameObject::setVelocityX(const float value) noexcept
{
	setVelocity({value, mVelocity.y});
}

void GameObject::setVelocityY(const float value) noexcept
{
	setVelocity({mVelocity.x, value});
}

void GameObject::setAreaBoundsVisible(const bool visible) noexcept
{
	mAreaBoundsVisible = visible;
}

void GameObject::setAreaBoundsColor(const sf::Color& color) noexcept
{
	mAreaBoundsColor = color;
}

void GameObject::accelerateVelocity(const sf::Vector2f& acceleration) noexcept
{
	setVelocity({mVelocity.x + acceleration.x, mVelocity.y + acceleration.y});
}

void GameObject::setDirection(const Directions direction) noexcept
{
	if (direction != mDirection)
	{
		mDirection = direction;

		mSprite->flip(GraphicsSpriteItem::Orientations::Horizontal);
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

void GameObject::receiveEvents(const sf::Event& event) noexcept
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

void GameObject::update(const sf::Time& frameTime) noexcept
{
	mState->update(*this, frameTime);

	if (mState->isDestroyed())
	{
		remove();
	}
}

GameObjectIdentifiers GameObject::getIdentifier() const noexcept
{
	return mIdentifier;
}

const sf::Vector2f& GameObject::getMaxVelocity() const noexcept
{
	return mMaxVelocity;
}

const sf::Vector2f& GameObject::getVelocity() const noexcept
{
	return mVelocity;
}

Directions GameObject::getDirection() const noexcept
{
	return mDirection;
}

bool GameObject::hasIdentifier(const GameObjectIdentifiers identifier) const noexcept
{
	return mIdentifier == identifier;
}

bool GameObject::hasDirection(const Directions direction) const noexcept
{
	return mDirection == direction;
}

const sf::Vector2f& GameObject::getMaxAcceleration() const noexcept
{
	return mMaxAcceleration;
}

const sf::Vector2f& GameObject::getAcceleration() const noexcept
{
	return mAcceleration;
}

bool GameObject::isAreaBoundsVisible() const noexcept
{
	return mAreaBoundsVisible;
}

bool GameObject::isContainsPoint(const sf::Vector2f& point) const noexcept
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
