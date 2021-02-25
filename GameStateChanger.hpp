#pragma once

#include "GameStateIdentifiers.hpp"

class GameStateChanger
{
public:
	virtual ~GameStateChanger() = default;

	virtual void pushStateRequest(const GameStateIdentifiers identifier) noexcept = 0;
	virtual void popStateRequest() noexcept = 0;
	virtual void clearStatesRequest() noexcept = 0;
};
