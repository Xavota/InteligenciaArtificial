#pragma once
#include "MenuManager.h"
class MapEditorMenu : public gl::MenuManager
{
public:
	void Init();
	void Reposition(sf::Vector2f wordlPosition, sf::Vector2f cameraSize);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();	
};

