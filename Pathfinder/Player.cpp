#include "Player.h"

Player::Player(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr): Agent(filename, startingIndex, mapPtr)
{
}

Player::~Player()
{
}

void Player::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Player::DebugRender(sf::RenderWindow* window)
{
	Hexagon drawHex;

	for(auto h : pathToFollow)
	{
		drawHex = *h->hex;
		drawHex.setOutlineColor(sf::Color::Cyan);
		drawHex.setFillColor(sf::Color::Transparent);
		window->draw(drawHex);
	}
}

void Player::HandleKeyboard(sf::Keyboard::Key key)
{
}

void Player::HandleMouse(sf::Mouse::Button mb)
{
	if(mb == sf::Mouse::Left)
	{
		target = map->GetSelectedHex();
	}
}

void Player::HandleMouse(sf::Vector2f& mousePosition)
{
}

HexData* Player::GetNextField()
{
	pathToFollow.clear();

	if (target != nullptr)
	{

		pathToFollow = map->AStarPath(map->GetHexDatByIndex(positionIndex.x, positionIndex.y), target, *map->GetMapPtr());

		if(pathToFollow.size() > 1)
		{
			pathToFollow.erase(pathToFollow.begin());
			HexData* nextField = pathToFollow[0];

			if(nextField->index == target->index)
			{
				target = nullptr;
			}

			return nextField;
		}

	}

	return map->GetHexDatByIndex(positionIndex.x, positionIndex.y);
}
