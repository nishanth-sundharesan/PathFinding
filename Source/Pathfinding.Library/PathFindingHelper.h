#pragma once
#include "Node.h"
#include <functional>
#include <deque>

namespace Library
{
	class PathFindingHelper
	{
	public:
		typedef std::function<float(const std::shared_ptr<Node>& currentNode, const std::shared_ptr<Node>& endNode)> HeuristicFunction;

		static float ZeroHeuristic(const std::shared_ptr<Node>& currentNode, const std::shared_ptr<Node>& endNode);
		static float ManhattanHeuristic(const std::shared_ptr<Node>& currentNode, const std::shared_ptr<Node>& endNode);
		static std::deque<std::shared_ptr<Node>> CalculatePathNodes(std::shared_ptr<Node>& startNode, std::shared_ptr<Node>& endNode);
	};
}