#pragma once

enum class FontIdentifiers
{
	Roboto
};

enum class TextureIdentifiers
{
	Enemies,
	Mario,
	Scenery
};

enum class MusicIdentifiers
{

};

namespace ResourcePaths
{
namespace Fonts
{
constexpr const auto Roboto = "Resources/Fonts/Roboto.ttf";
}
namespace Textures
{
constexpr const auto Enemies = "Resources/Textures/Enemies.png";
constexpr const auto Mario = "Resources/Textures/Mario.png";
constexpr const auto Scenery = "Resources/Textures/Scenery.png";
}
}
