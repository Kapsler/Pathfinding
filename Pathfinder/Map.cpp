#include "Map.h"
#include <allocators>
#include <valarray>
#include <iostream>

//Map::Map(float mapWidth, float mapHeight, float hexSize)
//{
//	selectedHex = nullptr;
//	GenerateFromNumbers(mapWidth, mapHeight, hexSize);
//}

Map::Map(float screenWidth, float screenHeight, const std::string& filename)
{
	LoadMapFromImage(screenWidth, screenHeight, filename);
}

Map::~Map()
{
	for(auto line : shapes)
	{
		for (auto hex : line)
		{
			delete hex;
		}
	}
}

void Map::Render(sf::RenderWindow* window)
{
	for(const auto line : shapes)
	{
		for(const auto hex : line)
		{
			window->draw(*hex);
		}
	}

	if (selectedHex != nullptr)
	{
		Hexagon drawSelected = *selectedHex;
		drawSelected.setOutlineColor(sf::Color::Red);
		window->draw(drawSelected);
	}
	
	
}

void Map::DebugRender(sf::RenderWindow* window)
{

}

void Map::HandleKeyboard(sf::Keyboard::Key key)
{

}

void Map::HandleMouse(sf::Mouse::Button mb, sf::Vector2f& mousePosition)
{
	sf::Vector2f mousePos = sf::Vector2f(mousePosition);

	SetCurrentHex(mousePos);

}

float Map::distanceBetweenFloatPoints(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void Map::SetCurrentHex(const sf::Vector2f& mousePos)
{
	float closestDist = std::numeric_limits<float>::max();
	float dist;

	for (const auto line : shapes)
	{
		for (const auto hex : line)
		{
			dist = distanceBetweenFloatPoints(mousePos, hex->getPosition());
			if (dist < closestDist)
			{
				closestDist = dist;
				selectedHex = hex;
			}
		}
	}
}

void Map::LoadMapFromImage(float screenWidth, float screenHeight, const std::string& filename)
{
	sf::Image mapImage;
	mapImage.loadFromFile(filename);

	GenerateFromImage(screenWidth, screenHeight, mapImage);

}

//void Map::GenerateFromNumbers(float width, float height, float hexSize)
//{
//	Hexagon sizes(hexSize);
//	float outlineThickness = 4.0f;
//
//	columns = static_cast<int>(width / ((sizes.width() + outlineThickness) * (3.0f / 4.0f)));
//	rows = static_cast<int>(height / (sizes.height() + outlineThickness)) - 1;
//
//	float initialOffsetX = (sizes.width() + outlineThickness) * (3.0f/4.0f) ;
//	float initialOffsetY = (sizes.height() + outlineThickness) * 1.3f;
//	float offsetX = initialOffsetX;
//	float offsetY = initialOffsetY;
//	
//	for(int i = 0; i < rows; ++i)
//	{
//		std::vector<Hexagon*> line;
//		for(int j = 0; j < columns; ++j)
//		{
//			Hexagon* tmp = new Hexagon(hexSize);
//			tmp->setOutlineColor(sf::Color::Blue);
//			tmp->setOutlineThickness(outlineThickness);
//			tmp->setPosition(offsetX, offsetY);
//			tmp->setFillColor(sf::Color::Green);
//
//			line.push_back(tmp);
//
//			offsetX += sizes.width() * 3.0f/4.0f + outlineThickness/2.0f; 
//			
//			if (j % 2 == 0)
//			{
//				offsetY -= sizes.height() / 2.0f + outlineThickness / 2.0f;
//			}
//			else
//			{
//				offsetY += sizes.height() / 2.0f + outlineThickness / 2.0f;
//			}
//		}
//		
//		shapes.push_back(line);
//		
//		offsetX = initialOffsetX;
//		offsetY = initialOffsetY + (i+1) * (sizes.height() + outlineThickness);
//
//	}
//
//
//}

void Map::GenerateFromImage(float screenWidth, float screenHeight, const sf::Image& mapImage)
{
	int imageWidth = mapImage.getSize().x;
	int imageHeight = mapImage.getSize().y;

	columns = imageWidth;
	rows = imageHeight;
	float outlineThickness = 2.0f;

	float hexWidth = ((3 * screenWidth) / (4 * columns) - outlineThickness) * 0.9f ;
	float hexHeight = ((screenHeight / (rows)) - outlineThickness) * 0.9f;

	 hexWidth =  (screenWidth / columns) * 3.0f/4.0f * 0.83f;
	 hexHeight = screenHeight / rows * 0.53f;

	Hexagon sizes(hexWidth < hexHeight ? hexWidth : hexHeight);

	float initialOffsetX = (sizes.width() + outlineThickness) * (3.0f / 4.0f);
	float initialOffsetY = (sizes.height() + outlineThickness) * 1.3f;
	float offsetX = initialOffsetX;
	float offsetY = initialOffsetY;

	shapes.resize(rows);
	terrain.resize(rows);

	for (int i = 0; i < rows; ++i)
	{
		shapes[i].resize(columns);
		terrain[i].resize(columns);

		for (int j = 0; j < columns; ++j)
		{

			Hexagon* tmp = new Hexagon(sizes);
			tmp->setOutlineColor(sf::Color::Blue);
			tmp->setOutlineThickness(outlineThickness);
			tmp->setPosition(offsetX, offsetY);

			sf::Color currentColor = mapImage.getPixel(j, i);

			if(currentColor == water)
			{
				terrain[i][j] = waterDifficulty;
				tmp->setFillColor(water);
			} else if(currentColor == sand)
			{
				terrain[i][j] = sandDifficulty;
				tmp->setFillColor(sand);
			} else if(currentColor == mud)
			{
				terrain[i][j] = mudDifficulty;
				tmp->setFillColor(mud);
			} else if(currentColor == grass)
			{
				terrain[i][j] = grassDifficulty;
				tmp->setFillColor(grass);
			} else if(currentColor == street)
			{
				terrain[i][j] = streetDifficulty;
				tmp->setFillColor(street);
			} else
			{
				terrain[i][j] = notfoundDifficulty;
				tmp->setFillColor(notfoundColor);
			}
			
			shapes[i][j] = tmp;

			offsetX += sizes.width() * 3.0f / 4.0f + outlineThickness / 2.0f;

			if (j % 2 == 0)
			{
				offsetY -= sizes.height() / 2.0f + outlineThickness / 2.0f;
			}
			else
			{
				offsetY += sizes.height() / 2.0f + outlineThickness / 2.0f;
			}
		}

		offsetX = initialOffsetX;
		offsetY = initialOffsetY + (i + 1) * (sizes.height() + outlineThickness);

	}

}
