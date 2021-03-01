#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"
#include "MarioCollisionHandler.hpp"
#include "EnemyCollisionHandler.hpp"

GameEngine::GameEngine() noexcept :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mFramerate{0u},
	mGameObjectManager{mGraphicsScene},
	mGameContextData{mResourceManager, mSpritesetManager, mGameObjectManager, mTilemapView},
	mGameStateManager{mGameContextData},
	mFramerateTextVisible{false}
{
	mRenderWindow.setKeyRepeatEnabled(false);
}

int GameEngine::run() noexcept
{
	if (!loadResources())
	{
		return 1;
	}

	initializeFramerateText();
	initializeSpritesets();
	initializeTilemapEditor();
	initializeCollisionHandlers();

	executeMainLoop();

	return 0;
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
				mFramerateTextVisible = !mFramerateTextVisible;
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
	if (mFramerateTextVisible)
	{
		mFramerate++;
	}

	mRenderWindow.clear();

	mRenderWindow.draw(mTilemapView);
	mRenderWindow.draw(mGraphicsScene);

	if (mFramerateTextVisible)
	{
		mRenderWindow.setView(mRenderWindow.getDefaultView());
		mRenderWindow.draw(mFramerateText);
	}

	mRenderWindow.display();
}

void GameEngine::executeMainLoop() noexcept
{
	const auto frameTime = sf::seconds(1.0f / 60u);
	const auto framerateTextUpdateTime = sf::seconds(1.0f);
	const auto threadSleepTime = sf::milliseconds(10);

	sf::Clock clock{};

	sf::Time elapsedFrameUpdateTime{};
	sf::Time elapsedFramerateTextUpdateTime{};

	initializeGameState();

	while (isRunning())
	{
		bool renderFrame{false};

		const auto deltaTime = clock.restart();

		elapsedFrameUpdateTime += deltaTime;
		elapsedFramerateTextUpdateTime += deltaTime;

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

		if (elapsedFramerateTextUpdateTime > framerateTextUpdateTime)
		{
			const auto framerateDisplayText = std::to_string(mFramerate);

			mFramerateText.setString(framerateDisplayText);
		}

		if (!renderFrame)
		{
			sf::sleep(threadSleepTime);
		}
	}

	mRenderWindow.close();
}

void GameEngine::initializeFramerateText() noexcept
{
	mFramerateText.setPosition(4.0f, 4.0f);
	mFramerateText.setFont(mResourceManager.getFont(FontIdentifiers::Roboto));
	mFramerateText.setCharacterSize(12u);
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

bool GameEngine::loadResources() noexcept
{
	if (!loadFonts())
	{
		return false;
	}

	if (!loadTextures())
	{
		return false;
	}
	
	return true;
}

bool GameEngine::loadFonts() noexcept
{
	if (!mResourceManager.loadFont(FontIdentifiers::Roboto, ResourcePaths::Fonts::Roboto))
	{
		return false;
	}

	return true;
}

bool GameEngine::loadTextures() noexcept
{
	if (!mResourceManager.loadTexture(TextureIdentifiers::Enemies, ResourcePaths::Textures::Enemies))
	{
		return false;
	}

	if (!mResourceManager.loadTexture(TextureIdentifiers::Items, ResourcePaths::Textures::Items))
	{
		return false;
	}

	if (!mResourceManager.loadTexture(TextureIdentifiers::Mario, ResourcePaths::Textures::Mario))
	{
		return false;
	}

	if (!mResourceManager.loadTexture(TextureIdentifiers::Scenery, ResourcePaths::Textures::Scenery))
	{
		return false;
	}

	if (!mResourceManager.loadTexture(TextureIdentifiers::Logo, ResourcePaths::Textures::Logo))
	{
		return false;
	}

	return true;
}
