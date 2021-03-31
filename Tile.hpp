#pragma once

#include "TileIndex.hpp"
#include "Flagset.hpp"
#include "Area.hpp"

class Tile final
{
public:
	enum class TraitType
	{
		Collider
	};

	using Identifier = unsigned char;
	using Traits = Flags<TraitType>;

	Tile() noexcept;

	void setIdentifier(const Identifier identifier) noexcept;

	void setTrait(const TraitType trait) noexcept;
	void setTraits(const Traits& traits) noexcept;

	void setIndex(const TileIndex& index) noexcept;
	void setArea(const FloatArea& area) noexcept;

	Identifier getIdentifier() const noexcept;

	const TileIndex& getIndex() const noexcept;
	const Traits& getTraits() const noexcept;
	const FloatArea& getArea() const noexcept;

	bool hasTrait(const TraitType trait) const noexcept;

private:
	Identifier mIdentifier;
	TileIndex mIndex;
	Traits mTraits;
	FloatArea mArea;
};
