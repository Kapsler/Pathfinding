#include "RadialStencil.h"

RadialStencil::RadialStencil()
{
	//First Ring
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1, 0, -1), 8));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1, -1, 0), 8));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, -1, 1), 8));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1, 0, 1), 8));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1, 1, 0), 8));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, 1, -1), 8));


	//Second Ring
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(2, 0, -2), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(2, -1, -1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(2, -2, 0), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1, -2, 1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, -2, 2), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1, -1, 2), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-2, 0, 2), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-2, 1, 1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-2, 2, 0), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1, 2, -1), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, 2, -2), 5));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1, 1, -2), 5));

	//Third Ring
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(3,0,-3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(3,-1,-2), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(3,-2,-1), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(3,-3,0), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(2,-3,1), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1,-3,2), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0,-3,3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1,-2,3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-2,-1,3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-3,0,3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-3,1,2), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-3,2,1), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-3,3,0), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-2,3,-1), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(-1,3,-2), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0,3,-3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(1,2,-3), 2));
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(2,1,-3), 2));

}
