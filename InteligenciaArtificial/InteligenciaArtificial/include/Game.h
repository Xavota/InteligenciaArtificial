#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-sfml.h"

#include "AgentManager.h"
#include "Flag.h"

#include "UI.h"
#include "MenuManager.h"
#include "Start_menu.h"

//#include "Player.h"
//#include "StateMachine.h"

//#include "Animation.h"

#include "Agent_StateMachine.h"

#include "Camera.h"

/**
  * @brief		Struct for storing the teams
*/
struct Team
{
	std::string m_name;
	sf::IntRect m_spawnZone;
	sf::IntRect m_safeZone;
	sf::Vector2f m_seekPoint;

	sf::Color m_color;
	unsigned int m_points = 0;

	unsigned int m_teamMembers = 0;
};

/**
  * @brief		The main class. Tells everything to work and contains the main loop. UML:
  * @startuml
  * object hola
  * hola : saludo = "Si"
  * @enduml
*/
class Game
{
public:
	void Run();

	Game() = default;
	~Game() = default;

	static void Start(std::vector<void*> instance);
	static void Quit(std::vector<void*> instance);

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

	/**
	  * @brief      Checks if a team has won
	  * @param      team: the team to check
	  * @bug	    No know Bugs
	*/
	bool CheckWin(Team& team);

	/**
	  * @brief      Tell the agents to relocate on its spawn zone and return to FOLLOW_FLAG state
	  * @bug	    No know Bugs
	*/
	void Restart();

	/**
	  * @brief      Adds a team
	  * @param      teamName: the name of the new team
	  * @param      teamColor: the color of the new team
	  * @bug	    No know Bugs
	*/
	void AddTeam(std::string teamName, sf::Color teamColor);
	/**
	  * @brief      Adds teammates to a team
	  * @param      teamName: the name of the team
	  * @param      count: how many teammates
	  * @bug	    No know Bugs
	*/
	void AddTeammates(std::string teamName, unsigned int count);

	/**
	  * @brief      Removes a team
	  * @param      teamName: the name of the team
	  * @bug	    No know Bugs
	*/
	void RemoveTeam(std::string teamName);
	/**
	  * @brief      Removes teammates of a team
	  * @param      teamName: the name of the team
	  * @param      count: how many teammates
	  * @bug	    No know Bugs
	*/
	void RemoveTeammates(std::string teamName, unsigned int count);

	/**
	  * @brief      Updates the color of the team and teammates
	  * @param      teamName: the name of the team
	  * @param      color: the new color
	  * @bug	    No know Bugs
	*/
	void UpdateTeamColor(std::string teamName, sf::Color color);

	/**
	  * @brief      Updates the seek position, safe zone and spawn zone of all the teams
	  * @bug	    No know Bugs
	*/
	void UpdateTeamsZones();

public:
	/* Game (needed by the state machines)*/

	AgentManager m_manager;
	Flag m_flag;

	bool m_finished = false;
	bool m_restart = false;

	std::string m_winnerTeam = "";

private:
	/* Utility */

	sf::Vector2i m_windowSize;
	sf::RenderWindow* m_window = nullptr;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	Camera m_camera;

	bool m_play = false;


	/* Game */
	// Logic
	Agent_StateMachine m_agentsStateMachine;
	Agent_AnimMachine m_agentsAnimMachine;
	std::vector<Team> m_teams;

	int m_maxPoints = 1;
	int m_radious = 512;
	sf::Vector2f m_center = {512, 512};

	// Visual
	sf::RectangleShape m_stage;
	std::vector<sf::Text> m_pointsTexts;

	sf::Text m_titleText;
	sf::Text m_winnerText;




	/* Test */
	/*Player m_player;
	StateMachine m_stateMachine;
	Animation m_animMachine;*/
};

sf::RenderWindow* GetGameWindow(int x = 500, int y = 500);

Game* getGame();