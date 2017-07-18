#include "pch.h"
#include "GreedyBestFirst.h"

using namespace std;

namespace Library
{
	deque<shared_ptr<Node>> GreedyBestFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
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
			shared_ptr<Node> currentNode = GetNodeWithLowHeuristic(frontierQueue);
			const vector<weak_ptr<Node>>& neighbours = currentNode->Neighbors();

			for (const weak_ptr<Node>& node : neighbours)
			{
				if (auto nodeSharedPtr = node.lock())
				{
					if (nodeSharedPtr->Parent().expired())
					{
						nodeSharedPtr->SetParent(currentNode);
						if (nodeSharedPtr == end)
						{
							endNode = nodeSharedPtr;
							frontierQueue.clear();
							break;
						}
						nodeSharedPtr->SetHeuristic(CalculateHeuristic(nodeSharedPtr, end));
						frontierQueue.push_back(nodeSharedPtr);
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

	/*float GreedyBestFirst::CalculateHeuristic(shared_ptr<Node> currentNode, shared_ptr<Node> endNode)
	{
		return static_cast<float>(abs(currentNode->Location().X() - endNode->Location().X()) + abs(currentNode->Location().Y() - endNode->Location().Y()));
	}*/

	shared_ptr<Node> GreedyBestFirst::GetNodeWithLowHeuristic(deque<shared_ptr<Node>>& frontierQueue)
	{
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
