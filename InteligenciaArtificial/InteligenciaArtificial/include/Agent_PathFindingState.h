#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class PathFindingAgent;

/**
  * @brief		The diferent functional states. Its used to identify in what state is an agent.
*/
enum class eAGENT_PATH_FINDING_STATE_TYPE
{
	NONE = -1,
	WAITING,
	FOLLIWING,
	ARRIVE,
	COUNT
};

/**
  * @brief		Tha father of all the functional states.
*/
class Agent_PathFindingState
{
public:
	Agent_PathFindingState() = default;
	virtual ~Agent_PathFindingState() = default;

	/**
	  * @brief      Execute when the state starts
	  * @bug	    No know Bugs
	*/
	virtual void Enter(PathFindingAgent* agent) = 0;
	/**
	  * @brief      Updates the state and handles the state changing. Returns the next state.
	  * @param      agent: the agent that will be controlling
	  * @bug	    No know Bugs
	*/
	virtual eAGENT_PATH_FINDING_STATE_TYPE Update(PathFindingAgent* agent) = 0;
	/**
	  * @brief      Execute when the states finishes
	  * @bug	    No know Bugs
	*/
	virtual void Exit(PathFindingAgent* agent) = 0;

protected:
	PathFindingAgent* m_player;
};

