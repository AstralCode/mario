#include "Game.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"

Game::Game() :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mStatistics{mFPSCounter},
	mGameObjectManager{mGamePhysics, mGameSpriteAtlasManager},
	mGameContextData{mGraphicsScene, mGameResourceContainer, mGameSpriteAtlasManager, mGameObjectManager},
	mGameStateManager{mGameContextData}
{
	mRenderWindow.setKeyRepeatEnabled(false);
}

void Game::run()
{
	loadResources();
	initializeStatistics();
	initializeGameSpriteAtlases();
	executeMainLoop();
}

void Game::processEvents()
{
	sf::Event event{};

	while (mRenderWindow.pollEvent(event))
	{
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

void Game::processLogic(const sf::Time& frameTime)
{
	mGameObjectManager.clean();
	mGameObjectManager.update(frameTime);

	mGraphicsScene.clean();

	mGameStateManager.processLogic(frameTime);
	mGameStateManager.executeRequests();
}

void Game::processRender()
{
	if (mStatistics.isVisible())
	{
		mFPSCounter.tick();
	}

	mRenderWindow.clear();
	mRenderWindow.draw(mGraphicsScene);

	if (mStatistics.isVisible())
	{
		mRenderWindow.setView(mRenderWindow.getDefaultView());
		mRenderWindow.draw(mStatistics.getGraphics());
	}

	mRenderWindow.display();
}

GameContextData& Game::getContextData()
{
	return mGameContextData;
}

bool Game::isRunning() const
{
	return mGameStateManager.hasActiveStates();
}

void Game::executeMainLoop()
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

void Game::initializeStatistics()
{
	mStatistics.setPosition(5.0f, 5.0f);
	mStatistics.setText(mGameResourceContainer.getFont(FontIdentifiers::Roboto));
	mStatistics.setVisible(false);
}

void Game::initializeGameSpriteAtlases()
{
	auto& marioSprites = mGameSpriteAtlasManager.createAtlas("mario");
	marioSprites.addRegion("mario_stand", {{0, 0}, {32, 32}, {{{0, 0, 24, 32}}}});
	marioSprites.addRegion("mario_move", {{1, 0}, {32, 32}, {{{0, 0, 26, 32}, {0, 0, 26, 32}, {0, 0, 24, 32}}}});

	auto& enemySprites = mGameSpriteAtlasManager.createAtlas("enemy");
	enemySprites.addRegion("goomba_move", {{0, 0}, {32, 32}, {{{0, 0, 32, 32}, {0, 0, 32, 32}}}});
	enemySprites.addRegion("goomba_dead", {{2, 0}, {32, 32}, {{{0, 16, 32, 16}}}});
}

void Game::initializeGameState()
{
	mGameStateManager.registerState<InitialGameState>(GameStateIdentifiers::Initial);
	mGameStateManager.pushState(GameStateIdentifiers::Initial);
}

void Game::loadResources()
{
	loadFonts();
	loadTextures();
}

void Game::loadFonts()
{
	mGameResourceContainer.addFont(FontIdentifiers::Roboto, makeFontPath("Roboto.ttf"));
}

void Game::loadTextures()
{
	mGameResourceContainer.addTexture(TextureIdentifiers::Enemies, makeTexturePath("Enemies.png"));
	mGameResourceContainer.addTexture(TextureIdentifiers::Mario, makeTexturePath("Mario.png"));
	mGameResourceContainer.addTexture(TextureIdentifiers::Scenery, makeTexturePath("Scenery.png"));
}

std::string Game::makeFontPath(const std::string& filename) const
{
	return getFontPath() + filename;
}

std::string Game::makeTexturePath(const std::string& filename) const
{
	return getTexturePath() + filename;
}

std::string Game::getResourcesPath() const
{
	return "Resources/";
}

std::string Game::getFontPath() const
{
	return getResourcesPath() + "Fonts/";
}

std::string Game::getTexturePath() const
{
	return getResourcesPath() + "Textures/";
}
