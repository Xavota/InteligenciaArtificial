#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

class MenuManager;

using namespace std;

namespace gl {
class UI
{
public:
	static void Init(sf::RenderWindow* window);
	static void Update();
	static void ChangeMenu(MenuManager* menu);
	static void Render(sf::RenderWindow* window);
	static void Destroy();

protected:
	static sf::RenderWindow* m_window;

	static MenuManager* m_menu;
};
}
