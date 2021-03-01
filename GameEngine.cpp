#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"
#include "MarioCollisionHandler.hpp"
#include "EnemyCollisionHandler.hpp"

GameEngine::GameEngine() noexcept :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mStatistics{mFPSCounter},
	mTilemapEditor{mResourceManager},
	mCollisionModule{mTilemapView},
	mGameObjectManager{mGraphicsScene, mGamePhysics, mCollisionModule},
	mGameContextData{mTilemapView, mTilemapEditor, mResourceManager, mSpritesetManager, mGameObjectManager},
	mGameStateManager{mGameContextData}
{
	mRenderWindow.setKeyRepeatEnabled(false);
}

void GameEngine::run() noexcept
{
	loadResources();
	initializeStatistics();
	initializeSpritesets();
	initializeTilemapEditor();
	initializeCollisionHandlers();
	executeMainLoop();
}

GameContextData& GameEngine::getContextData() noexcept
{
	return mGameContextData;
}

bool GameEngine::isRunning() const noexcept
{
	return mGameStateManager.hasActiveStates();
}

void GameEngine::processEvents() noexcept
{
	sf::Event event{};

	while (mRenderWindow.pollEvent(event))
	{
		mTilemapView.receiveEvents(event);
		mGameObjectManager.receiveEvents(event);
		mGameStateManager.processEvents(event);

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F1)
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

void GameEngine::processLogic(const sf::Time& frameTime) noexcept
{
	mGameObjectManager.update(frameTime);
	mGameObjectManager.clean();

	mGameStateManager.processLogic(frameTime);
	mGameStateManager.executeRequests();
}

void GameEngine::processRender() noexcept
{
	if (mStatistics.isVisible())
	{
		mFPSCounter.tick();
	}

	mRenderWindow.clear();

	//mRenderWindow.draw(mTilemapView);
	//mRenderWindow.draw(mGraphicsScene);
	//mRenderWindow.draw(mTilemapView.getGrid());
	mRenderWindow.draw(mTilemapEditor);

	if (mStatistics.isVisible())
	{
		mRenderWindow.setView(mRenderWindow.getDefaultView());
		mRenderWindow.draw(mStatistics.getGraphics());
	}

	mRenderWindow.display();
}

void GameEngine::executeMainLoop() noexcept
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

void GameEngine::initializeStatistics() noexcept
{
	mStatistics.setText(mResourceManager.getFont(FontIdentifiers::Roboto));
	mStatistics.setVisible(false);
}

void GameEngine::initializeSpritesets() noexcept
{
	auto& marioSpriteset = mSpritesetManager.create(SpritesetIdentifiers::Mario);
	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Stand, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 24, 32}, OriginPoint{13, 16}}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Move, SpritesetRegion{GridSize{32, 32}, GridTileIndex{1, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 26, 32}, OriginPoint{13, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{IntArea{0, 0, 26, 32}, OriginPoint{13, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{IntArea{0, 0, 24, 32}, OriginPoint{12, 16}}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Slide, SpritesetRegion{GridSize{32, 32}, GridTileIndex{8, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 24, 32}, OriginPoint{12, 16}}}
	}}});

	auto& enemySpriteset = mSpritesetManager.create(SpritesetIdentifiers::Enemy);
	enemySpriteset.addRegion(SpritesetRegionIdentifiers::Goomba::Move, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}}
	}}});

	enemySpriteset.addRegion(SpritesetRegionIdentifiers::Goomba::Dead, {GridSize{32, 32}, {2, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 16, 32, 16}, OriginPoint{16, 0}}}
	}}});

	auto& blocksSpriteset = mSpritesetManager.create(SpritesetIdentifiers::Blocks);
	blocksSpriteset.addRegion(SpritesetRegionIdentifiers::Blocks::QuestionMarkBox, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}}
	}}});

	blocksSpriteset.addRegion(SpritesetRegionIdentifiers::Blocks::WaterQuestionMarkBox, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 1}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{IntArea{0, 0, 32, 32}, OriginPoint{16, 16}}}
	}}});

	auto& itemSpriteset = mSpritesetManager.create(SpritesetIdentifiers::Items);
	itemSpriteset.addRegion(SpritesetRegionIdentifiers::Items::Coin, SpritesetRegion{GridSize{32, 32}, GridTileIndex{4, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{IntArea{6, 2, 20, 28}, OriginPoint{10, 14}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{IntArea{6, 2, 20, 28}, OriginPoint{10, 14}}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{IntArea{6, 2, 20, 28}, OriginPoint{10, 14}}}
	}}});

	itemSpriteset.addRegion(SpritesetRegionIdentifiers::Items::ScoreCoin, SpritesetRegion{GridSize{32, 32}, GridTileIndex{9, 3}, {{
		SpritesetArea{GridSize{11, 16}, GridTileIndex{0, 0}, SpriteArea{IntArea{0, 0, 10, 16}, OriginPoint{5, 8}}},
		SpritesetArea{GridSize{11, 16}, GridTileIndex{1, 0}, SpriteArea{IntArea{0, 0, 10, 16}, OriginPoint{5, 8}}},
		SpritesetArea{GridSize{11, 16}, GridTileIndex{2, 0}, SpriteArea{IntArea{0, 0, 10, 16}, OriginPoint{5, 8}}}
	}}});
}

void GameEngine::initializeTilemapEditor() noexcept
{
	mTilemapEditor.initialize(mResourceManager.getTexture(TextureIdentifiers::Scenery));
}

void GameEngine::initializeCollisionHandlers() noexcept
{
	mCollisionModule.addHandler<MarioCollisionHandler>();
	mCollisionModule.addHandler<EnemyCollisionHandler>();
}

void GameEngine::initializeGameState() noexcept
{
	mGameStateManager.registerState<InitialGameState>(GameStateIdentifiers::Initial);
	mGameStateManager.pushState(GameStateIdentifiers::Initial);
}

void GameEngine::loadResources() noexcept
{
	loadFonts();
	loadTextures();
}

void GameEngine::loadFonts() noexcept
{
	mResourceManager.addFont(FontIdentifiers::Roboto, ResourcePaths::Fonts::Roboto);
}

void GameEngine::loadTextures() noexcept
{
	mResourceManager.addTexture(TextureIdentifiers::Enemies, ResourcePaths::Textures::Enemies);
	mResourceManager.addTexture(TextureIdentifiers::Items, ResourcePaths::Textures::Items);
	mResourceManager.addTexture(TextureIdentifiers::Mario, ResourcePaths::Textures::Mario);
	mResourceManager.addTexture(TextureIdentifiers::Scenery, ResourcePaths::Textures::Scenery);
	mResourceManager.addTexture(TextureIdentifiers::Scenery, ResourcePaths::Textures::Logo);
}
