#pragma once

#include <SFML/Graphics.hpp>
#include "simulation.hpp"

struct Config
{
	int width, height;
};

class Application
{
public:
	Application( const Config &config );

	// lance une simulation avec un pas de
	// dt en seconde
	void run( float dt );

private:
	void handle_inputs( float dt );
	void update( float dt );
	void render( float dt );

	bool m_running {false};
	Simulation m_simulation;

	sf::RenderWindow m_window;
	sf::View m_view;
};