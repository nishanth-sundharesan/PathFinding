#pragma once
#include "IPathFinder.h"

namespace Library
{
	class GreedyBestFirst final : public IPathFinder
	{
	public:
		GreedyBestFirst();
		GreedyBestFirst(const GreedyBestFirst&) = delete;
		GreedyBestFirst& operator=(const GreedyBestFirst&) = delete;
		GreedyBestFirst(const GreedyBestFirst&&) = delete;
		GreedyBestFirst& operator=(GreedyBestFirst&&) = delete;
		~GreedyBestFirst() = default;

		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::uint32_t& numberOfNodesVisited) override;

	private:
		std::shared_ptr<Node> GetNodeWithLowHeuristic(std::deque<std::shared_ptr<Node>>& frontierQueue);

		std::function<float(const std::shared_ptr<Node>& currentNode, const std::shared_ptr<Node>& endNode)> mHeuristicFunction;
	};
}