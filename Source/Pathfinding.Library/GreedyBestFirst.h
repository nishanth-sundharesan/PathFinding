#pragma once
#include "IPathFinder.h"
#include "PathFindingHelper.h"

namespace Library
{
	class GreedyBestFirst final : public IPathFinder
	{
	public:
		GreedyBestFirst(PathFindingHelper::HeuristicFunction heuristicFunction);
		GreedyBestFirst(const GreedyBestFirst&) = delete;
		GreedyBestFirst& operator=(const GreedyBestFirst&) = delete;
		GreedyBestFirst(const GreedyBestFirst&&) = delete;
		GreedyBestFirst& operator=(GreedyBestFirst&&) = delete;
		~GreedyBestFirst() = default;

		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::uint32_t& numberOfNodesVisited) override;

	private:
		PathFindingHelper::HeuristicFunction mHeuristicFunction;
	};
}