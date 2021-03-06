#pragma once

#include <memory>
#include <queue>
#include <deque>
#include <functional>
#include <unordered_map>

#include "GameState.hpp"
#include "GameStateChanger.hpp"
#include "GameStateStackRequest.hpp"

class GameStateManager final : public GameStateChanger
{
public:
	GameStateManager(World& world) noexcept;

	template <typename TGameState>
	void registerState(const GameStateIdentifiers identifier) noexcept;

	void pushState(const GameStateIdentifiers identifier) noexcept;
	void popState() noexcept;
	void clearStates() noexcept;

	void pushStateRequest(const GameStateIdentifiers identifier) noexcept override;
	void popStateRequest() noexcept override;
	void clearStatesRequest() noexcept override;

	void executeRequests() noexcept;

	void processEvents(const sf::Event& event) noexcept;
	void processLogic(const sf::Time& dt) noexcept;

	std::size_t getActiveStateCount() const noexcept;

	bool hasActiveStates() const noexcept;

private:
	GameState* findState(const GameStateIdentifiers identifier) const;
	GameState* getActiveState() const noexcept;

	World& mWorld;

	std::unordered_map<GameStateIdentifiers, std::unique_ptr<GameState>> mStates;
	std::queue<std::unique_ptr<GameStateStackRequest>> mStateStackRequests;
	std::deque<GameState*> mStateStack;
};

template <typename TGameState>
inline void GameStateManager::registerState(const GameStateIdentifiers identifier) noexcept
{
	static_assert(std::is_base_of_v<GameState, TGameState>, "TGameState must derived from GameState class");

	mStates.emplace(identifier, std::make_unique<TGameState>(*this, mWorld));
}
