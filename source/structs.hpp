#pragma once

#include <vector>

struct Vec2
{
	double x, y;

	Vec2 &operator+=( const Vec2 &v );
	Vec2 &operator-=( const Vec2 &v );
	Vec2 &operator*=( double f );
	Vec2 &operator/=( double f );
};

using Polygon = std::vector<Vec2>;

struct Rectangle
{
	Vec2 pos;
	Vec2 size;
};

struct Segment
{
	Vec2 p1, p2;
};

struct Line
{
	Vec2 p, v;
};

struct Circle
{
	Vec2 pos;
	double r;
};



Vec2 operator+( const Vec2 &v1, const Vec2 &v2 );
Vec2 operator-( const Vec2 &v1, const Vec2 &v2 );
Vec2 operator*( const Vec2 &v, double f );
Vec2 operator/( const Vec2 &v, double f );

double dot( const Vec2 &v1, const Vec2 &v2 );