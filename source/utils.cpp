#include "utils.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <random>
#include <iostream>


static std::mt19937 engine;

float frand( float a, float b )
{
	std::uniform_real_distribution d(a, b);
	return d(engine);
}

int irand( int a, int b )
{
	std::uniform_int_distribution d(a, b);
	return d(engine);
}

// https://en.wikipedia.org/wiki/Fast_inverse_square_root
double Q_rsqrt( double number )
{
	long i;
	double x2, y;
	const double threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = * ( long * ) &y; // evil doubleing point bit level hacking
	i = 0x5f3759df - ( i >> 1 ); // what the fuck?
	y = * ( double * ) &i;
	y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration

	return y;
}

double determinant( Vec2 c1, Vec2 c2 )
{
	return c1.x * c2.y - c1.y * c2.x;
}

bool egalf( double a, double b, double t) {
	return (a > b - t) && (a < b + t);
}

/*
	resout le système d'equation:
	c1 X + c2 Y = rep 
*/
std::optional<Vec2> resolve_equation_sys( Vec2 c1, Vec2 c2, Vec2 rep )
{
	double det = determinant(c1, c2);
	
	if( egalf(det, 0.0, 0.001) )
		return {};

	return Vec2{ determinant(rep, c2) / det, determinant(c1, rep) / det };
}

std::optional<Vec2> resoudre_deg_2( double a, double b, double c )
{
	double delta = b*b -4*a*c;
	if( delta < 0 ) return {};

	delta = sqrt(delta);

	if( egalf(a, 0.0, 0.0001) ) return {};
	
	return Vec2{ (-b+delta)/(2*a), (-b-delta)/(2*a) };
}

double angle( Vec2 pos, Vec2 p1, Vec2 p2 )
{
	Vec2 v1 = p1 - pos, v2 = p2 - pos;
	return atan2( v2.y, v2.x ) - atan2( v1.y, v1.x );
}

double angle( Vec2 pos )
{
	return atan2( pos.y, pos.x );
}

std::optional<Vec2> custruct_normal( Vec2 v )
{
	if( egalf(v.x, 0.0, 0.0001) && egalf(v.y, 0.0, 1.0) )
		return {};
	
	if( egalf(v.x, 0.0, 0.0001) )
		return Vec2{ 1.0 ,-v.x/v.y };
	
	return Vec2{ -v.y/v.x, 1.0 };
}

double length( Vec2 &vec )
{
	return sqrt( vec.x*vec.x + vec.y*vec.y );
}

void normalize( Vec2 &vec )
{
	float l = length(vec);
	vec /= l;
}

void fast_normalize( Vec2 &vec )
{
	float one_over_length = Q_rsqrt( vec.x * vec.x + vec.y * vec.y );
	vec *= one_over_length;
}

bool collision( Circle s0, Circle s1 )
{
	return distance2(s0.pos, s1.pos) < (s0.r + s1.r)*(s0.r + s1.r);
}

std::optional<Vec2> intersection( Line d1, Line d2 )
{
	Vec2 p1 = d1.p, p2 = d2.p;
	auto n1 = custruct_normal(d1.v), n2 = custruct_normal(d2.v);

	if( !n1 || !n2 ) return {};
	
	Vec2 c1 = { n1.value().x, n2.value().x };
	Vec2 c2 = { n1.value().y, n2.value().y };
	Vec2 rep = { p1.x * n1.value().x + p1.y * n1.value().y, p2.x * n2.value().x + p2.y * n2.value().y };

	return resolve_equation_sys(c1, c2, rep);
}

