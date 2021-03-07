#pragma once

template <typename T>
class Margins final
{
public:
	Margins();
	Margins(const T left, const T top, const T right, const T bottom) noexcept;

	void set(const T left, const T top, const T right, const T bottom) noexcept;

	void setLeft(const T left) noexcept;
	void setTop(const T top) noexcept;
	void setRight(const T right) noexcept;
	void setBottom(const T bottom) noexcept;

	T getLeft() const noexcept;
	T getTop() const noexcept;
	T getRight() const noexcept;
	T getBottom() const noexcept;

private:
	T mLeft;
	T mTop;
	T mRight;
	T mBottom;
};

template <typename T>
inline Margins<T>::Margins() :
	mLeft{0},
	mTop{0},
	mRight{0},
	mBottom{0}
{

}

template <typename T>
inline Margins<T>::Margins(const T left, const T top, const T right, const T bottom) noexcept
{
	mLeft = left;
	mTop = top;
	mRight = right;
	mBottom = bottom;
}

template <typename T>
inline void Margins<T>::set(const T left, const T top, const T right, const T bottom) noexcept
{
	mLeft = left;
	mTop = top;
	mRight = right;
	mBottom = bottom;
}

template <typename T>
inline void Margins<T>::setLeft(const T left) noexcept
{
	mLeft = left;
}

template <typename T>
inline void Margins<T>::setTop(const T top) noexcept
{
	mTop = top;
}

template <typename T>
inline void Margins<T>::setRight(const T right) noexcept
{
	mRight = right;
}

template <typename T>
inline void Margins<T>::setBottom(const T bottom) noexcept
{
	mBottom = bottom;
}

template <typename T>
inline T Margins<T>::getLeft() const noexcept
{
	return mLeft;
}

template <typename T>
inline T Margins<T>::getTop() const noexcept
{
	return mTop;
}

template <typename T>
inline T Margins<T>::getRight() const noexcept
{
	return mRight;
}

template <typename T>
inline T Margins<T>::getBottom() const noexcept
{
	return mBottom;
}

using IntMargins = Margins<int>;
using FloatMargins = Margins<float>;
