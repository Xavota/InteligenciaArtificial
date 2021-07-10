#pragma once
#include "Agent_State.h"
class Agent_FollowCarrierState : public Agent_State
{
public:
	Agent_FollowCarrierState() = default;
	~Agent_FollowCarrierState() = default;

	/**
	  * @brief      Execute when the state starts
	  * @bug	    No know Bugs
	*/
	void Enter();
	/**
	  * @brief      Updates the state and handles the state changing. Returns the next state.
	  * @param      agent: the agent that will be controlling
	  * @bug	    No know Bugs
	*/
	eAGENT_STATE_TYPE Update(Agent* agent);
	/**
	  * @brief      Execute when the states finishes
	  * @bug	    No know Bugs
	*/
	void Exit();

private:

};

