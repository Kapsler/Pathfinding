#include "Map.h"
#include <deque>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Agent.h"

Map::Map(float screenWidth, float screenHeight, const std::string& filename)
{
	LoadMapFromImage(screenWidth, screenHeight, filename);

	debugFont.loadFromFile("./Assets/arial.ttf");
	debugText.setFont(debugFont);
	debugText.setCharacterSize(18);
	debugText.setFillColor(sf::Color::White);
	debugText.setOutlineThickness(2);
	debugText.setOutlineColor(sf::Color::Black);
}

Map::~Map()
{
	for(auto line : hexMap)
	{
		for (auto hex : line)
		{
			delete hex;
		}
	}
}

void Map::Render(sf::RenderWindow* window)
{
	ResetThreat();

	sf::Color r = sf::Color::Red;

	for(const auto line : hexMap)
	{
		for(const auto hexdat : line)
		{
			window->draw(*(hexdat->hex));

			if(hexdat->threat > 0)
			{
				Hexagon threatHex = *hexdat->hex;
				r.a = 50 * hexdat->threat;
				threatHex.setFillColor(r);
				threatHex.setOutlineColor(sf::Color::Red);
				window->draw(threatHex);
			}
			
		}
	}

	if (selectedHexDat != nullptr)
	{
		Hexagon drawSelected = *selectedHexDat->hex;
		drawSelected.setOutlineColor(sf::Color::Cyan);
		window->draw(drawSelected);
	}
}

void Map::DebugRender(sf::RenderWindow* window)
{
	/*if (selectedHexDat != nullptr)
	{
		Hexagon drawSelected;

		for(auto hexdat : GetNeighbors(selectedHexDat, hexMap))
		{
			drawSelected = *hexdat->hex;
			drawSelected.setOutlineColor(sf::Color::Cyan);
			window->draw(drawSelected);
		}

		drawSelected = *selectedHexDat->hex;
		drawSelected.setOutlineColor(sf::Color::Red);
		window->draw(drawSelected);


		for (auto hexdat : debugPath)
		{
			drawSelected = *hexdat->hex;
			drawSelected.setFillColor(sf::Color(255,0,255,255));
			window->draw(drawSelected);
		}
	}*/


	//DebugRenderText(window);
}

void Map::DebugRenderText(sf::RenderWindow* window)
{
	//DebugText - Render Indices on Hexes

	for (const auto line : hexMap)
	{
		for (const auto hexdat : line)
		{
			debugText.setPosition(hexdat->hex->getPosition());
			debugText.setString(std::to_string(hexdat->index.x) + "," + std::to_string(hexdat->index.y));
			debugText.setOrigin(debugText.getGlobalBounds().width / 2.0f, debugText.getGlobalBounds().height / 2.0f);
			window->draw(debugText);
		}
	}
}

std::vector<HexData*> Map::GetNeighbors(HexData* current, std::vector<std::vector<HexData*>> &usedMap)
{
	std::vector<HexData*> neighbors;

	sf::Vector2i evenOffsets[6] = { sf::Vector2i(0,1), sf::Vector2i(1,0), sf::Vector2i(0,-1), sf::Vector2i(-1,0), sf::Vector2i(+1,-1), sf::Vector2i(+1, +1) };
	sf::Vector2i oddOffsets[6] = { sf::Vector2i(0,1), sf::Vector2i(1,0), sf::Vector2i(0,-1), sf::Vector2i(-1,0), sf::Vector2i(-1,+1), sf::Vector2i(-1, -1) };

	Hexagon drawSelected;
	sf::Vector2i* offsets = current->index.y % 2 == 0 ? evenOffsets : oddOffsets;

	for (auto i = 0; i < 6; ++i)
	{
		auto xindex = current->index.x + offsets[i].x;
		auto yindex = current->index.y + offsets[i].y;

		if (xindex >= 0 && xindex < usedMap.size() && yindex >= 0 && yindex < usedMap[0].size())
		{
			neighbors.push_back(usedMap[xindex][yindex]);
		}
	}

	return neighbors;
}

std::vector<HexData*> Map::AStarPath(HexData* start, HexData* target, std::vector<std::vector<HexData*>> &usedMap)
{

	ResetThreat();

	//Breadth Search
	std::vector<HexData*> foundPath;
	std::unordered_map<HexData*, HexData*> cameFrom;
	std::unordered_map<HexData*, int> costsSoFar;
	std::multimap<float, HexData*> priorityToDo;

	if(GetDifficulty(target) >= unpassable)
	{
		std::cout << "Target is unpassable!" << std::endl;
		return foundPath;
	}

	priorityToDo.insert(std::pair<float, HexData*>(0.0f, start));
	cameFrom.insert_or_assign(start, nullptr);
	costsSoFar.insert_or_assign(start, 0);

	HexData* currentHex;

	while (!priorityToDo.empty())
	{
	currentHex = priorityToDo.begin()->second;
	priorityToDo.erase(priorityToDo.begin());
	
		if(currentHex == target)
		{
			break;
		}
	
		for (HexData* neighbor : GetNeighbors(currentHex, usedMap))
		{
			int difficulty = GetDifficulty(neighbor);
			if(difficulty >= unpassable)
			{
				costsSoFar.insert_or_assign(neighbor, unpassable);
			}
			int newCosts = costsSoFar[currentHex] + difficulty;
			

			if (costsSoFar.find(neighbor) == costsSoFar.end() || newCosts < costsSoFar.at(neighbor))
			{
				costsSoFar.insert_or_assign(neighbor, newCosts);
				float priority = newCosts;
				priorityToDo.insert(std::pair<float, HexData*>(priority, neighbor));
				cameFrom.insert_or_assign(neighbor, currentHex);
			}
		}
	}

	//Build Path
	currentHex = target;
	foundPath.push_back(currentHex);

	while(currentHex != start)
	{
		currentHex = cameFrom.at(currentHex);
		foundPath.push_back(currentHex);
	}

	std::reverse(foundPath.begin(), foundPath.end());

	//Adds all tested nodes to path
	//for(auto it = cameFrom.begin(); it != cameFrom.end(); ++it)
	//{
	//	if(it->second != nullptr)
	//	{
	//		foundPath.push_back(it->second);
	//	}
	//		
	//}

	//std::cout << "Found Path! Size: " << foundPath.size() << std::endl;

	return foundPath;
}

