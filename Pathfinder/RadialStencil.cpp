#include "RadialStencil.h"

RadialStencil::RadialStencil()
{
	//First Ring
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1, -1, 0), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, -1, 1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1, 0, 1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1, 1, 0), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, 1, -1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1, 0, -1), 5));


	//Second Ring


	//Third Ring
}
