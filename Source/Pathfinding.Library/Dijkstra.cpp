#include "pch.h"
#include "Dijkstra.h"
#include "PathFindingHelper.h"

using namespace std;

namespace Library
{
	Dijkstra::Dijkstra(PathFindingHelper::HeuristicFunction heuristicFunction)
		:AStar(heuristicFunction)
	{
	}
}