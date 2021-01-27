#include "EmptyGameObjectState.hpp"

EmptyGameObjectState EmptyGameObjectState::mState;

EmptyGameObjectState* EmptyGameObjectState::getInstance()
{
	return &mState;
}

void EmptyGameObjectState::onSet(GameObject&)
{

}

void EmptyGameObjectState::update(GameObject&, const sf::Time&)
{

}
