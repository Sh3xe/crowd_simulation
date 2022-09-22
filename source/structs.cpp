#include "structs.hpp"

Vec2 &Vec2::operator+=( const Vec2 &v )
{
	x += v.x;
	y += v.y;
	return *this;
}

Vec2 &Vec2::operator-=( const Vec2 &v )
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2 &Vec2::operator*=( double f )
{
	x *= f;
	y *= f;
	return *this;
}

Vec2 &Vec2::operator/=( double f )
{
	x /= f;
	y /= f;
	return *this;
}

Vec2 operator+( const Vec2 &v1, const Vec2 &v2 )
{
	Vec2 ret = v1;
	ret += v2;
	return ret;
}

Vec2 operator-( const Vec2 &v1, const Vec2 &v2 )
{
	Vec2 ret = v1;
	ret -= v2;
	return ret;
}

Vec2 operator*( const Vec2 &v, double f )
{
	Vec2 ret = v;
	ret *= f;
	return ret;
}

Vec2 operator/( const Vec2 &v, double f )
{
	Vec2 ret = v;
	ret /= f;
	return ret;
}

double dot( const Vec2 &v1, const Vec2 &v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}