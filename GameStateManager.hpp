#pragma once

#include <memory>
#include <deque>
#include <queue>
#include <functional>
#include <unordered_map>

#include "GameState.hpp"
#include "GameStateChanger.hpp"
#include "GameStateStackRequest.hpp"
#include "GameContextData.hpp"

class GameStateManager final : public GameStateChanger
{
public:
	GameStateManager(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene) noexcept;

	template<typename TGameState>
	void registerState(const GameStateIdentifiers identifier) noexcept;

	void pushState(const GameStateIdentifiers identifier) noexcept;
	void popState() noexcept;
	void clearStates() noexcept;

	void pushStateRequest(const GameStateIdentifiers identifier) noexcept override;
	void popStateRequest() noexcept override;
	void clearStatesRequest() noexcept override;

	void executeRequests() noexcept;

	void processEvents(const sf::Event& event) noexcept;
	void processLogic(const sf::Time& fixedFrameTime) noexcept;

	std::size_t getActiveStateCount() const noexcept;

	bool hasActiveStates() const noexcept;

private:
	GameState* findState(const GameStateIdentifiers identifier) const;
	GameState* getActiveState() const noexcept;

	GameContextData mContextData;
	std::unordered_map<GameStateIdentifiers, std::unique_ptr<GameState>> mStates;
	std::queue<std::unique_ptr<GameStateStackRequest>> mStateStackRequests;
	std::deque<GameState*> mStateStack;
};

template<typename TGameState>
inline void GameStateManager::registerState(const GameStateIdentifiers identifier) noexcept
{
	static_assert(std::is_base_of_v<GameState, TGameState>, "TGameState must derived from GameState");

	mStates.emplace(identifier, std::make_unique<TGameState>(mContextData));
}
