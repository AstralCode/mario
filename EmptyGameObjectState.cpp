#include "EmptyGameObjectState.hpp"

EmptyGameObjectState EmptyGameObjectState::mState;

EmptyGameObjectState* EmptyGameObjectState::getInstance()
{
	return &mState;
}

EmptyGameObjectState::EmptyGameObjectState() :
	mIsDestroyed{false}
{

}

void EmptyGameObjectState::onSet(GameObject&)
{

}

void EmptyGameObjectState::onUnset(GameObject&)
{

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
