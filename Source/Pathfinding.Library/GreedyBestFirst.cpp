#include "pch.h"
#include "GreedyBestFirst.h"

using namespace std;

namespace Library
{
	GreedyBestFirst::GreedyBestFirst(PathFindingHelper::HeuristicFunction heuristicFunction)
		:mHeuristicFunction(heuristicFunction)
	{
	}

	deque<shared_ptr<Node>> GreedyBestFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, uint32_t& numberOfNodesVisited)
	{
		struct NodeWithHighHeuristic
		{
			bool operator()(const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) const
			{
				return lhs->Heuristic() > rhs->Heuristic();
			}
		};
		priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, NodeWithHighHeuristic> frontierQueue;
				
		start->SetHeuristic(mHeuristicFunction(start, end));
		frontierQueue.push(start);		
				
		while (!frontierQueue.empty())
		{
			shared_ptr<Node> currentNode = frontierQueue.top();
			if (currentNode == end)
			{
				return PathFindingHelper::CalculatePathNodes(start, currentNode);
			}
			frontierQueue.pop();

			for (const weak_ptr<Node>& node : currentNode->Neighbors())
			{
				shared_ptr<Node> neighbor;
				if ((neighbor = node.lock()) && neighbor->Parent().expired())
				{
					neighbor->SetParent(currentNode);
					neighbor->SetHeuristic(mHeuristicFunction(neighbor, end));
					frontierQueue.push(neighbor);

					++numberOfNodesVisited;
				}
			}
		}
		
		return deque<shared_ptr<Node>>();
	}
}
