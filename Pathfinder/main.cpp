#include "Hexagon.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <iostream>
#include "Moving.h"
#include "Agent.h"
#include "Player.h"
#include "RadialStencil.h"

const float screenWidth = 1050.0f;
const float screenHeight = 1200.0f;
sf::RenderWindow *window;
	
std::vector<Renderable*> toRender;
std::vector<Interactive*> toInteract;
std::vector<Moving*> toMove;

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenWidth), static_cast<unsigned int>(screenHeight)), "Pathfinding");
	window->setVerticalSyncEnabled(true);

	Map* map = new Map(screenWidth, screenHeight, "./Assets/terrain30.png");
	toRender.push_back(map);
	toInteract.push_back(map);

	Agent* enemy = new Agent("./Assets/bear.png", sf::Vector2i(9, 12), map);
	enemy->SetThreatStencil(new RadialStencil());
	toRender.push_back(enemy);
	toMove.push_back(enemy);
	map->AddThreat(enemy);
	{
		std::vector<HexData*> path;
		path.push_back(map->GetHexDatByIndex(19, 12));
		path.push_back(map->GetHexDatByIndex(9, 12));
		enemy->SetWayPoints(path);
	}

	enemy = new Agent("./Assets/bear.png", sf::Vector2i(7, 27), map);
	enemy->SetThreatStencil(new RadialStencil());
	toRender.push_back(enemy);
	toMove.push_back(enemy);
	map->AddThreat(enemy);
	{
		std::vector<HexData*> path;
		path.push_back(map->GetHexDatByIndex(22, 20));
		path.push_back(map->GetHexDatByIndex(7, 27));
		enemy->SetWayPoints(path);
	}

	Player* player = new Player("./Assets/panda.png", sf::Vector2i(0, 0), map);
	player->SetThreatStencil(new ThreatStencil());
	toRender.push_back(player);
	toMove.push_back(player);
	toInteract.push_back(player);
	map->AddThreat(player);

	sf::Clock fpsClock, moveClock;
	float totalMoveTime = 0;

	while (window->isOpen())
	{
		float currentFpsTime = fpsClock.restart().asSeconds();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}

				for (const auto i : toInteract)
				{
					i->HandleKeyboard(event.key.code);
				}
			}

			if(event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mpos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

				for (const auto i : toInteract)
				{
					i->HandleMouse(mpos);
				}
			}
			
			if(event.type == sf::Event::MouseButtonPressed)
			{
				for (const auto i : toInteract)
				{
					i->HandleMouse(event.mouseButton.button);
				}
			}

		}

		totalMoveTime += moveClock.restart().asSeconds();

		if(totalMoveTime > 10.0f)
		{
			float fps = 1.0f / (currentFpsTime);
			window->setTitle("Pathfinding (" + std::to_string(static_cast<int>(fps)) + ")");

			for(auto m : toMove)
			{
				m->Move();
			}
			totalMoveTime = 0.0f;
		}

		window->clear();

		for(const auto r : toRender)
		{
			r->Render(window);
			r->DebugRender(window);
		}

		window->display();
	}

	return 0;
}
