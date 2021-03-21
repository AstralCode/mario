#pragma once

#include "GameState.hpp"

class InitialGameState final : public GameState
{
public:
	InitialGameState(GameContextData& contextData, GameStateChanger& gameStateChanger) noexcept;

	void onEnter() noexcept override;
	void onLeave() noexcept override;

	void processLogic(const sf::Time& dt) noexcept override;

private:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onEscapePressed() noexcept override;

	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	World& mWorld;
};
