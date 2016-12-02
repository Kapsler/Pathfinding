#pragma once
#include <vector>
#include "Hexagon.h"
#include "Renderable.h"
#include "Interactive.h"

class Map : public Renderable, public Interactive
{
public:
	//Map(float mapWidth, float mapHeight, float hexSize);
	explicit Map(float screenWidth, float screenHeight, const std::string& filename);
	virtual ~Map();

	virtual void Render(sf::RenderWindow* window) override;
	virtual void DebugRender(sf::RenderWindow* window) override;
	virtual void HandleKeyboard(sf::Keyboard::Key key) override;
	virtual void HandleMouse(sf::Mouse::Button mb, sf::Vector2f& mousePosition) override;

private:
	//void GenerateFromNumbers(float width, float height, float hexSize);
	void GenerateFromImage(float screenWidth, float screenHeight, const sf::Image& mapImage);
	static float distanceBetweenFloatPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);
	void SetCurrentHex(const sf::Vector2f& mousePos);
	void LoadMapFromImage(float screenWidth, float screenHeight, const std::string& filename);
	

	std::vector<std::vector<int>> terrain;
	std::vector<std::vector<Hexagon*>> shapes;
	Hexagon* selectedHex = nullptr;
	
	int rows, columns;

	sf::Color water = sf::Color(60, 180, 255);
	sf::Color sand = sf::Color(200, 180, 70);
	sf::Color mud = sf::Color(160, 100, 60);
	sf::Color grass = sf::Color(50, 150, 60);
	sf::Color street = sf::Color(130, 130, 130);
	sf::Color notfoundColor = sf::Color::Magenta;

	int waterDifficulty = 1000;
	int sandDifficulty = 5;
	int mudDifficulty = 3;
	int grassDifficulty = 2;
	int streetDifficulty = 1;
	int notfoundDifficulty = 1000;

};
