#pragma once

enum class TileAttributes
{
	Destroyable	= 1 << 0,
	Visible		= 1 << 1,
	Deadly		= 1 << 2,
	Solid		= 1 << 3
};
