#pragma once

#include "Graph.h"
#include <string>
#include <cstdint>

namespace Library
{
	class GridHelper final
	{
	public:
		static Graph LoadGridFromFile(const std::string& filename);
		static Graph LoadGridFromFile(const std::string& filename, int32_t& graphWidth, int32_t& graphHeight);	
		static bool IsValidGridLocation(const Point& location, std::int32_t maxWidth, std::int32_t maxLength);
		static bool IsValidGridLocation(std::int32_t xPosition, std::int32_t yPosition, std::int32_t maxWidth, std::int32_t maxLength);
	};
}