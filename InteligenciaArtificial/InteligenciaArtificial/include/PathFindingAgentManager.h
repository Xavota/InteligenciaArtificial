#pragma once
#include "PathFindingAgent.h"

class PathFindingAgentManager
{
public:
	PathFindingAgentManager();
	~PathFindingAgentManager();

	/**
	  * @brief      Initializes the Agent
	  * @param      stateMachine: the functional state machine the will control the agent
	  * @param      animMachine: the animation state machine the will control the agent's image
	  * @bug	    No know Bugs
	*/
	void Init(Agent_PathFindingStateMachine* stMachine, Agent_PathFindingAnimMachine* animMachine);
	/**
	  * @brief      Updates the Agent
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Renders the Agent
	  * @param      window: the window where is gonna be rendered
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

	/**
	  * @brief      Places the agent on a new position
	  * @param      pos: the position of the agent
	  * @bug	    No know Bugs
	*/
	void SetAgentPosition(sf::Vector2f pos);
	/**
	  * @brief      Returns the current position of the agent
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetAgentPosition();

	/**
	  * @brief      Sets the velocity for the movement of the agent
	  * @param      vel: the new velocity
	  * @bug	    No know Bugs
	*/
	void SetAgentVelocity(float vel);

private:
	PathFindingAgent m_agent;
};

