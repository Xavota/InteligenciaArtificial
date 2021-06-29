#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "PunchState.h"

//enum class ePUNCH_TYPE;

class Player
{
public:
	Player() = default;
	~Player() = default;

	/**
	  * @brief      Initiates the Player.
	  * @param      pos: the position on the screen of the player
	  * @param      size: the size of the player in pixels
	  * @param      tex: the texture of the player
	  * @param      velocity: the speed value of the player
	  * @param      jumpStrength: the jump force.
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2f pos, sf::Vector2f size, sf::Texture* tex, float velocity, float jumpStrength, StateMachine* machine);
	/**
	  * @brief      Updates the logic of the player
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Renders the player on a window
	  * @param      window: the window that it'll be rendering to
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Free the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

	eSTATE_TYPE GetState();
	void SetState(eSTATE_TYPE s);
	ePUNCH_TYPE GetPunchState();
	void SetPunchState(ePUNCH_TYPE s);

private:
	/* View */
	sf::RectangleShape m_shape;


	/* Movement */
	float m_velocity;
	float m_jumpStrength;


	/* State Machine */
	friend class PunchState;
	friend class PunchA;
	friend class PunchB;
	friend class PunchC;
	friend class KickState;
	StateMachine* m_machine;
	eSTATE_TYPE m_state = eSTATE_TYPE::STAND;
	ePUNCH_TYPE m_punchState = ePUNCH_TYPE::PUNCHA;

	float m_punchKickTimer = 0;
};

