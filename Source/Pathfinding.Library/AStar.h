#pragma once
#include "IPathFinder.h"

namespace Library
{
	class AStar final : public IPathFinder
	{
	public:
		AStar() = default;
		~AStar() = default;

		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;
	private:
		std::shared_ptr<Node> GetNodeWithLowestTotalCost(std::deque<std::shared_ptr<Node>>& frontierQueue);

		static const float sPathCost;
	};
}