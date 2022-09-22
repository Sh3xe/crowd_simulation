#pragma once

#include <utility>
#include <optional>
#include "structs.hpp"

float frand( float a, float b );
int irand( int a, int b );

double distance_rapide( Vec2 p1, Vec2 p2 );
double distance2( Vec2 p1, Vec2 p2 );
double distance( Vec2 v1, Vec2 v2 );
std::optional<double> distance( Vec2 pos, Vec2 dir, Circle s );
std::optional<double> distance( Vec2 pos, Vec2 dir, Segment seg );

std::optional<Vec2> intersection( Segment s1, Segment s2 );
std::optional<Vec2> intersection( Line d1, Line d2 );

std::optional<Vec2> resolve_equation_sys( Vec2 c1, Vec2 c2, Vec2 rep );
std::optional<Vec2> custruct_normal( Vec2 v );
std::optional<Vec2> resoudre_deg_2( double a, double b, double c );

bool collision( Circle s0, Circle s1 );
bool collision( Vec2 pt, Polygon pol );
Vec2 closest( Vec2 pt, Polygon pol);

double Q_rsqrt( double number );
double length( Vec2 &vec );
void normalize( Vec2 &vec );
void fast_normalize( Vec2 &vec );

// renvoie l'angle entre p1 et p2 du point de vue de pos
double angle( Vec2 pos, Vec2 p1, Vec2 p2 );
double angle( Vec2 pos );