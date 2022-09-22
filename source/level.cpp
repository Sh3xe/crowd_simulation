#include "level.hpp"
#include <fstream>
#include <cassert>

std::optional<Level> load_level_from_file( const std::string &path )
{
	assert(false); // pas testé
	std::fstream file { path, std::ios::in };
	if (!file) return {};

	Level level;

	int vertex_count {0};
	file >> vertex_count;
	assert(vertex_count >= 0 && vertex_count < 100);
	level.simulation_zone.reserve(vertex_count);

	// récupération de la zone de delimitation
	Vec2 vec {0.0f, 0.0f};
	for( int i = 0; i < vertex_count; ++i )
	{
		file >> vec.x >> vec.y;
		level.simulation_zone.push_back( vec );
	}

	// récupération des obstacles
	int obstacles_count {0};
	int vertex_count {0};
	Vec2 pos;
	file >> obstacles_count;
	assert(obstacles_count <= 1000 && obstacles_count >= 0 );

	// pour chaques obstacles
	for(int i = 0; i < obstacles_count; ++i)
	{
		// on créer un polygone
		Polygon p;
		file >> vertex_count;
		assert(vertex_count >= 0 && vertex_count <= 1000);
		p.reserve(vertex_count);
		
		// on remplitses sommets
		for(int j = 0; j < vertex_count; ++j)
		{
			file >> pos.x >> pos.y;
			p.push_back(pos);
		}

		// on l'ajoute à la liste
		level.obstacles.push_back(p);
	}

	// récupération des arrêtes du graphe
	vertex_count = 0;
	file >> vertex_count;
	assert(vertex_count >= 0 && vertex_count <= 100);

	level.graph_neighbours.reserve(vertex_count);
	level.graph_positions.reserve(vertex_count);
	for(int i = 0; i < vertex_count; ++i)
	{
		float x, y;
		int next;
		file >> x >> y >> next;
		level.graph_neighbours.push_back(next);
		level.graph_positions.push_back(Vec2{x, y});
	}

	// récupération des zones d'apparition
	int spawn_zone_count = 0;
	SpawningZone zone;
	file >> spawn_zone_count;
	assert(spawn_zone_count >= 0 && spawn_zone_count <= 10 );
	level.spawning_zones.reserve(spawn_zone_count);

	for(int i = 0; i < spawn_zone_count; ++i)
	{
		file >> zone.position.x >> zone.position.y >> zone.size.x >> zone.size.y >> zone.graph_start >> zone.spawning_coeff;
		level.spawning_zones.push_back(zone);
	}

	if( file.fail() ) return {}; 

	return {};
}
