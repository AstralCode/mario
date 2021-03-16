#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "ResourceLoader.hpp"
#include "InitialGameState.hpp"

GameEngine::GameEngine() noexcept :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mGameStateManager{mResources, mSpritesets, mScene},
	mFramerate{0u},
	mFramerateTextVisible{false}
{
	mRenderWindow.setKeyRepeatEnabled(false);
}

int GameEngine::run() noexcept
{
	loadResources();

	initializeFramerateText();
	initializeSpritesets();

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
		mScene.receiveEvents(event);
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

void GameEngine::processLogic(const sf::Time& fixedFrameTime) noexcept
{
	mScene.update(fixedFrameTime);

	mGameStateManager.processLogic(fixedFrameTime);
	mGameStateManager.executeRequests();
}

void GameEngine::processRender() noexcept
{
	mFramerate++;

	mRenderWindow.clear();
	mRenderWindow.draw(mScene);

	if (mFramerateTextVisible)
	{
		mRenderWindow.setView(mRenderWindow.getDefaultView());
		mRenderWindow.draw(mFramerateText);
	}

	mRenderWindow.display();
}

void GameEngine::loadResources()
{
	loadFonts();
	loadTextures();
}

void GameEngine::loadFonts()
{
	mResources.addFont(FontIdentifiers::Roboto, ResourceLoader::loadFont(ResourcePaths::Fonts::Roboto));
}

void GameEngine::loadTextures()
{
	mResources.addTexture(TextureIdentifiers::Enemies, ResourceLoader::loadTexture(ResourcePaths::Textures::Enemies));
	mResources.addTexture(TextureIdentifiers::Items, ResourceLoader::loadTexture(ResourcePaths::Textures::Items));
	mResources.addTexture(TextureIdentifiers::Mario, ResourceLoader::loadTexture(ResourcePaths::Textures::Mario));
	mResources.addTexture(TextureIdentifiers::Scenery, ResourceLoader::loadTexture(ResourcePaths::Textures::Scenery));
	mResources.addTexture(TextureIdentifiers::Logo, ResourceLoader::loadTexture(ResourcePaths::Textures::Logo));
}

void GameEngine::initializeFramerateText() noexcept
{
	mFramerateText.setPosition(4.0f, 4.0f);
	mFramerateText.setFont(mResources.getFont(FontIdentifiers::Roboto));
	mFramerateText.setCharacterSize(12u);
}

void GameEngine::initializeSpritesets() noexcept
{
	auto& marioSpriteset = mSpritesets.create(SpritesetIdentifiers::Mario);
	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Stand, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Move, SpritesetRegion{GridSize{32, 32}, GridTileIndex{1, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 26, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 26, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Slide, SpritesetRegion{GridSize{32, 32}, GridTileIndex{8, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(SpritesetRegionIdentifiers::Mario::Jump, SpritesetRegion{GridSize{32, 32}, GridTileIndex{4, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	auto& enemySpriteset = mSpritesets.create(SpritesetIdentifiers::Enemy);
	enemySpriteset.addRegion(SpritesetRegionIdentifiers::Goomba::Move, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 32, 32}}
	}}});

	enemySpriteset.addRegion(SpritesetRegionIdentifiers::Goomba::Dead, {GridSize{32, 32}, {2, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 16, 32, 16}}
	}}});

	auto& blocksSpriteset = mSpritesets.create(SpritesetIdentifiers::Blocks);
	blocksSpriteset.addRegion(SpritesetRegionIdentifiers::Blocks::QuestionMarkBox, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{0, 0, 32, 32}}
	}}});

	blocksSpriteset.addRegion(SpritesetRegionIdentifiers::Blocks::WaterQuestionMarkBox, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 1}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{0, 0, 32, 32}}
	}}});

	auto& itemSpriteset = mSpritesets.create(SpritesetIdentifiers::Items);
	itemSpriteset.addRegion(SpritesetRegionIdentifiers::Items::Coin, SpritesetRegion{GridSize{32, 32}, GridTileIndex{4, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{6, 2, 20, 28}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{6, 2, 20, 28}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{6, 2, 20, 28}}
	}}});

	itemSpriteset.addRegion(SpritesetRegionIdentifiers::Items::ScoreCoin, SpritesetRegion{GridSize{32, 32}, GridTileIndex{9, 3}, {{
		SpritesetArea{GridSize{11, 16}, GridTileIndex{0, 0}, SpriteArea{0, 0, 10, 16}},
		SpritesetArea{GridSize{11, 16}, GridTileIndex{1, 0}, SpriteArea{0, 0, 10, 16}},
		SpritesetArea{GridSize{11, 16}, GridTileIndex{2, 0}, SpriteArea{0, 0, 10, 16}}
	}}});
}

void GameEngine::initializeGameState() noexcept
{
	mGameStateManager.registerState<InitialGameState>(GameStateIdentifiers::Initial);
	mGameStateManager.pushState(GameStateIdentifiers::Initial);
}

void GameEngine::executeMainLoop() noexcept
{
	const auto fixedFrameTime = sf::seconds(1.0f / 60u);
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

		while (elapsedFrameUpdateTime > fixedFrameTime)
		{
			processEvents();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			processLogic(fixedFrameTime);

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			renderFrame = true;

			elapsedFrameUpdateTime -= fixedFrameTime;
		}

		if (renderFrame)
		{
			processRender();
		}

		updateFramerateText(elapsedFramerateTextUpdateTime);

		if (!renderFrame)
		{
			sf::sleep(threadSleepTime);
		}
	}

	mRenderWindow.close();
}

void GameEngine::updateFramerateText(sf::Time& elapsedUpdateTime) noexcept
{
	const auto updateTime = sf::seconds(1.0f);

	if (const auto text = std::to_string(mFramerate); elapsedUpdateTime > updateTime)
	{
		mFramerateText.setString("FPS: " + text);

		elapsedUpdateTime = sf::Time::Zero;
		mFramerate = 0u;
	}
}
