#include "pch.h"
#include "AStar.h"

using namespace std;

namespace Library
{
	AStar::AStar(PathFindingHelper::HeuristicFunction heuristicFunction)
		:mHeuristicFunction(heuristicFunction)
	{
	}

	deque<shared_ptr<Node>> AStar::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, uint32_t& numberOfNodesVisited)
	{
		unordered_set<shared_ptr<Node>> frontierQueueLookup;
		struct NodeWithHighTotalCost
		{
			bool operator()(const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) const
			{
				return lhs->TotalCost() > rhs->TotalCost();
			}
		};
		priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, NodeWithHighTotalCost> frontierQueue;		
		set<shared_ptr<Node>> closedSet;
		
		start->SetHeuristic(mHeuristicFunction(start, end));		
		frontierQueue.push(start);
		frontierQueueLookup.insert(start);
		
		while (!frontierQueue.empty())
		{
			shared_ptr<Node> currentNode = frontierQueue.top();
			if (currentNode == end)
			{
				return PathFindingHelper::CalculatePathNodes(start, currentNode);
			}
			frontierQueue.pop();
			frontierQueueLookup.erase(currentNode);			
			closedSet.insert(currentNode);

			for (const weak_ptr<Node>& node : currentNode->Neighbors())
			{
				if (auto neighbor = node.lock())
				{
					if (closedSet.find(neighbor) == closedSet.end())
					{
						float pathCost = currentNode->PathCost() + 1;

						if (frontierQueueLookup.find(neighbor) != frontierQueueLookup.end())
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
							frontierQueue.push(neighbor);
							frontierQueueLookup.insert(neighbor);

							++numberOfNodesVisited;
						}
					}
				}
			}			
		} 
		
		return deque<shared_ptr<Node>>();
	}	
}