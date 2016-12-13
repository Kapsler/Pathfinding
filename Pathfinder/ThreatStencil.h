#pragma once
#include <vector>
#include "CubeCoords.h"
#include "HexData.h"

class ThreatStencil
{
public:

	static sf::Vector2i CubeToOffset(CubeCoords&);
	void SetThreats(sf::Vector2i origin, std::vector<std::vector<HexData*>>& usedMap);


protected:
	std::vector<std::pair<CubeCoords, int>> stencil;

};
