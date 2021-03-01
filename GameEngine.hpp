#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceManager.hpp"
#include "SpritesetManager.hpp"
#include "GameObjectManager.hpp"
#include "GameObjectFactory.hpp"
#include "GameContextData.hpp"
#include "GameStateManager.hpp"

class GameEngine final
{
public:
	GameEngine() noexcept;

	int run() noexcept;

	bool isRunning() const noexcept;

protected:
	void processEvents() noexcept;
	void processLogic(const sf::Time& frameTime) noexcept;
	void processRender() noexcept;

private:
	void executeMainLoop() noexcept;

	void initializeFramerateText() noexcept;
	void initializeSpritesets() noexcept;
	void initializeTilemapEditor() noexcept;
	void initializeCollisionHandlers() noexcept;
	void initializeGameState() noexcept;

	bool loadResources() noexcept;
	bool loadFonts() noexcept;
	bool loadTextures() noexcept;

	sf::RenderWindow mRenderWindow;

	unsigned int mFramerate;
	sf::Text mFramerateText;

	ResourceManager mResourceManager;
	SpritesetManager mSpritesetManager;

	TilemapView mTilemapView;
	
	GameObjectManager mGameObjectManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;

	bool mFramerateTextVisible;
};
