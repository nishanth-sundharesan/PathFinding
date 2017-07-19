#include "pch.h"
#include "GreedyBestFirst.h"
#include "PathFindingHelper.h"

using namespace std;

namespace Library
{
	GreedyBestFirst::GreedyBestFirst()
		:mHeuristicFunction(PathFindingHelper::ManhattanHeuristic)
	{
	}

	deque<shared_ptr<Node>> GreedyBestFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, uint32_t& numberOfNodesVisited)
	{
		deque<shared_ptr<Node>> frontierQueue;
		start->SetParent(start);
		start->SetHeuristic(mHeuristicFunction(start, end));
		frontierQueue.push_back(start);		

		while (!frontierQueue.empty())
		{
			shared_ptr<Node> currentNode = GetNodeWithLowHeuristic(frontierQueue);
			if (currentNode == end)
			{
				return PathFindingHelper::CalculatePathNodes(start, currentNode);
			}
			
			for (const weak_ptr<Node>& node : currentNode->Neighbors())
			{
				std::shared_ptr<Node> neighbor;
				if ((neighbor = node.lock()) && neighbor->Parent().expired())
				{
					neighbor->SetParent(currentNode);

					neighbor->SetHeuristic(mHeuristicFunction(neighbor, end));
					frontierQueue.push_back(neighbor);

					++numberOfNodesVisited;
				}
			}
		}

		frontierQueue.clear();
		return frontierQueue;
	}

	shared_ptr<Node> GreedyBestFirst::GetNodeWithLowHeuristic(deque<shared_ptr<Node>>& frontierQueue)
	{
		//TODO change this to priority queue data structure
		deque<shared_ptr<Node>>::iterator nodeToRemove = frontierQueue.begin();
		shared_ptr<Node> lowestHeuristicNode = *nodeToRemove;

		for (auto it = frontierQueue.begin(); it != frontierQueue.end(); ++it)
		{
			if ((*it)->Heuristic() < lowestHeuristicNode->Heuristic())
			{
				lowestHeuristicNode = *it;
				nodeToRemove = it;
			}
		}

		frontierQueue.erase(nodeToRemove);
		return lowestHeuristicNode;
	}
}
