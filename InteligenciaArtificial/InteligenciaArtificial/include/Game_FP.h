#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-sfml.h"

#include <windows.h>


#include "Camera.h"

#include "Grid.h"
#include "PathFindingAgentManager.h"
#include "Agent_PathFindingStateMachine.h"
#include "Agent_PathFindingAnimMachine.h"

/**
  * @brief		The main class. Tells everything to work and contains the main loop. UML:
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

	void OpenMapFile(std::string mapName);
	void SaveMapFile(std::string mapName);

public:
	static void Grass(std::vector<void*> params);
	static void Sand(std::vector<void*> params);
	static void Water(std::vector<void*> params);
	static void Wall(std::vector<void*> params);

public:
	Grid m_grid;
	PathFindingAgentManager m_manager;

private:
	/* Utility */

	sf::Vector2i m_windowSize;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	Camera m_camera;

	/* Behaviour */

	Agent_PathFindingStateMachine m_stateMachine;
	Agent_PathFindingAnimMachine m_animMachine;

	sf::Vector2i m_gridSize;
	sf::Vector2f m_cellsSize;

	bool m_notFound = false;

public:
	sf::RenderWindow* m_window = nullptr;	
};

Game_FP* getGame_FP();

std::string OpenFileGetName(HWND owner = NULL);
std::string SaveFileGetName(HWND owner = NULL);