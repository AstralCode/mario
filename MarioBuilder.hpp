#pragma once

#include "HeroBuilder.hpp"

class ResourceContainer;
class SpritesetContainer;
class EntityContainer;

class MarioBuilder final : public HeroBuilder
{
public:
	MarioBuilder(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	void create(EntityContainer& heroes) noexcept;

	void buildTexture() noexcept override;
	void buildComponents() noexcept override;

	void buildStandAnimation() noexcept override;
	void buildMoveAnimation() noexcept override;
	void buildJumpAnimation() noexcept override;
	void buildSlideAnimation() noexcept override;
	void buildLoseAnimation() noexcept override;

	void buildStates() noexcept override;

	Hero* getHero() const noexcept;

private:
	const ResourceContainer& mResources;
	const SpritesetContainer& mSpritesets;

	Hero* mMario;
};
