#pragma once
#include <vector>
#include "HexData.h"
#include "Hexagon.h"
#include "Renderable.h"
#include "Interactive.h"

class Map : public Renderable, public Interactive
{
public:
	explicit Map(float screenWidth, float screenHeight, const std::string& filename);
	virtual ~Map();

	void Render(sf::RenderWindow* window) override;
	void DebugRender(sf::RenderWindow* window) override;
	void HandleKeyboard(sf::Keyboard::Key key) override;
	void HandleMouse(sf::Mouse::Button mb, sf::Vector2f& mousePosition) override;

	float GetHexSize() const;
	sf::Vector2f GetPositionByIndex(int x, int y);
	sf::Vector2f GetPositionByIndex(sf::Vector2i posIndex);

private:
	void GenerateFromImage(float screenWidth, float screenHeight, const sf::Image& mapImage);
	static float distanceBetweenFloatPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);
	void SetCurrentHex(const sf::Vector2f& mousePos);
	void LoadMapFromImage(float screenWidth, float screenHeight, const std::string& filename);
	void DebugRenderText(sf::RenderWindow *window);
	std::vector<HexData*> GetNeighbors(HexData* current);

	std::vector<std::vector<HexData*>> shapes;
	HexData* selectedHexDat = nullptr;
	
	int rows, columns;
	float hexsize;

	sf::Color water = sf::Color(60, 180, 255);
	sf::Color sand = sf::Color(200, 180, 70);
	sf::Color mud = sf::Color(160, 100, 60);
	sf::Color grass = sf::Color(50, 150, 60);
	sf::Color street = sf::Color(130, 130, 130);
	sf::Color notfoundColor = sf::Color::Magenta;

	int unpassable = 100;
	int waterDifficulty = 1000;
	int sandDifficulty = 5;
	int mudDifficulty = 3;
	int grassDifficulty = 2;
	int streetDifficulty = 1;
	int notfoundDifficulty = 1000;

	sf::Text debugText;
	sf::Font debugFont;
};
