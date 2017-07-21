#include "pch.h"
#include "PathFindingHelper.h"

using namespace std;

namespace Library
{
	float PathFindingHelper::ZeroHeuristic(const shared_ptr<Node>& currentNode, const shared_ptr<Node>& endNode)
	{
		UNREFERENCED_PARAMETER(currentNode);
		UNREFERENCED_PARAMETER(endNode);
		return 0.0f;
	}

	float PathFindingHelper::ManhattanHeuristic(const shared_ptr<Node>& currentNode, const shared_ptr<Node>& endNode)
	{
		return static_cast<float>(abs(currentNode->Location().X() - endNode->Location().X()) + abs(currentNode->Location().Y() - endNode->Location().Y()));
	}

	deque<shared_ptr<Node>> PathFindingHelper::CalculatePathNodes(shared_ptr<Node>& startNode, shared_ptr<Node>& endNode)
	{
		deque<shared_ptr<Node>> pathNodes;

		while (endNode->Parent().lock() != startNode)
		{
			endNode = endNode->Parent().lock();
			pathNodes.push_front(endNode);
		}

		return pathNodes;
	}
}