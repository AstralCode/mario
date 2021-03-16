#pragma once

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
namespace GameObjects
{
namespace Mario
{
constexpr const auto MaxVelocityX = 32.0f * 20.0f;
constexpr const auto MaxVelocityY = 32.0f * 20.0f;
constexpr const auto MoveAnimationDuration = 0.25f;
}
namespace Creature
{
constexpr const auto MaxVelocityX = 32.0f * 8.0f;
constexpr const auto MaxVelocityY = 32.0f * 8.0f;
constexpr const auto MoveAnimationDuration = 0.25f;
}
namespace Items
{
constexpr const auto ShineAnimationDuration = 0.25f;
constexpr const auto ShineAnimationDelay = 0.25f;
}
}
}
