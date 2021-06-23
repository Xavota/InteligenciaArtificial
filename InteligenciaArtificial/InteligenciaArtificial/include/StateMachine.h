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
	void Init(Player* player);
	/**
	  * @brief      Updates the state machine, and changes its internal states
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

private:
	Player* m_player;
	State* m_state = nullptr;

	std::vector<State*> m_states;
	eSTATE_TYPE m_current = eSTATE_TYPE::NONE;
};