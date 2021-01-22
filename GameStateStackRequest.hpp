#pragma once

#include "SFML/System/NonCopyable.hpp"

#include "GameStateIdentifiers.hpp"

class GameStateManager;

class GameStateStackRequest : private sf::NonCopyable
{
public:
	virtual ~GameStateStackRequest() = default;

	virtual void execute(GameStateManager& gameStateManager) = 0;
};

class PushGameStateRequest final : public GameStateStackRequest
{
public:
	PushGameStateRequest(const GameStateIdentifiers identifier);

	void execute(GameStateManager& gameStateManager) override;

private:
	GameStateIdentifiers mGameStateIdentifier;
};

class PopGameStateRequest final : public GameStateStackRequest
{
public:
	void execute(GameStateManager& gameStateManager) override;
};

class ClearGameStatesRequest final : public GameStateStackRequest
{
public:
	void execute(GameStateManager& gameStateManager) override;
};
