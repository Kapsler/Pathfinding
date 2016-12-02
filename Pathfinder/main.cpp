#include "Hexagon.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <iostream>

const float screenWidth = 1050.0f;
const float screenHeight = 1200.0f;
sf::RenderWindow *window;

std::vector<Renderable*> toRender;
std::vector<Interactive*> toInteract;

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenWidth), static_cast<unsigned int>(screenHeight)), "Pathfinding");
	window->setVerticalSyncEnabled(true);

	Map* terrain = new Map(screenWidth, screenHeight, "./Assets/terrain.png");
	toRender.push_back(terrain);
	toInteract.push_back(terrain);

	sf::Clock clock;
	float lastTime = 0; 
	float fps = 0.0f;

	while (window->isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		fps = 1.0 / (currentTime);
		lastTime = currentTime;
		window->setTitle("Pathfinding (" + std::to_string(fps) + ")");

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

			if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mpos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

				for (const auto i : toInteract)
				{
					i->HandleMouse(event.mouseButton.button, mpos);
				}
			}

		}

		window->clear();

		for(const auto r : toRender)
		{
			r->Render(window);
		}

		window->display();
	}

	return 0;
}
