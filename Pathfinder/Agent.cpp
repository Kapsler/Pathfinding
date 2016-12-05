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

}

void Agent::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Agent::DebugRender(sf::RenderWindow* window)
{

}

void Agent::HandleKeyboard(sf::Keyboard::Key key)
{

}

void Agent::HandleMouse(sf::Mouse::Button mb)
{
}

void Agent::HandleMouse(sf::Vector2f& mousePosition)
{
}