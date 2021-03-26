#pragma once

#include <bitset>
#include <type_traits>
#include <initializer_list>

template <typename TEnum, size_t TEnumSize>
class Flagset
{
public:
	Flagset() = default;
	Flagset(std::initializer_list<TEnum> flags) noexcept;

	void set(const TEnum flag) noexcept;
	void set(std::initializer_list<TEnum> flags) noexcept;
	void set(const Flagset& flags) noexcept;

	void unset(const TEnum flag) noexcept;
	void unset(std::initializer_list<TEnum> flags) noexcept;
	void unset(const Flagset& flags) noexcept;

	void reset() noexcept;

	bool isSet(const TEnum flag) const noexcept;

	bool isSetAnyOf(const Flagset& flags) const noexcept;
	bool isSetAllOf(const Flagset& flags) const noexcept;
	bool isSetNoneOf(const Flagset& flags) const noexcept;

	bool isEmpty() const noexcept;

private:
	std::bitset<TEnumSize> mFlagset;
};

template <typename TEnum, size_t TEnumSize>
inline Flagset<TEnum, TEnumSize>::Flagset(std::initializer_list<TEnum> flags) noexcept
{
	set(flags);
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::set(const TEnum flag) noexcept
{
	mFlagset.set(static_cast<int>(flag));
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::set(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		set(flag);
	}
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::set(const Flagset& flags) noexcept
{
	mFlagset |= flags.mFlagset;
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::unset(const TEnum flag) noexcept
{
	mFlagset.set(static_cast<int>(flag), false);
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::unset(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		unset(flag);
	}
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::unset(const Flagset& flags) noexcept
{
	mFlagset |= ~flags.mFlagset;
}

template <typename TEnum, size_t TEnumSize>
inline void Flagset<TEnum, TEnumSize>::reset() noexcept
{
	mFlagset.reset();
}

template <typename TEnum, size_t TEnumSize>
inline bool Flagset<TEnum, TEnumSize>::isSet(const TEnum flag) const noexcept
{
	return mFlagset.test(static_cast<int>(flag));
}

template <typename TEnum, size_t TEnumSize>
inline bool Flagset<TEnum, TEnumSize>::isSetAnyOf(const Flagset& flags) const noexcept
{
	return (mFlagset & flags.mFlagset) > 0;
}

template <typename TEnum, size_t TEnumSize>
inline bool Flagset<TEnum, TEnumSize>::isSetAllOf(const Flagset& flags) const noexcept
{
	return (mFlagset & flags.mFlagset) == flags.mFlagset;
}

template <typename TEnum, size_t TEnumSize>
inline bool Flagset<TEnum, TEnumSize>::isSetNoneOf(const Flagset& flags) const noexcept
{
	return !isSetAnyOf(flags);
}

template <typename TEnum, size_t TEnumSize>
inline bool Flagset<TEnum, TEnumSize>::isEmpty() const noexcept
{
	return mFlagset.count() == 0u;
}
