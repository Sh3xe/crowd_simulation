#include "application.hpp"
#include <SFML/System.hpp>
#include "logger.hpp"

Application::Application(const Config &config):
	m_window(sf::VideoMode(config.width, config.height), "Simulation foule"),
	m_view( {0.0f, 0.0f}, {config.width, config.height} )
{
}

void Application::run( float dt )
{
	m_running = true;

	while(m_running && m_window.isOpen() )
	{
		m_window.clear();
		m_window.setView(m_view);

		handle_inputs( dt );
		update( dt );
		render( dt );

		sf::sleep( sf::seconds(dt) );
		m_window.display();
	}

	m_window.close();
}

void Application::handle_inputs(float dt)
{
	static sf::Vector2f last_mouse_pos {0, 0};

	sf::Event event;
	while( m_window.pollEvent(event) )
	{
		if( event.type == sf::Event::Closed )
			m_running = false;
		if( event.type == sf::Event::MouseMoved )
		{
			sf::Vector2f new_mouse_pos = {event.mouseMove.x, event.mouseMove.y};
			sf::Vector2f delta_pos = last_mouse_pos - new_mouse_pos;
			last_mouse_pos = new_mouse_pos;
			
			if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_view.setCenter( m_view.getCenter() + delta_pos );
			}
		}
	}
}

void Application::render( float dt )
{
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Red);
	shape.setSize({200, 300});
	m_window.draw(shape);
}

void Application::update( float dt )
{
	m_simulation.tick(dt);
}