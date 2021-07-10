#pragma once
#include <vector>
#include "Agent_State.h"

class Agent;

class Agent_StateMachine
{
public:
	Agent_StateMachine();
	~Agent_StateMachine();

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
	void Update(Agent* agent);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

private:
	std::vector<Agent_State*> m_states;
	Agent_State* m_state;
};

