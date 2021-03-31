#pragma once

#include <bitset>
#include <type_traits>
#include <initializer_list>

template <typename TEnum>
class Flags
{
public:
	Flags() = default;
	Flags(std::initializer_list<TEnum> flags) noexcept;

	void set(const TEnum flag) noexcept;
	void set(std::initializer_list<TEnum> flags) noexcept;
	void set(const Flags& flags) noexcept;

	void unset(const TEnum flag) noexcept;
	void unset(std::initializer_list<TEnum> flags) noexcept;
	void unset(const Flags& flags) noexcept;

	void reset() noexcept;

	bool isSet(const TEnum flag) const noexcept;

	bool isSetAnyOf(const Flags& flags) const noexcept;
	bool isSetAllOf(const Flags& flags) const noexcept;
	bool isSetNoneOf(const Flags& flags) const noexcept;

	bool isEmpty() const noexcept;

private:
	std::bitset<32u> mFlagset;
};

template <typename TEnum>
inline Flags<TEnum>::Flags(std::initializer_list<TEnum> flags) noexcept
{
	set(flags);
}

template <typename TEnum>
inline void Flags<TEnum>::set(const TEnum flag) noexcept
{
	mFlagset.set(static_cast<int>(flag));
}

template <typename TEnum>
inline void Flags<TEnum>::set(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		set(flag);
	}
}

template <typename TEnum>
inline void Flags<TEnum>::set(const Flags& flags) noexcept
{
	mFlagset |= flags.mFlagset;
}

template <typename TEnum>
inline void Flags<TEnum>::unset(const TEnum flag) noexcept
{
	mFlagset.set(static_cast<int>(flag), false);
}

template <typename TEnum>
inline void Flags<TEnum>::unset(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		unset(flag);
	}
}

template <typename TEnum>
inline void Flags<TEnum>::unset(const Flags& flags) noexcept
{
	mFlagset |= ~flags.mFlagset;
}

template <typename TEnum>
inline void Flags<TEnum>::reset() noexcept
{
	mFlagset.reset();
}

template <typename TEnum>
inline bool Flags<TEnum>::isSet(const TEnum flag) const noexcept
{
	return mFlagset.test(static_cast<int>(flag));
}

template <typename TEnum>
inline bool Flags<TEnum>::isSetAnyOf(const Flags& flags) const noexcept
{
	return (mFlagset & flags.mFlagset) > 0;
}

template <typename TEnum>
inline bool Flags<TEnum>::isSetAllOf(const Flags& flags) const noexcept
{
	return (mFlagset & flags.mFlagset) == flags.mFlagset;
}

template <typename TEnum>
inline bool Flags<TEnum>::isSetNoneOf(const Flags& flags) const noexcept
{
	return !isSetAnyOf(flags);
}

template <typename TEnum>
inline bool Flags<TEnum>::isEmpty() const noexcept
{
	return mFlagset.count() == 0u;
}
