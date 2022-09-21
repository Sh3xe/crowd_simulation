#pragma once

#include <SFML/System/Vector2.hpp>

struct Level
{

};

struct Pedestrian
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float angle;
	float target_angle;
	float mass;
	float radius;	
};

class Simulation
{
public:
	Simulation();

	void render();
	void tick(float delta_time);

private:

};