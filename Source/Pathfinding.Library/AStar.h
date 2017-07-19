#pragma once
#include "IPathFinder.h"
#include "PathFindingHelper.h"

namespace Library
{
	class AStar : public IPathFinder
	{
	public:
		AStar(PathFindingHelper::HeuristicFunction heuristicFunction);
		AStar(const AStar&) = delete;
		AStar& operator=(const AStar&) = delete;
		AStar(const AStar&&) = delete;
		AStar& operator=(AStar&&) = delete;
		virtual ~AStar() = default;
		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::uint32_t& numberOfNodesVisited) override;

	protected:
		PathFindingHelper::HeuristicFunction mHeuristicFunction;

	private:
		std::shared_ptr<Node> GetNodeWithLowestTotalCost(std::deque<std::shared_ptr<Node>>& frontierQueue);		
	};
}