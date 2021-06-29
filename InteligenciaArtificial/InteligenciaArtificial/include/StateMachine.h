#pragma once
#include "State.h"
#include <vector>

class Player;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	/**
	  * @brief      Initialize the State machine
	  * @param      player: the player it will be controling
	  * @bug	    No know Bugs
	*/
	void Init();
	/**
	  * @brief      Updates the state machine, and changes its internal states
	  * @bug	    No know Bugs
	*/
	void Update(Player* player);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

private:
	State* m_state = nullptr;

	std::vector<State*> m_states;
};