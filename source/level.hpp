#pragma once

#include <vector>
#include <string>
#include <optional>
#include "structs.hpp"

struct SpawningZone
{
	Vec2 position;
	Vec2 size;
	int graph_start;
	int spawning_coeff;
};

struct Level
{
	std::vector<Vec2> simulation_zone;
	std::vector<Polygon> obstacles;
	std::vector<Vec2> graph_positions;
	std::vector<int> graph_neighbours;
	std::vector<SpawningZone> spawning_zones;
};

std::optional<Level> load_level_from_file( const std::string &path );