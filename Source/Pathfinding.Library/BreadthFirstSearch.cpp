#include "pch.h"
#include "BreadthFirstSearch.h"
#include "PathFindingHelper.h"

using namespace std;

namespace Library
{
	deque<shared_ptr<Node>> BreadthFirstSearch::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, uint32_t& numberOfNodesVisited)
	{
		deque<shared_ptr<Node>> frontierQueue;		
		frontierQueue.push_back(start);
				
		while (!frontierQueue.empty())
		{
			shared_ptr<Node> currentNode = frontierQueue.front();
			frontierQueue.pop_front();

			if (currentNode == end)
			{
				return PathFindingHelper::CalculatePathNodes(start, currentNode);
			}
			
			for (const weak_ptr<Node>& node : currentNode->Neighbors())
			{
				shared_ptr<Node> neighbor;
				if ((neighbor = node.lock()) && neighbor->Parent().expired())
				{					
					neighbor->SetParent(currentNode);					
					frontierQueue.push_back(neighbor);

					++numberOfNodesVisited;
				}
			}
		}

		frontierQueue.clear();
		return frontierQueue;
	}
}