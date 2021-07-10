#pragma once

class Agent;

enum class eAGENT_STATE_TYPE
{
	NONE = -1,
	FOLLOW_FLAG,
	FOLLOW_CARRIER,
	PROTECT_FALG,
	HAS_FLAG,
	WIN_LOSE,
	COUNT
};

class Agent_State
{
public:
	Agent_State() = default;
	virtual ~Agent_State() = default;

	/**
	  * @brief      Execute when the state starts
	  * @bug	    No know Bugs
	*/
	virtual void Enter() = 0;
	/**
	  * @brief      Updates the state and handles the state changing. Returns the next state.
	  * @param      agent: the agent that will be controlling
	  * @bug	    No know Bugs
	*/
	virtual eAGENT_STATE_TYPE Update(Agent* agent) = 0;
	/**
	  * @brief      Execute when the states finishes
	  * @bug	    No know Bugs
	*/
	virtual void Exit() = 0;

protected:
	Agent* m_player;
};