std::optional<Vec2> intersection( Segment s1, Segment s2 )
{
	// on transforme nos segments en droite
	Line d1 { s1.p1, (s1.p2 - s1.p1) };
	Line d2 { s2.p1, (s2.p2 - s1.p1) };

	// on récupère l'intersection entre les deux droites
	auto inter = intersection( d1, d2 );
	if( !inter ) return {};

	// on vérifie que le point d'intersection se trouve bien sur les deux segments à la fois
	// pour ça, on effectue le produit scalaire entre (p1 - P) et (p2 - P)
	// s'il est négatif alors on est dans le segment, autrement on est en dehors
	double scal1 = dot( s1.p1 - inter.value(), s1.p2 - inter.value());
	double scal2 = dot( s2.p2 - inter.value(), s2.p2 - inter.value());

	if( scal1 > 0 || scal2 > 0 ) return {};

	return inter;
}

double distance2( Vec2 p1, Vec2 p2 )
{
	return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
}

double distance_rapide( Vec2 p1, Vec2 p2 )
{
	return 1 / Q_rsqrt( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) );
}

double distance( Vec2 p1, Vec2 p2 )
{
	return sqrt( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) );
}

std::optional<double> distance( Vec2 pos, Vec2 dir, Circle s )
{
	double a = dir.x*dir.x + dir.y*dir.y;
	double b = 2*(pos.y*dir.y - dir.y*s.pos.y + pos.x*dir.x - dir.x*s.pos.x);
	double c = -s.r*s.r + pos.x*pos.x + pos.y*pos.y + s.pos.x*s.pos.x + s.pos.y*s.pos.y - 2*pos.x*s.pos.x - 2*pos.y*s.pos.y;

	auto solutions = resoudre_deg_2(a, b, c);
/*
	std::cout << solutions.value().x <<  " " << solutions.value().y << std::endl;
	std::cout << a << " " << b << " " << c << std::endl;*/
	if(!solutions || (solutions.value().y < 0 && solutions.value().x < 0)) return {};
	
	Vec2 p1 = pos + dir * solutions.value().x;
	Vec2 p2 = pos + dir * solutions.value().y;
	
	double d1 = distance2( p1, pos );
	double d2 = distance2( p2, pos );

	if( d1 < d2 ) return sqrt(d1);
	
	return sqrt(d2);
}

std::optional<double> distance( Vec2 pos, Vec2 dir, Segment seg )
{
	Line d1 = {pos, dir}, d2 = { seg.p1, seg.p2 - seg.p1 };
	auto inter = intersection( d1, d2 );

	if(!inter) return {};

	// on vérifie que le point d'intersection se trouve bien sur les deux segments à la fois
	// pour ça, on effectue le produit scalaire entre (p1 - P) et (p2 - P)
	// s'il est négatif alors on est dans le segment, autrement on est en dehors
	double scal = dot( seg.p1 - inter.value(), seg.p2 - inter.value());

	if( scal > 0  || dot(dir, inter.value() - pos) < 0 ) return {};
	
	return distance(inter.value(), pos);
}

bool collision( Vec2 pos, Vec2 dir, Segment seg )
{
	Line d1 = {pos, dir}, d2 = { seg.p1, seg.p2 - seg.p1 };
	auto inter = intersection( d1, d2 );

	if(!inter) return false;

	// on vérifie que le point d'intersection se trouve bien sur les deux segments à la fois
	// pour ça, on effectue le produit scalaire entre (p1 - P) et (p2 - P)
	// s'il est négatif alors on est dans le segment, autrement on est en dehors
	double scal = dot( seg.p1 - inter.value(), seg.p2 - inter.value());

	if( scal > 0  || dot(dir, inter.value() - pos) < 0 ) return false;
	
	return true;
}


bool collision( Vec2 pt, Polygon pol )
{
	assert(pol.size() >= 2);

	// on compte le nombre de points d'intersections entre 
	// n'importe quelle droite qui part de pt et le polygone
	int intersection_count = 0;
	Vec2 dir = {0.0f, 1.0f};

	Vec2 &last = pol.back();
	for( auto &point: pol)
	{
		Segment seg = {last, point};
		if( collision(pt, dir, seg) ) ++intersection_count;
		last = point;
	}

	// il y a collision ssi ce nombre est impair
	return intersection_count % 2 == 1;
}

Vec2 closest( Vec2 pt, Polygon pol )
{
	assert(false);
	return {0, 0};
}
