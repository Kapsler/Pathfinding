#include "ThreatStencil.h"

void ThreatStencil::SetThreats(sf::Vector2i origin, std::vector<std::vector<HexData*>>& usedMap)
{
	sf::Vector2i offsets;

	if(!stencil.empty())
	{
		for(auto p : stencil)
		{
			offsets = CubeToOffset(p.first);
			if(origin.x + offsets.x >= 0 && origin.x + offsets.x < usedMap.size() && origin.y + offsets.y >= 0 && origin.y + offsets.y < usedMap[0].size())
			{
				usedMap[origin.x + offsets.x][origin.y + offsets.y]->threat += p.second;
			}
		}
	}
	
}

sf::Vector2i ThreatStencil::CubeToOffset(CubeCoords& cube)
{
	sf::Vector2i ret;
	ret.x = cube.z + (cube.x + (cube.x & 1)) / 2;
	ret.y = cube.x;
	return ret;
}
