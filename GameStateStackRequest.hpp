#pragma once

#include "GameStateIdentifiers.hpp"

class GameStateManager;

class GameStateStackRequest
{
public:
	virtual ~GameStateStackRequest() = default;

	virtual void execute(GameStateManager& gameStateManager) noexcept = 0;
};

class PushGameStateRequest final : public GameStateStackRequest
{
public:
	PushGameStateRequest(const GameStateIdentifiers identifier) noexcept;

	void execute(GameStateManager& gameStateManager) noexcept override;

private:
	GameStateIdentifiers mGameStateIdentifier;
};

class PopGameStateRequest final : public GameStateStackRequest
{
public:
	void execute(GameStateManager& gameStateManager) noexcept override;
};

class ClearGameStatesRequest final : public GameStateStackRequest
{
public:
	void execute(GameStateManager& gameStateManager) noexcept override;
};
