#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"

GameEngine::GameEngine() :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mStatistics{mFPSCounter},
	mGameObjectManager{mGamePhysics, mGameSpriteAtlasManager},
	mGameContextData{mTiledMap, mGraphicsScene, mGameResourceContainer, mGameSpriteAtlasManager, mGameObjectManager},
	mGameStateManager{mGameContextData}
{
	mRenderWindow.setKeyRepeatEnabled(false);
}

void GameEngine::run()
{
	loadResources();
	initializeStatistics();
	initializeGameSpriteAtlases();
	executeMainLoop();
}

GameContextData& GameEngine::getContextData()
{
	return mGameContextData;
}

bool GameEngine::isRunning() const
{
	return mGameStateManager.hasActiveStates();
}

void GameEngine::processEvents()
{
	sf::Event event{};

	while (mRenderWindow.pollEvent(event))
	{
		mTiledMap.receiveEvents(event);
		mGameObjectManager.receiveEvents(event);
		mGameStateManager.processEvents(event);

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F2)
			{
				mStatistics.setVisible(!mStatistics.isVisible());
			}
			break;

		case sf::Event::Closed:
			mGameStateManager.clearStatesRequest();
			break;

		default:
			break;
		}
	}

	mGameStateManager.executeRequests();
}

void GameEngine::processLogic(const sf::Time& frameTime)
{
	mGameObjectManager.clean();
	mGameObjectManager.update(frameTime);

	mGraphicsScene.clean();

	mGameStateManager.processLogic(frameTime);
	mGameStateManager.executeRequests();
}

void GameEngine::processRender()
{
	if (mStatistics.isVisible())
	{
		mFPSCounter.tick();
	}

	mRenderWindow.clear();

	mRenderWindow.draw(mTiledMap);
	mRenderWindow.draw(mGraphicsScene);
	mRenderWindow.draw(mTiledMap.getGrid());

	if (mStatistics.isVisible())
	{
		mRenderWindow.setView(mRenderWindow.getDefaultView());
		mRenderWindow.draw(mStatistics.getGraphics());
	}

	mRenderWindow.display();
}

void GameEngine::executeMainLoop()
{
	const auto frameTime = sf::seconds(1.0f / 60);
	const auto threadSleepTime = sf::milliseconds(10);

	sf::Clock clock{};
	sf::Time elapsedFrameUpdateTime{};
	sf::Time elapsedFPSCounterUpdateTime{};

	initializeGameState();

	while (isRunning())
	{
		const auto loopTime = clock.restart();
		bool renderFrame{false};

		elapsedFrameUpdateTime += loopTime;
		elapsedFPSCounterUpdateTime += loopTime;

		while (elapsedFrameUpdateTime > frameTime)
		{
			processEvents();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			processLogic(frameTime);

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			renderFrame = true;

			elapsedFrameUpdateTime -= frameTime;
		}

		if (renderFrame)
		{
			processRender();
		}

		mStatistics.update(loopTime);

		if (!renderFrame)
		{
			sf::sleep(threadSleepTime);
		}
	}

	mRenderWindow.close();
}

void GameEngine::initializeStatistics()
{
	mStatistics.setPosition(5.0f, 5.0f);
	mStatistics.setText(mGameResourceContainer.getFont(FontIdentifiers::Roboto));
	mStatistics.setVisible(false);
}

void GameEngine::initializeGameSpriteAtlases()
{
	auto& marioSprites = mGameSpriteAtlasManager.createAtlas("mario");
	marioSprites.addRegion("mario_stand", {{0, 0}, {32, 32}, {{{0, 0, 24, 32}}}});
	marioSprites.addRegion("mario_move", {{1, 0}, {32, 32}, {{{0, 0, 26, 32}, {0, 0, 26, 32}, {0, 0, 24, 32}}}});
	marioSprites.addRegion("mario_slide", {{8, 0}, {32, 32}, {{{0, 0, 24, 32}}}});

	auto& enemySprites = mGameSpriteAtlasManager.createAtlas("enemy");
	enemySprites.addRegion("goomba_move", {{0, 0}, {32, 32}, {{{0, 0, 32, 32}, {0, 0, 32, 32}}}});
	enemySprites.addRegion("goomba_dead", {{2, 0}, {32, 32}, {{{0, 16, 32, 16}}}});
}

void GameEngine::initializeGameState()
{
	mGameStateManager.registerState<InitialGameState>(GameStateIdentifiers::Initial);
	mGameStateManager.pushState(GameStateIdentifiers::Initial);
}

void GameEngine::loadResources()
{
	loadFonts();
	loadTextures();
}

void GameEngine::loadFonts()
{
	mGameResourceContainer.addFont(FontIdentifiers::Roboto, makeFontPath("Roboto.ttf"));
}

void GameEngine::loadTextures()
{
	mGameResourceContainer.addTexture(TextureIdentifiers::Enemies, makeTexturePath("Enemies.png"));
	mGameResourceContainer.addTexture(TextureIdentifiers::Mario, makeTexturePath("Mario.png"));
	mGameResourceContainer.addTexture(TextureIdentifiers::Scenery, makeTexturePath("Scenery.png"));
}

std::string GameEngine::makeFontPath(const std::string& filename) const
{
	return getFontPath() + filename;
}

std::string GameEngine::makeTexturePath(const std::string& filename) const
{
	return getTexturePath() + filename;
}

std::string GameEngine::getResourcesPath() const
{
	return "Resources/";
}

std::string GameEngine::getFontPath() const
{
	return getResourcesPath() + "Fonts/";
}

std::string GameEngine::getTexturePath() const
{
	return getResourcesPath() + "Textures/";
}
