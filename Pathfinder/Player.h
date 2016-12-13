#pragma once
#include "Agent.h"

class Player : public Agent, public Interactive
{
public:
	Player(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Player();

	void Render(sf::RenderWindow* window) override;
	void DebugRender(sf::RenderWindow* window) override;

	void HandleKeyboard(sf::Keyboard::Key key) override;
	void HandleMouse(sf::Mouse::Button mb) override;
	void HandleMouse(sf::Vector2f& mousePosition) override;

	HexData* GetNextField() override;

	HexData* target = nullptr;
	std::vector<Agent*> threats;
};
