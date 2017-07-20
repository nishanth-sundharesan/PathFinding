#pragma once
#include "AStar.h"

namespace Library
{
	class Dijkstra final : public AStar
	{
	public:
		Dijkstra(PathFindingHelper::HeuristicFunction heuristicFunction);
		Dijkstra(const Dijkstra&) = delete;
		Dijkstra& operator=(const Dijkstra&) = delete;
		Dijkstra(const Dijkstra&&) = delete;
		Dijkstra& operator=(Dijkstra&&) = delete;
		~Dijkstra() = default;			
	};	
}