#include "EmptyGameObjectState.hpp"

EmptyGameObjectState EmptyGameObjectState::mState;

EmptyGameObjectState::EmptyGameObjectState() :
	mIsDestroyed{false}
{

}

EmptyGameObjectState* EmptyGameObjectState::getInstance()
{
	return &mState;
}

void EmptyGameObjectState::update(GameObject&, const sf::Time&)
{

}

void EmptyGameObjectState::destroy()
{
	mIsDestroyed = true;
}

bool EmptyGameObjectState::isDestroyed() const
{
	return mIsDestroyed;
}
