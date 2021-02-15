#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"

GameEngine::GameEngine() :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mStatistics{mFPSCounter},
	mGameObjectManager{mGraphicsScene, mGamePhysics},
	mGameContextData{mTiledMap, mResourceManager, mSpritesetManager, mGameObjectManager},
	mGameStateManager{mGameContextData}
{
	mRenderWindow.setKeyRepeatEnabled(false);
}

void GameEngine::run()
{
	loadResources();
	initializeStatistics();
	initializeSpritesets();
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
	mStatistics.setText(mResourceManager.getFont(FontIdentifiers::Roboto));
	mStatistics.setVisible(false);
}

void GameEngine::initializeSpritesets()
{
	auto& marioSpriteset = mSpritesetManager.create(SpritesetIdentifiers::Mario);
	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Stand, {{32, 32}, {0, 0}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Move, {{32, 32}, {1, 0}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 0, 26, 32}},
		SpritesetArea{{32, 32}, {1, 0}, {0, 0, 26, 32}},
		SpritesetArea{{32, 32}, {2, 0}, {0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Slide, {{32, 32}, {8, 0}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 0, 24, 32}}
	}}});

	auto& enemySpriteset = mSpritesetManager.create(SpritesetIdentifiers::Enemy);
	enemySpriteset.addRegion(SpritesetRegionIdentifiers::Goomba::Move, {{32, 32}, {0, 0}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 0, 32, 32}},
		SpritesetArea{{32, 32}, {1, 0}, {0, 0, 32, 32}}
	}}});

	enemySpriteset.addRegion(SpritesetRegionIdentifiers::Goomba::Dead, {{32, 32}, {2, 0}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 16, 32, 16}}
	}}});

	auto& blocksSpriteset = mSpritesetManager.create(SpritesetIdentifiers::Blocks);
	blocksSpriteset.addRegion(SpritesetRegionIdentifiers::Blocks::QuestionMarkBox, {{32, 32}, {0, 3}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 0, 32, 32}},
		SpritesetArea{{32, 32}, {1, 0}, {0, 0, 32, 32}},
		SpritesetArea{{32, 32}, {2, 0}, {0, 0, 32, 32}}
	}}});

	blocksSpriteset.addRegion(SpritesetRegionIdentifiers::Blocks::WaterQuestionMarkBox, {{32, 32}, {0, 4}, {{
		SpritesetArea{{32, 32}, {0, 0}, {0, 0, 32, 32}},
		SpritesetArea{{32, 32}, {1, 0}, {0, 0, 32, 32}},
		SpritesetArea{{32, 32}, {2, 0}, {0, 0, 32, 32}}
	}}});

	auto& itemSpriteset = mSpritesetManager.create(SpritesetIdentifiers::Items);
	itemSpriteset.addRegion(SpritesetRegionIdentifiers::Items::Coin, {{32, 32}, {12, 12}, {{
		SpritesetArea{{32, 32}, {0, 0}, {6, 2, 20, 28}},
		SpritesetArea{{32, 32}, {1, 0}, {6, 2, 20, 28}},
		SpritesetArea{{32, 32}, {2, 0}, {6, 2, 20, 28}}
	}}});

	itemSpriteset.addRegion(SpritesetRegionIdentifiers::Items::ScoreCoin, {{32, 32}, {11, 15}, {{
		SpritesetArea{{11, 16}, {0, 0}, {0, 0, 10, 16}},
		SpritesetArea{{11, 16}, {1, 0}, {0, 0, 10, 16}},
		SpritesetArea{{11, 16}, {2, 0}, {0, 0, 10, 16}}
	}}});
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
	mResourceManager.addFont(FontIdentifiers::Roboto, ResourcePaths::Fonts::Roboto);
}

void GameEngine::loadTextures()
{
	mResourceManager.addTexture(TextureIdentifiers::Enemies, ResourcePaths::Textures::Enemies);
	mResourceManager.addTexture(TextureIdentifiers::Mario, ResourcePaths::Textures::Mario);
	mResourceManager.addTexture(TextureIdentifiers::Scenery, ResourcePaths::Textures::Scenery);
}
