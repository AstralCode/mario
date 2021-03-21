#pragma once

#include <map>
#include <memory>

#include "Entity.hpp"
#include "EntityState.hpp"

template <typename TEntity, typename TStates>
class EntityStateMachine final
{
public:
	template <typename TDerivedState>
	void registerState(const TStates identifier) noexcept;

	void setCurrentState(TEntity& entity, const TStates identifier);

	EntityState<TEntity>& getCurrentState() noexcept;
	const EntityState<TEntity>& getCurrentState() const noexcept;

private:
	std::map<TStates, std::unique_ptr<EntityState<TEntity>>> mStates;

	EntityState<TEntity>* mCurrentState;
};

template <typename TEntity, typename TStates>
template <typename TDerivedState>
inline void EntityStateMachine<TEntity, TStates>::registerState(const TStates identifier) noexcept
{
	static_assert(std::is_base_of_v<EntityState<TEntity>, TDerivedState>, "TDerivedState must derived from EntityState class");

	mStates.emplace(identifier, std::make_unique<TDerivedState>());
}

template <typename TEntity, typename TStates>
inline void EntityStateMachine<TEntity, TStates>::setCurrentState(TEntity& entity, const TStates identifier)
{
	mCurrentState = mStates.at(identifier).get();
	mCurrentState->onSet(entity);
}

template <typename TEntity, typename TStates>
inline EntityState<TEntity>& EntityStateMachine<TEntity, TStates>::getCurrentState() noexcept
{
	return *mCurrentState;
}

template <typename TEntity, typename TStates>
inline const EntityState<TEntity>& EntityStateMachine<TEntity, TStates>::getCurrentState() const noexcept
{
	return *mCurrentState;
}
