#pragma once
#include "Agent_PathFindingState.h"

/**
  * @brief		Animation state. Excecutes when the agent is carrying the flag
*/
class Agent_PathFindingFolowingState : public Agent_PathFindingState
{
public:
	Agent_PathFindingFolowingState() = default;
	~Agent_PathFindingFolowingState() = default;

	/**
	  * @brief      Execute when the state starts
	  * @bug	    No know Bugs
	*/
	void Enter(PathFindingAgent* agent);
	/**
	  * @brief      Updates the state and handles the state changing. Returns the next state.
	  * @param      agent: the agent that will be controlling
	  * @bug	    No know Bugs
	*/
	eAGENT_PATH_FINDING_STATE_TYPE Update(PathFindingAgent* agent);
	/**
	  * @brief      Execute when the states finishes
	  * @bug	    No know Bugs
	*/
	void Exit(PathFindingAgent* agent);

private:
	std::vector<sf::Vector2f> m_path;
};
