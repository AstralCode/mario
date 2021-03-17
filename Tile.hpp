#pragma once

#include "Flags.hpp"
#include "Area.hpp"

struct Tile
{
	enum class Attributes
	{
		None,
		Collider
	};

	struct Index
	{
		using Type = int;

		Type row{0};
		Type column{0};

		constexpr bool operator==(const Index& index) const noexcept;
	};

	using Identifier = unsigned char;
	using AttributeFlags = Flags<Attributes, 1u>;

	Index index{};
	Identifier identifier{0u};
	AttributeFlags attributes{Attributes::None};
	FloatArea area{};
};

inline constexpr bool Tile::Index::operator==(const Index& index) const noexcept
{
	return (row == index.row && column == index.column);
}
