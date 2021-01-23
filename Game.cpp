#include "Game.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"

Game::Game() :
	mRenderWindow{{640u, 480u}, "Mario"},
	mFrameTime{sf::seconds(1.0f / 60u)},
	mStatistics{mFPSCounter},
	mGameContextData{mGameResourceManager},
	mGameStateManager{mGameContextData}
{

}

void Game::run()
{
	loadResources();
	initializeStatistics();
	executeMainLoop();

	mRenderWindow.close();
}

void Game::processEvents()
{
	sf::Event event{};

	while (mRenderWindow.pollEvent(event))
	{
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

void Game::processLogic()
{
	mGameStateManager.processLogic(mFrameTime);
	mGameStateManager.executeRequests();
}

void Game::processRender()
{
	mFPSCounter.tick();

	mRenderWindow.clear();

	mGameStateManager.processRender(mRenderWindow);
	renderStatistics();

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
	const auto threadSleepTime = sf::milliseconds(10);

	sf::Clock clock{};
	sf::Time elapsedFrameUpdateTime{};
	sf::Time elapsedFPSCounterUpdateTime{};

	initializeGameState();

	while (isRunning())
	{
		const auto deltaTime = clock.restart();
		elapsedFrameUpdateTime += deltaTime;
		elapsedFPSCounterUpdateTime += deltaTime;

		bool renderFrame{false};

		while (elapsedFrameUpdateTime > mFrameTime)
		{
			processEvents();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			processLogic();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			renderFrame = true;

			elapsedFrameUpdateTime -= mFrameTime;
		}

		if (renderFrame)
		{
			processRender();
		}

		mStatistics.update(deltaTime);

		if (!renderFrame)
		{
			sf::sleep(threadSleepTime);
		}
	}
}

void Game::initializeStatistics()
{
	mStatistics.setPosition(5.0f, 5.0f);
	mStatistics.setText(mGameResourceManager.getFont(FontIdentifiers::Roboto));
	mStatistics.setVisible(false);
}

void Game::renderStatistics()
{
	if (mStatistics.isVisible())
	{
		mRenderWindow.draw(mStatistics.getGraphics());
	}
}

void Game::loadResources()
{
	loadFonts();
	loadTextures();
}

void Game::loadFonts()
{
	mGameResourceManager.addFont(FontIdentifiers::Roboto, makeFontPath("Roboto.ttf"));
}

void Game::loadTextures()
{
	mGameResourceManager.addTexture(TextureIdentifiers::Enemies, makeTexturePath("Enemies.png"));
	mGameResourceManager.addTexture(TextureIdentifiers::Mario, makeTexturePath("Mario.png"));
	mGameResourceManager.addTexture(TextureIdentifiers::Scenery, makeTexturePath("Scenery.png"));
}

std::string Game::makeFontPath(const std::string& filename) const
{
	return getFontPath() + filename;
}

std::string Game::makeTexturePath(const std::string& filename) const
{
	return getTexturePath() + filename;
}

void Game::initializeGameState()
{
	constexpr const auto initialStateIdentifier = GameStateIdentifiers::Initial;

	mGameStateManager.registerState<InitialGameState>(initialStateIdentifier);
	mGameStateManager.pushState(initialStateIdentifier);
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
