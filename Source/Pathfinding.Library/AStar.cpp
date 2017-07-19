#include "pch.h"
#include "AStar.h"
#include <set>

using namespace std;

namespace Library
{
	AStar::AStar(PathFindingHelper::HeuristicFunction heuristicFunction)
		:mHeuristicFunction(heuristicFunction)
	{
	}

	deque<shared_ptr<Node>> AStar::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, uint32_t& numberOfNodesVisited)
	{
		deque<shared_ptr<Node>> frontierQueue;
		set<shared_ptr<Node>> closedSet;

		start->SetParent(start);
		start->SetHeuristic(mHeuristicFunction(start, end));
		frontierQueue.push_back(start);

		shared_ptr<Node> currentNode;

		while (!frontierQueue.empty())
		{
			currentNode = GetNodeWithLowestTotalCost(frontierQueue);
			if (currentNode == end)
			{
				return PathFindingHelper::CalculatePathNodes(start, currentNode);
			}
			closedSet.insert(currentNode);

			for (const weak_ptr<Node>& node : currentNode->Neighbors())
			{
				if (auto neighbor = node.lock())
				{
					if (closedSet.find(neighbor) == closedSet.end())
					{
						float pathCost = currentNode->PathCost() + 1;

						if (find(frontierQueue.begin(), frontierQueue.end(), neighbor) != frontierQueue.end())
						{
							if (pathCost < neighbor->PathCost())
							{
								neighbor->SetParent(currentNode);
								neighbor->SetPathCost(pathCost);
							}
						}
						else
						{
							neighbor->SetHeuristic(mHeuristicFunction(neighbor, end));
							neighbor->SetParent(currentNode);
							neighbor->SetPathCost(pathCost);
							frontierQueue.push_back(neighbor);

							++numberOfNodesVisited;
						}
					}
				}
			}			
		} 

		frontierQueue.clear();
		return frontierQueue;
	}

	shared_ptr<Node> AStar::GetNodeWithLowestTotalCost(deque<shared_ptr<Node>>& frontierQueue)
	{
		//TODO change this to priority queue data structure
		deque<shared_ptr<Node>>::iterator nodeToRemove = frontierQueue.begin();
		shared_ptr<Node> lowestTotalCostNode = *nodeToRemove;

		for (auto it = frontierQueue.begin(); it != frontierQueue.end(); ++it)
		{
			if ((*it)->TotalCost() < lowestTotalCostNode->TotalCost())
			{
				lowestTotalCostNode = *it;
				nodeToRemove = it;
			}
		}

		frontierQueue.erase(nodeToRemove);
		return lowestTotalCostNode;
	}
}