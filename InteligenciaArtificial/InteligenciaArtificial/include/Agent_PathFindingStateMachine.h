#pragma once
#include "Agent_PathFindingState.h"
#include <vector>

class PathFindingAgent;

class Agent_PathFindingStateMachine
{
public:
	Agent_PathFindingStateMachine();
	~Agent_PathFindingStateMachine();

	/**
	  * @brief      Initialize the State machine
	  * @bug	    No know Bugs
	*/
	void Init();
	/**
	  * @brief      Updates the state machine, and changes its internal states
	  * @param      agent: the agent it will be controling
	  * @bug	    No know Bugs
	*/
	void Update(PathFindingAgent* agent);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

private:
	std::vector<Agent_PathFindingState*> m_states;
	Agent_PathFindingState* m_state = nullptr;
};

