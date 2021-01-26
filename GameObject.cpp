#include "GameObject.hpp"

#include "EmptyGameObjectState.hpp"

GameObject::GameObject(GraphicsSpriteItem* sprite) :
    mSprite{sprite},
	mState{EmptyGameObjectState::getInstance()},
	mIsMouseOver{false}
{

}

void GameObject::setState(GameObjectState* state)
{
	mState = state;
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

void GameObject::removeSprite()
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
