#include "pch.h"
#include "AStar.h"

using namespace std;

namespace Library
{
	const float AStar::sPathCost = 0.0f;

	deque<shared_ptr<Node>> AStar::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		UNREFERENCED_PARAMETER(closedSet);

		deque<shared_ptr<Node>> frontierQueue;
		start->SetParent(start);
		start->SetHeuristic(CalculateHeuristic(start, end));
		frontierQueue.push_back(start);

		shared_ptr<Node> endNode(nullptr);

		//Change it to do while
		while (!frontierQueue.empty())
		{
			shared_ptr<Node> currentNode = GetNodeWithLowestTotalCost(frontierQueue);
			const vector<weak_ptr<Node>>& neighbours = currentNode->Neighbors();

			for (const weak_ptr<Node>& node : neighbours)
			{
				if (auto nodeSharedPtr = node.lock())
				{
					if (!nodeSharedPtr->IsInClosedSet())
					{
						if (nodeSharedPtr == end)
						{
							nodeSharedPtr->SetParent(currentNode);
							endNode = nodeSharedPtr;
							frontierQueue.clear();
							break;
						}

						//If path cost existed, then it would be calculated here.
						//Calculate path cost for the neighbor
						float pathCost = currentNode->PathCost() + 1;
						if (find(frontierQueue.begin(), frontierQueue.end(), nodeSharedPtr) != frontierQueue.end())
						{
							if (pathCost < nodeSharedPtr->PathCost())
							{
								nodeSharedPtr->SetParent(currentNode);
								nodeSharedPtr->SetPathCost(pathCost);
							}
						}
						else
						{
							nodeSharedPtr->SetHeuristic(CalculateHeuristic(nodeSharedPtr, end));
							nodeSharedPtr->SetParent(currentNode);
							nodeSharedPtr->SetPathCost(pathCost);
							frontierQueue.push_back(nodeSharedPtr);

							currentNode->SetIsInClosetSet(true);
						}
					}
				}
			}
		}
		if (endNode)
		{
			while (endNode->Parent().lock() != start)
			{
				endNode = endNode->Parent().lock();
				frontierQueue.push_front(endNode);
			}
		}
		else
		{
			frontierQueue.clear();
		}

		return frontierQueue;		
	}

	shared_ptr<Node> AStar::GetNodeWithLowestTotalCost(deque<shared_ptr<Node>>& frontierQueue)
	{
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