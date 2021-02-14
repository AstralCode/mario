#pragma once

#include "GameState.hpp"
#include "GameObjectFactory.hpp"

class InitialGameState final : public GameState
{
public:
	InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger);

	void onEnter() override;
	void onLeave() override;

	void processLogic(const sf::Time& frameTime) override;

private:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) override;
	void onEscapePressed() override;

	GraphicsItem* mSceneLayer;

	GraphicsItem* mBackgroundLayer;
	GraphicsItem* mPlayersLayer;
	GraphicsItem* mEnemiesLayer;
	GraphicsItem* mItemsLayer;
	GraphicsItem* mBlocksLayer;

	GameObjectFactory mGameObjectFactory;
};
