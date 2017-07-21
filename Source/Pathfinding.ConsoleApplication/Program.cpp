#include "pch.h"
#include <unordered_map>
#include "GridHelper.h"
#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "GreedyBestFirst.h"
#include "AStar.h"
#include "Dijkstra.h"
#include "PathFindingHelper.h"

Library::Point GetValidPointOnGrid(const Library::Graph& graph, std::int32_t gridWidth, std::int32_t gridHeight, const std::string& messageForConsole)
{
	std::cout << "\n" << messageForConsole;
	std::cout << "\nX value should be between 0 & " << gridWidth - 1 << ", Y value should be between 0 & " << gridHeight - 1;
	std::cout << "\nThe X & Y values should not correspond to the blocking path. Valid example: 1 1\n ";

	while (true)
	{
		std::int32_t nodeXPosition;
		std::int32_t nodeYPosition;

		std::cin >> nodeXPosition;
		std::cin >> nodeYPosition;

		if (Library::GridHelper::IsValidGridLocation(nodeXPosition, nodeYPosition, gridWidth, gridHeight) &&
			graph.At(nodeXPosition, nodeYPosition)->Type() != Library::NodeType::Wall)
		{
			return Library::Point(nodeXPosition, nodeYPosition);
		}
		std::cout << "\n" << messageForConsole;
	}
}

void DisplayTracedPath(const std::deque<std::shared_ptr<Library::Node>>& pathNodes, const Library::Graph& graph, std::int32_t gridWidth, std::int32_t gridHeight, const std::string& algorithmName,
	const Library::Point& startPoint, const Library::Point& endPoint)
{
	std::cout << "\n----------------------------------------";
	std::cout << "\n\t" << algorithmName;
	std::cout << "\n----------------------------------------\n";

	std::cout << "\nSTART node: " << startPoint.X() << "," << startPoint.Y();
	std::cout << "\nEND node: " << endPoint.X() << "," << endPoint.Y() << "\n\n";

	for (std::int32_t i = 0; i < gridHeight; ++i)
	{
		for (std::int32_t j = 0; j < gridWidth; ++j)
		{
			std::cout << " ";
			if (std::find(pathNodes.begin(), pathNodes.end(), graph.At(j, i)) != pathNodes.end())
			{
				std::cout << "X";
			}
			else if(j == startPoint.X() && i == startPoint.Y())
			{
				std::cout << "S";
			}
			else if(j == endPoint.X() && i == endPoint.Y())
			{
				std::cout << "E";
			}
			else
			{
				std::cout << static_cast<std::int32_t>(graph.At(j, i)->Type());
			}
		}
		std::cout << "\n";
	}	
}

void DisplayElapedTime(float time)
{
	std::cout << "\nTime taken to calculate path (microseconds): " << time;
}

void DisplayNumberOfNodesVisited(std::uint32_t numberOfVisitedNodes)
{
	std::cout << "\nNumber of visited nodes: " << numberOfVisitedNodes << "\n";
}

int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

#pragma region Load Grid
	std::int32_t gridWidth;
	std::int32_t gridHeight;
	Library::Graph graph = Library::GridHelper::LoadGridFromFile("Grid.grid", gridWidth, gridHeight);
#pragma endregion

#pragma region Display Loaded Grid and Legends
	std::cout << "Map Representation (2D Grid): \n \n";
	for (std::int32_t i = 0; i < gridWidth; ++i)
	{
		for (std::int32_t j = 0; j < gridHeight; ++j)
		{
			std::cout << " ";
			std::cout << static_cast<std::int32_t>(graph.At(j, i)->Type());
		}
		std::cout << "\n";
	}

	std::cout << "\nLegend:";
	std::cout << "\n0 - Path";
	std::cout << "\n1 - Blocking Path";
	std::cout << "\nX - Shortest path from START to END";
	std::cout << "\nS - Start node";
	std::cout << "\nE - End node\n";
#pragma endregion

#pragma region Read Input
	Library::Point startPoint = GetValidPointOnGrid(graph, gridWidth, gridHeight, "Please enter valid X & Y values for START node:");
	Library::Point endPoint = GetValidPointOnGrid(graph, gridWidth, gridHeight, "Please enter valid X & Y values for END node:");
#pragma endregion

#pragma region Declare Pathfinding Algorithms
	std::unordered_map<std::string, std::shared_ptr<Library::IPathFinder>> pathFindingAlgorithms =
	{
		{ "Breadth-First Search Algorithm", std::make_shared<Library::BreadthFirstSearch>() },
		{ "Greedy Best-First Search Algorithm ", std::make_shared<Library::GreedyBestFirst>(Library::PathFindingHelper::ManhattanHeuristic) },
		{ "AStar Algorithm", std::make_shared<Library::AStar>(Library::PathFindingHelper::ManhattanHeuristic) },
		{ "Dijkstra's Algorithm", std::make_shared<Library::Dijkstra>(Library::PathFindingHelper::ZeroHeuristic) }
	};
#pragma endregion

#pragma region Find Path Using Pathfinding Algorithms
	Library::StopWatch stopWatch;
	for (auto& algorithm : pathFindingAlgorithms)
	{
		std::uint32_t numberOfNodesVisited = 0;
		stopWatch.Restart();
		std::deque<std::shared_ptr<Library::Node>> pathNodes = algorithm.second->FindPath(graph.At(startPoint), graph.At(endPoint), numberOfNodesVisited);
		stopWatch.Stop();

		DisplayTracedPath(pathNodes, graph, gridWidth, gridHeight, algorithm.first, startPoint, endPoint);
		DisplayElapedTime(static_cast<float>(stopWatch.Elapsed().count()));
		DisplayNumberOfNodesVisited(numberOfNodesVisited);
		graph.Reset();
	}
#pragma endregion

	return 0;
}