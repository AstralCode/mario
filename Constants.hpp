#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace Constants
{
namespace ResourcePaths
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
constexpr const auto TileSize = 32.0f;
constexpr const auto Friction = 0.926f;
constexpr const auto Gravity = 1800.0f;
}
namespace GameObjects
{
namespace Mario
{
constexpr const auto AccelerationX = World::TileSize * 20.0f;
constexpr const auto MaxVelocityX = World::TileSize * 10.0f;
constexpr const auto MaxVelocityY = World::TileSize * 26.0f;
constexpr const auto MoveAnimationDuration = 0.25f;
constexpr const auto Up = sf::Keyboard::W;
constexpr const auto Down = sf::Keyboard::S;
constexpr const auto Left = sf::Keyboard::A;
constexpr const auto Right = sf::Keyboard::D;
}
namespace Creature
{
constexpr const auto AccelerationX = World::TileSize * 10.0f;
constexpr const auto MaxVelocityX = World::TileSize * 1.5f;
constexpr const auto MoveAnimationDuration = 0.25f;
}
namespace Items
{
constexpr const auto ShineAnimationDuration = 0.25f;
constexpr const auto ShineAnimationDelay = 0.25f;
}
}
}
