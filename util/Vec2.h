#pragma once

#include <cmath>

// ２次元ベクトル
class Vec2
{
public:
	float x;
	float y;
public:
	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vec2( float x, float y ) : x(x), y(y)
	{
	}
	virtual ~Vec2() {}
	
	Vec2& operator = (const Vec2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}
#if false
	bool operator == (const Vec2& vec)
	{
		return ((x == vec.x) && (y == vec.y));
	}
	bool operator != (const Vec2& vec)
	{
		return ((x != vec.x) || (y != vec.y));
	}
#endif

	const Vec2& operator+() const
	{
		return *this;
	}
	Vec2& operator+()
	{
		return *this;
	}
	Vec2 operator-() const
	{
		return Vec2(-x, -y);
	}

	Vec2& operator+=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	Vec2 operator+(const Vec2& vec) const
	{
		return Vec2(x + vec.x, y + vec.y);
	}
	Vec2& operator+(Vec2&& vec) const
	{
		return vec += *this;
	}

	Vec2& operator-=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	Vec2 operator-(const Vec2& vec) const
	{
		return Vec2(x - vec.x, y - vec.y);
	}
	Vec2& operator-(Vec2&& vec) const
	{
		vec.x = -vec.x;
		vec.y = -vec.y;
		vec += *this;
		return vec;
	}

	Vec2& operator*=(float k)
	{
		x *= k;
		y *= k;
		return *this;
	}
	Vec2 operator*(float k)
	{
		return Vec2(x*k, y*k);
	}

	Vec2& operator/=(float k)
	{
		x /= k;
		y /= k;
		return *this;
	}
	Vec2 operator/(float k) const
	{
		return Vec2(x / k, y / k);
	}

	// 長さ
	float length() const
	{
		// 自身との内積の平方根が長さ
		return std::sqrtf(this->dot(*this));
	}
	// 正規化
	Vec2 normalize() const
	{
		const float len = length();
		if (len == 0)
		{
			return *this;
		}
		return (*this / len);
	}
	// 角度

	// 内積
	float dot( const Vec2& vec ) const
	{
		return (x * vec.x) + (y * vec.y);
	}
	// 外積
	float cross( const Vec2& vec ) const
	{
		return (x * vec.y) - (y * vec.x);
	}

	bool isZero()
	{
		return ((x == 0.0f) && (y == 0.0f));
	}
};
