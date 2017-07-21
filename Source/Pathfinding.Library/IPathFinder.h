#pragma once

#include "Node.h"
#include <deque>

namespace Library
{	
	class IPathFinder
	{
	public:
		virtual ~IPathFinder() { };
		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::uint32_t& numberOfNodesVisited) = 0;			
	};
}