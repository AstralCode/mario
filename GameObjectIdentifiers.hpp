#pragma once

#include "Flags.hpp"

enum class GameObjectIdentifiers
{
	Mario,
	Goomba,
	Coin,
	ScoreCoin,
	QuestionMarkBox
};

using GameObjectIdentifierFlags = Flags<GameObjectIdentifiers, 5u>;
