#include "GameEngine.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "Constants.hpp"
#include "ResourceLoader.hpp"
#include "InitialGameState.hpp"

GameEngine::GameEngine() noexcept :
	mRenderWindow{{640u, 480u}, "Mario", sf::Style::Titlebar | sf::Style::Close},
	mWorld{mResources, mSpritesets},
	mGameStateManager{mWorld},
	mFramerate{0u},
	mIsFramerateTextVisible{true}
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
		mWorld.receiveEvents(event);
		mGameStateManager.processEvents(event);

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F1)
			{
				mIsFramerateTextVisible = !mIsFramerateTextVisible;
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

void GameEngine::processLogic(const sf::Time& dt) noexcept
{
	mWorld.update(dt);

	mGameStateManager.processLogic(dt);
	mGameStateManager.executeRequests();
}

void GameEngine::processRender() noexcept
{
	mFramerate++;

	mRenderWindow.clear();
	mRenderWindow.draw(mWorld);

	if (mIsFramerateTextVisible)
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
	mResources.addFont(FontId::Roboto, ResourceLoader::loadFont(Constants::Resources::Fonts::Roboto));
}

void GameEngine::loadTextures()
{
	mResources.addTexture(TextureId::Enemies, ResourceLoader::loadTexture(Constants::Resources::Textures::Enemies));
	mResources.addTexture(TextureId::Items, ResourceLoader::loadTexture(Constants::Resources::Textures::Items));
	mResources.addTexture(TextureId::Hero, ResourceLoader::loadTexture(Constants::Resources::Textures::Hero));
	mResources.addTexture(TextureId::Scenery, ResourceLoader::loadTexture(Constants::Resources::Textures::Scenery));
	mResources.addTexture(TextureId::Logo, ResourceLoader::loadTexture(Constants::Resources::Textures::Logo));
}

void GameEngine::initializeFramerateText() noexcept
{
	mFramerateText.setPosition(4.0f, 4.0f);
	mFramerateText.setFont(mResources.getFont(FontId::Roboto));
	mFramerateText.setCharacterSize(12u);
}

void GameEngine::initializeSpritesets() noexcept
{
	auto& marioSpriteset = mSpritesets.getMarioSpriteset();
	marioSpriteset.addRegion(MarioSpritesetRegions::Stand, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(MarioSpritesetRegions::Move, SpritesetRegion{GridSize{32, 32}, GridTileIndex{1, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 26, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 26, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(MarioSpritesetRegions::Slide, SpritesetRegion{GridSize{32, 32}, GridTileIndex{8, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(MarioSpritesetRegions::Jump, SpritesetRegion{GridSize{32, 32}, GridTileIndex{4, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 24, 32}}
	}}});

	marioSpriteset.addRegion(MarioSpritesetRegions::Lose, SpritesetRegion{GridSize{32, 32}, GridTileIndex{7, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 4, 28, 28}}
	}}});

	auto& enemySpriteset = mSpritesets.getGoombaSpriteset();
	enemySpriteset.addRegion(GoombaSpritesetRegions::Move, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 32, 32}}
	}}});

	enemySpriteset.addRegion(GoombaSpritesetRegions::Lose, {GridSize{32, 32}, {2, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 16, 32, 16}}
	}}});

	auto& itemSpriteset = mSpritesets.getItemSpriteset();
	itemSpriteset.addRegion(ItemSpritesetRegions::Coin, SpritesetRegion{GridSize{32, 32}, GridTileIndex{4, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{6, 2, 20, 28}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{6, 2, 20, 28}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{6, 2, 20, 28}}
	}}});

	itemSpriteset.addRegion(ItemSpritesetRegions::CoinPickup, SpritesetRegion{GridSize{32, 32}, GridTileIndex{4, 4}, {{
		SpritesetArea{GridSize{16, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 16, 32}},
		SpritesetArea{GridSize{16, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 16, 32}},
		SpritesetArea{GridSize{16, 32}, GridTileIndex{2, 0}, SpriteArea{0, 0, 16, 32}},
		SpritesetArea{GridSize{16, 32}, GridTileIndex{3, 0}, SpriteArea{0, 0, 16, 32}}
	}}});

	itemSpriteset.addRegion(ItemSpritesetRegions::QBox, SpritesetRegion{GridSize{32, 32}, GridTileIndex{0, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{1, 0}, SpriteArea{0, 0, 32, 32}},
		SpritesetArea{GridSize{32, 32}, GridTileIndex{2, 0}, SpriteArea{0, 0, 32, 32}}
	}}});

	itemSpriteset.addRegion(ItemSpritesetRegions::QBoxEmpty, SpritesetRegion{GridSize{32, 32}, GridTileIndex{3, 0}, {{
		SpritesetArea{GridSize{32, 32}, GridTileIndex{0, 0}, SpriteArea{0, 0, 32, 32}}
	}}});

	itemSpriteset.addRegion(ItemSpritesetRegions::ScoreCoin, SpritesetRegion{GridSize{32, 32}, GridTileIndex{9, 3}, {{
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
	const auto dt = sf::seconds(1.0f / 60u);
	const auto threadSleepTime = sf::milliseconds(10);

	sf::Clock clock{};

	sf::Time elapsedFrameUpdateTime{};
	sf::Time elapsedFramerateTextUpdateTime{};

	initializeGameState();

	while (isRunning())
	{
		bool isRenderFrame{false};

		const auto deltaTime = clock.restart();

		elapsedFrameUpdateTime += deltaTime;
		elapsedFramerateTextUpdateTime += deltaTime;

		while (elapsedFrameUpdateTime > dt)
		{
			processEvents();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			processLogic(dt);

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			isRenderFrame = true;

			elapsedFrameUpdateTime -= dt;
		}

		if (isRenderFrame)
		{
			processRender();
		}

		updateFramerateText(elapsedFramerateTextUpdateTime);

		if (!isRenderFrame)
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
