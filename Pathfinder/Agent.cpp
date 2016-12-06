#include "Agent.h"
#include <iostream>

Agent::Agent(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr)
{
	map = mapPtr;
	positionIndex = startingIndex;

	//Load Sprite
	sf::Texture* tex = new sf::Texture();
	if(!tex->loadFromFile(filename))
	{
		std::cerr << "Error loading texture " << filename << std::endl;
	}
	tex->setSmooth(true);
	sprite.setTexture(*tex);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(map->GetPositionByIndex(positionIndex));

	float scalex = map->GetHexSize() / sprite.getGlobalBounds().width ;
	float scaley = map->GetHexSize() / sprite.getGlobalBounds().height;
	float uniformscale = (scalex < scaley ? scalex : scaley) * 0.9f;

	sprite.scale(uniformscale, uniformscale);
}

Agent::~Agent()
{

}

void Agent::Move()
{
	HexData* nextHex = GetNextField();

	positionIndex = nextHex->index;
	position = nextHex->hex->getPosition();
	sprite.setPosition(position);
}

void Agent::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Agent::DebugRender(sf::RenderWindow* window)
{

}

HexData* Agent::GetNextField()
{
	pathToFollow.clear();

	if (wayPoints.size() > 0)
	{
		HexData* target = wayPoints[targetindex%wayPoints.size()];

		pathToFollow = Map::AStarPath((*map->GetMapPtr())[positionIndex.x][positionIndex.y], target, *map->GetMapPtr());

		if (pathToFollow.size() > 1)
		{
			HexData* nextField = pathToFollow[1];

			if (nextField->index == target->index)
			{
				targetindex++;
			}

			return nextField;
		}
	} 

	return map->GetHexDatByIndex(positionIndex.x, positionIndex.y);
}

void Agent::SetWayPoints(std::vector<HexData*> otherWayPoints)
{
	wayPoints = otherWayPoints;
}
