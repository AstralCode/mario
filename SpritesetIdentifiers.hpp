#pragma once

#include <string>

namespace SpritesetIdentifiers
{
	constexpr const auto Mario = "mario";
	constexpr const auto Enemy = "enemy";
	constexpr const auto Items = "items";
	constexpr const auto Blocks = "blocks";
}

namespace SpritesetRegionIdentifiers
{
	namespace Mario
	{
		constexpr const auto Stand = "stand";
		constexpr const auto Move = "move";
		constexpr const auto Slide = "slide";
		constexpr const auto Jump = "jump";
	}

	namespace Goomba
	{
		constexpr const auto Move = "move";
		constexpr const auto Dead = "dead";
	}
	namespace Items
	{
		constexpr const auto Coin = "coin";
		constexpr const auto ScoreCoin = "score-coin";
	}
	namespace Blocks
	{
		constexpr const auto QuestionMarkBox = "question-mark-box";
		constexpr const auto WaterQuestionMarkBox = "water-question-mark-box";
	}
}
