#pragma once

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
	bool m_running {false};

};