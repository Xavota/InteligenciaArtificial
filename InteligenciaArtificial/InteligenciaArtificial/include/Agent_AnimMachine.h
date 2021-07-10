#pragma once
#include "Agent_AnimState.h"
#include <vector>

class Agent_AnimMachine
{
public:
	Agent_AnimMachine();
	~Agent_AnimMachine();

	/**
	  * @brief      Creates all the states needed by the machine
	  * @bug	    No know Bugs
	*/
	void Init();
	/**
	  * @brief      Updates the current state and changes the state if needed
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	void Update(class Agent* agent);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

private:
	Agent_AnimState* m_state;

	std::vector<Agent_AnimState*> m_states;
};

