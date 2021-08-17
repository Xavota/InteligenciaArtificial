#pragma once
#include <SFML/Graphics.hpp>
#include "MenuManager.h"
#include <vector>

using namespace std;

class Start_menu : public gl::MenuManager
{
public:
	void Init();
	void Reposition(sf::Vector2f wordlPosition, sf::Vector2f cameraSize);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();
};

