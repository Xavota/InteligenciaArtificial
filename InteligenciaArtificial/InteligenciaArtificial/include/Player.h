#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.h"

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
	void Init(sf::Vector2f pos, sf::Vector2f size, sf::Texture* tex, float velocity, float jumpStrength);
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

private:
	float m_velocity;
	float m_jumpStrength;
	sf::RectangleShape m_shape;

	StateMachine m_machine;
};

