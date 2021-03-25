#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace Constants
{
	namespace Resources
	{
		namespace Fonts
		{
			constexpr const auto Roboto = "Resources/Fonts/Roboto.ttf";
		}
		namespace Textures
		{
			constexpr const auto Enemies = "Resources/Textures/Enemies.png";
			constexpr const auto Items = "Resources/Textures/Items.png";
			constexpr const auto Mario = "Resources/Textures/Mario.png";
			constexpr const auto Scenery = "Resources/Textures/Scenery.png";
			constexpr const auto Logo = "Resources/Textures/Logo.png";
		}
	}
	namespace World
	{
		namespace Tilemap
		{
			constexpr const auto TileSize = 32.0f;
		}
		namespace Physics
		{
			constexpr const auto Friction = 0.92f;
			constexpr const auto Gravity = 1800.0f;
		}
		namespace Mario
		{
			constexpr const auto AccelerationX = World::Tilemap::TileSize * 20.0f;
			constexpr const auto MaxVelocityX = World::Tilemap::TileSize * 10.0f;
			constexpr const auto MaxVelocityY = World::Tilemap::TileSize * 24.0f;
			constexpr const auto StopVelocityX = 12.0f;
			constexpr const auto MoveAnimationDuration = 0.25f;
			constexpr const auto LoseAnimationStart = 0.5f;
			constexpr const auto LoseAnimationEnd = 2.0f;
			constexpr const auto Up = sf::Keyboard::W;
			constexpr const auto Down = sf::Keyboard::S;
			constexpr const auto Left = sf::Keyboard::A;
			constexpr const auto Right = sf::Keyboard::D;
		}
		namespace Enemy
		{
			constexpr const auto AccelerationX = World::Tilemap::TileSize * 5.0f;
			constexpr const auto MaxVelocityX = World::Tilemap::TileSize * 5.0f;
			constexpr const auto MoveAnimationDuration = 0.25f;
			constexpr const auto LoseAnimationDuration = 1.0f;
		}
		namespace Items
		{
			constexpr const auto ShineAnimationDuration = 0.25f;
			constexpr const auto ShineAnimationDelay = 0.25f;
			constexpr const auto PickupAnimationDuration = 0.15f;
			constexpr const auto PickupVelocityY = World::Tilemap::TileSize * 15.0f;
			constexpr const auto PickupAnimationEnd = 0.5f;
		}
	}
}
