#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-sfml.h"

#include "Camera.h"

#include "Grid.h"

/**
  * @brief		The main class. Tells everything to work and contains the main loop. UML:
  * @startuml
  * object hola
  * hola : saludo = "Si"
  * @enduml
*/
class Game_FP
{
public:
	void Run();

	Game_FP() = default;
	~Game_FP () = default;

private:

	/**
	  * @brief      Initialice everything in the game
	  * @bug	    No know Bugs
	*/
	void Init();
	/**
	  * @brief      Updates everything in the game
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Process the events and send them to the Input class
	  * @bug	    No know Bugs
	*/
	void ProcessEvents();
	/**
	  * @brief      Renders every actor
	  * @bug	    No know Bugs
	*/
	void Render();
	/**
	  * @brief      Constructs and render ImGui
	  * @bug	    No know Bugs
	*/
	void ImguiRender();
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

private:
	/* Utility */

	sf::Vector2i m_windowSize;
	sf::RenderWindow* m_window = nullptr;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	Camera m_camera;

	/* Behaviour */

	sf::Vector2i m_gridSize;
	sf::Vector2f m_cellsSize;

	Grid m_grid;
	float m_notFound = false;
};

Game_FP* getGame_FP();
