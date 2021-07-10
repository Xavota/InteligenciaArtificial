#pragma once
#include "Agent_State.h"

/**
  * @brief		Functional state. Excecutes when the agent has won or lost the game
*/
class Agent_WinLoseState : public Agent_State
{
public:
	Agent_WinLoseState() = default;
	~Agent_WinLoseState() = default;

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

