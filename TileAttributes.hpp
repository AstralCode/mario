#pragma once

#include "Flags.hpp"

enum class TileAttributes
{
	Solid
};

using TileAttributeFlags = Flags<TileAttributes, 1u>;
