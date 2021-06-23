#pragma once
class Player;

enum class eSTATE_TYPE
{
	NONE = -1,
	STAND,
	CROUCH,
	PUNCH,
	KICK,
	COUNT
};

class State
{
public:
	State();
	virtual ~State();

	/**
	  * @brief      Execute when the state starts
	  * @param      player: the player that will be controlling
	  * @bug	    No know Bugs
	*/
	virtual void Enter(Player* a) = 0;
	/**
	  * @brief      Updates the state and handles the state changing. Returns the next state.
	  * @bug	    No know Bugs
	*/
	virtual eSTATE_TYPE Update() = 0;
	/**
	  * @brief      Execute when the states finishes
	  * @bug	    No know Bugs
	*/
	virtual void Exit() = 0;

protected:
	Player* m_player;
};

