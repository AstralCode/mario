#pragma once

#include "ItemBuilder.hpp"

class ResourceContainer;
class SpritesetContainer;
class EntityContainer;

class CoinBuilder final : public ItemBuilder
{
public:
	CoinBuilder(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	void create(EntityContainer& items) noexcept;

	void buildTexture() noexcept override;
	void buildComponents() noexcept override;

	void buildActiveAnimation() noexcept override;
	void buildPickupAnimation() noexcept override;

	void buildState() noexcept override;

	Item* getItem() const noexcept;

private:
	const ResourceContainer& mResources;
	const SpritesetContainer& mSpritesets;

	Item* mItem;
};

