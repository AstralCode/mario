#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"

GameEngine::GameEngine() :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mStatistics{mFPSCounter},
	mGameObjectManager{mGamePhysics},
	mGameContextData{mTiledMap, mGraphicsScene, mGameResourceManager, mGameSpriteAtlasManager, mGameObjectManager},
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
	mStatistics.setText(mGameResourceManager.getFont(FontIdentifiers::Roboto));
	mStatistics.setVisible(false);
}

void GameEngine::initializeGameSpriteAtlases()
{
	const sf::Vector2i spriteSize{32, 32};

	auto& marioSprites = mGameSpriteAtlasManager.createAtlas(SpriteAtlasIdentifiers::Mario);
	marioSprites.addRegion(SpriteAtlasRegionIdentifiers::Mario::Stand, {spriteSize, {0, 0}, {{{0, 0, 24, 32}}}});
	marioSprites.addRegion(SpriteAtlasRegionIdentifiers::Mario::Move, {spriteSize, {1, 0}, {{{0, 0, 26, 32}, {0, 0, 26, 32}, {0, 0, 24, 32}}}});
	marioSprites.addRegion(SpriteAtlasRegionIdentifiers::Mario::Slide, {spriteSize, {8, 0}, {{{0, 0, 24, 32}}}});

	auto& enemySprites = mGameSpriteAtlasManager.createAtlas(SpriteAtlasIdentifiers::Enemy);
	enemySprites.addRegion(SpriteAtlasRegionIdentifiers::Goomba::Move, {spriteSize, {0, 0}, {{{0, 0, 32, 32}, {0, 0, 32, 32}}}});
	enemySprites.addRegion(SpriteAtlasRegionIdentifiers::Goomba::Dead, {spriteSize, {2, 0}, {{{0, 16, 32, 16}}}});

	auto& blocksSprites = mGameSpriteAtlasManager.createAtlas(SpriteAtlasIdentifiers::Blocks);
	blocksSprites.addRegion(SpriteAtlasRegionIdentifiers::Blocks::QuestionMarkBox, {spriteSize, {0, 3}, {{{0, 0, 32, 32}, {0, 0, 32, 32}, {0, 0, 32, 32}}}});
	blocksSprites.addRegion(SpriteAtlasRegionIdentifiers::Blocks::WaterQuestionMarkBox, {spriteSize, {0, 4}, {{{0, 0, 32, 32}, {0, 0, 32, 32}, {0, 0, 32, 32}}}});

	auto& itemSprites = mGameSpriteAtlasManager.createAtlas(SpriteAtlasIdentifiers::Items);
	itemSprites.addRegion(SpriteAtlasRegionIdentifiers::Items::Coin, {spriteSize, {12, 12}, {{{6, 2, 20, 28}, {6, 2, 20, 28}, {6, 2, 20, 28}}}});
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
	mGameResourceManager.addFont(FontIdentifiers::Roboto, ResourcePaths::Fonts::Roboto);
}

void GameEngine::loadTextures()
{
	mGameResourceManager.addTexture(TextureIdentifiers::Enemies, ResourcePaths::Textures::Enemies);
	mGameResourceManager.addTexture(TextureIdentifiers::Mario, ResourcePaths::Textures::Mario);
	mGameResourceManager.addTexture(TextureIdentifiers::Scenery, ResourcePaths::Textures::Scenery);
}
