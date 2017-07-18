#pragma once
#include "IPathFinder.h"

namespace Library
{
	class GreedyBestFirst final : public IPathFinder
	{
	public:
		GreedyBestFirst() = default;
		~GreedyBestFirst() = default;

		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;

	private:
		/*float CalculateHeuristic(std::shared_ptr<Node> currentNode, std::shared_ptr<Node> endNode);*/

		std::shared_ptr<Node> GetNodeWithLowHeuristic(std::deque<std::shared_ptr<Node>>& frontierQueue);
	};
}