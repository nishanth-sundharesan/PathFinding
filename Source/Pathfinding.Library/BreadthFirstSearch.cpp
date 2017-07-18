#include "pch.h"
#include "BreadthFirstSearch.h"

using namespace std;

namespace Library
{
	deque<shared_ptr<Node>> BreadthFirstSearch::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		UNREFERENCED_PARAMETER(closedSet);

		deque<shared_ptr<Node>> frontierQueue;
		start->SetParent(start);
		frontierQueue.push_back(start);

		shared_ptr<Node> endNode(nullptr);

		//Change it to do while
		while (!frontierQueue.empty())
		{
			shared_ptr<Node> currentNode = frontierQueue.front();
			const std::vector<std::weak_ptr<Node>>& neighbours = currentNode->Neighbors();
			frontierQueue.pop_front();

			for (const std::weak_ptr<Node>& node : neighbours)
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
}