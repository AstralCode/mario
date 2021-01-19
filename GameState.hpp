#pragma once

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class GameContextData;
class GameStateManager;

class GameState : private sf::NonCopyable
{
public:
	GameState(GameContextData& gameContextData, GameStateManager& gameStateManager);
	virtual ~GameState() = default;

	virtual void ProcessEvents(const sf::Event& event) = 0;
	virtual void ProcessLogic() = 0;
	virtual void ProcessRender(sf::RenderTarget& renderer) const = 0;

protected:
	GameContextData& mGameContextData;
	GameStateManager& mGameStateManager;
};
