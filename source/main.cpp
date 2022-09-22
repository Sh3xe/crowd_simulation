#include "application.hpp"

int main(int argc, char *argv[])
{
	Config config {1280, 720};
	Application app {config};
	app.run( 1.0f / 100.0f );
	return 0;
}