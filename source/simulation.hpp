#pragma once

#include <vector>
#include "structs.hpp"
#include "level.hpp"

struct Pedestrian
{
	Vec2 position;
	Vec2 velocity;
	float angle;

	float target_velocity;
	float target_angle;
	
	float mass;
	float radius;	
};


class Simulation
{
public:
	friend class Application;

	Simulation();

	void tick(float delta_time);

private:
	std::vector<Pedestrian> m_crowd;
	Level m_level;
};