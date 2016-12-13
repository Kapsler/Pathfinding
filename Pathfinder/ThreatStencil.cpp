#include "ThreatStencil.h"

void ThreatStencil::SetThreats(sf::Vector2i origin, std::vector<std::vector<HexData*>>& usedMap)
{
	sf::Vector2i offsetIndex;
	CubeCoords originCube = OffsetToCube(origin); 
	CubeCoords targetCube;

	if(!stencil.empty())
	{
		for(auto p : stencil)
		{
			targetCube = originCube + p.first;
			offsetIndex = CubeToOffset(targetCube);
			if(offsetIndex.x >= 0 && offsetIndex.x < usedMap.size() && offsetIndex.y >= 0 && offsetIndex.y < usedMap[0].size())
			{
				usedMap[offsetIndex.x][offsetIndex.y]->threat += p.second;
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

CubeCoords ThreatStencil::OffsetToCube(sf::Vector2i& off)
{
	CubeCoords ret;

	ret.x = off.y;
	ret.z = off.x - (off.y + (off.y & 1)) / 2;
	ret.y = -ret.x - ret.z;

	return ret;
}
