#pragma once

#include "simulation.hpp"

struct Config
{
	int width, height;
};

class Application
{
public:
	Application( const Config &config );

	void run();

private:
	void handle_inputs();
	void update();
	void draw();

	bool m_running {false};
	Simulation m_simulation;

};