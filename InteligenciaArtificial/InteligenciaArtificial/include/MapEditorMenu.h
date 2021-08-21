#pragma once
#include "MenuManager.h"
class MapEditorMenu : public gl::MenuManager
{
public:
	/**
	  * @brief      Initializes the menu
	  * @bug	    No know Bugs
	*/
	void Init();
	/**
	  * @brief      Repositions the menu to screen space
	  * @param      wordlPosition: the position of the camera in the world
	  * @param      cameraSize: the scale of the camera
	  * @bug	    No know Bugs
	*/
	void Reposition(sf::Vector2f wordlPosition, sf::Vector2f cameraSize);
	/**
	  * @brief      Updates all the things in the menu
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Renders all the things in the menu
	  * @param      window: the window to where is gonna be rendered
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();	
};