int Map::GetDifficulty(HexData* HexToTest)
{
	return HexToTest->terrain + HexToTest->threat;
}


void Map::HandleKeyboard(sf::Keyboard::Key key)
{

}

void Map::HandleMouse(sf::Vector2f& mousePosition)
{
	sf::Vector2f mousePos = sf::Vector2f(mousePosition);

	SetCurrentHex(mousePos);
	
}

void Map::HandleMouse(sf::Mouse::Button mb)
{
	//if (mb == sf::Mouse::Left)
	//{
	//	debugPath = AStarPath(hexMap[0][0], selectedHexDat, *GetMapPtr());
	//}
}

std::vector<std::vector<HexData*>>* Map::GetMapPtr()
{
	return &hexMap;
}

HexData* Map::GetSelectedHex() const
{
	return selectedHexDat;
}

float Map::GetHexSize() const
{
	return hexsize * 2.0f;
}

sf::Vector2f Map::GetPositionByIndex(int x, int y)
{
	return hexMap[x][y]->hex->getPosition();
}

sf::Vector2f Map::GetPositionByIndex(sf::Vector2i posIndex)
{
	return hexMap[posIndex.x][posIndex.y]->hex->getPosition();
}

HexData* Map::GetHexDatByIndex(int x, int y)
{
	return hexMap[x][y];
}

void Map::AddThreat(Agent* threat)
{
	threats.push_back(threat);
}

void Map::ResetThreat()
{
	for(auto l : hexMap)
	{
		for(auto h : l)
		{
			h->threat = 0;
		}
	}

	for(auto t : threats)
	{
		t->GetThreatStencil()->SetThreats(t->GetPositionIndex(), *GetMapPtr());
		hexMap[t->GetPositionIndex().x][t->GetPositionIndex().y]->threat += unpassable;
	}
		
}

float Map::distanceBetweenFloatPoints(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}

void Map::SetCurrentHex(const sf::Vector2f& mousePos)
{
	float closestDist = std::numeric_limits<float>::max();
	float dist;

	for (const auto line : hexMap)
	{
		for (const auto hexdat : line)
		{
			dist = distanceBetweenFloatPoints(mousePos, hexdat->hex->getPosition());
			if (dist < closestDist)
			{
				closestDist = dist;
				selectedHexDat = hexdat;
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

void Map::GenerateFromImage(float screenWidth, float screenHeight, const sf::Image& mapImage)
{
	int imageWidth = mapImage.getSize().x;
	int imageHeight = mapImage.getSize().y;

	columns = imageWidth;
	rows = imageHeight;
	float outlineThickness = 2.0f;

	float hexWidth = (screenWidth / columns) * 3.0f/4.0f * 0.83f;
	float hexHeight = ((screenHeight) / rows) * 0.53f;

	hexsize = hexWidth < hexHeight ? hexWidth : hexHeight;

	Hexagon sizes(hexsize);

	float initialOffsetX = (sizes.width() + outlineThickness) * (3.0f / 4.0f);
	float initialOffsetY = (sizes.height() + outlineThickness) * 1.3f;
	float offsetX = initialOffsetX;
	float offsetY = initialOffsetY;

	hexMap.resize(rows);

	for (int i = 0; i < rows; ++i)
	{
		hexMap[i].resize(columns);

		for (int j = 0; j < columns; ++j)
		{
			HexData *hexDatTmp = new HexData();

			Hexagon* tmp = new Hexagon(sizes);
			tmp->setOutlineColor(sf::Color::Blue);
			tmp->setOutlineThickness(outlineThickness);
			tmp->setPosition(offsetX, offsetY);


			sf::Color currentColor = mapImage.getPixel(j, i);

			if(currentColor == water)
			{
				 hexDatTmp->terrain = waterDifficulty;
				tmp->setFillColor(water);
			} else if(currentColor == sand)
			{
				hexDatTmp->terrain = sandDifficulty;
				tmp->setFillColor(sand);
			} else if(currentColor == mud)
			{
				hexDatTmp->terrain = mudDifficulty;
				tmp->setFillColor(mud);
			} else if(currentColor == grass)
			{
				hexDatTmp->terrain = grassDifficulty;
				tmp->setFillColor(grass);
			} else if(currentColor == street)
			{
				hexDatTmp->terrain = streetDifficulty;
				tmp->setFillColor(street);
			} else
			{
				hexDatTmp->terrain = notfoundDifficulty;
				tmp->setFillColor(notfoundColor);
			}

			hexDatTmp->hex = tmp;
			hexDatTmp->index.x = i;
			hexDatTmp->index.y = j;
			hexMap[i][j] = hexDatTmp;

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
