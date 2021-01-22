#pragma once

#include "GameStateIdentifiers.hpp"

class GameStateChanger
{
public:
	virtual ~GameStateChanger() = default;

	virtual void pushStateRequest(const GameStateIdentifiers identifier) = 0;
	virtual void popStateRequest() = 0;
	virtual void clearStatesRequest() = 0;
};
