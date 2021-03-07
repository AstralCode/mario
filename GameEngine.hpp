#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "GraphicsScene.hpp"
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
	void loadResources();
	void loadFonts();
	void loadTextures();

	void initializeFramerateText() noexcept;
	void initializeSpritesets() noexcept;
	void initializeGameState() noexcept;

	void execute() noexcept;

	sf::RenderWindow mRenderWindow;

	ResourceContainer mResources;
	SpritesetContainer mSpritesets;
	GraphicsScene mScene;
	GameContextData mContextData;
	GameStateManager mGameStateManager;

	sf::Text mFramerateText;
	unsigned int mFramerate;

	bool mFramerateTextVisible;
};
