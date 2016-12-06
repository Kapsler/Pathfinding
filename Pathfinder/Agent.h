#pragma once
#include "Map.h"
#include "Renderable.h"
#include "Moving.h"

class Agent : public Renderable, public Moving
{
public:
	Agent(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Agent();

	void Move() override;
	void Render(sf::RenderWindow* window) override;
	void DebugRender(sf::RenderWindow* window) override;

	virtual HexData* GetNextField();
	void SetWayPoints(std::vector<HexData*> otherWayPoints);

protected:
	sf::Vector2i positionIndex;
	sf::Vector2f position;

	sf::Sprite sprite;

	Map* map;

	std::vector<HexData*> pathToFollow;

private:
	std::vector<HexData*> wayPoints;
	int targetindex = 0;
};
