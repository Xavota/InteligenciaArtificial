#pragma once
#include <SFML/Graphics.hpp>
class Agent;

/**
  * @brief		The flag that will be captured
*/
class Flag
{
public:
	Flag() = default;
	/**
	  * @brief      Constructor. Calls the Init function
	  * @param      pos: the initial position of the flag
	  * @bug	    No know Bugs
	*/
	Flag(sf::Vector2f pos);
	~Flag() = default;

	/**
	  * @brief      Initialize the flag
	  * @param      pos: the initial position of the flag
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2f pos);
	/**
	  * @brief      Updates the flag
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Renders the flag
	  * @param      window: the window where it'll be rendered
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

	/**
	  * @brief      Returns the agents that is carrying the flag
	  * @bug	    No know Bugs
	*/
	Agent* GetCarrier();
	/**
	  * @brief      Changes the agents that is carrying the flag
	  * @param      carrier: the agent carrying the flag
	  * @bug	    No know Bugs
	*/
	void SetCarrier(Agent* carrier);

	/**
	  * @brief      Returns the position of the flag
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetPosition();
	/**
	  * @brief      Sets the position of the flag
	  * @param      pos: the new position
	  * @bug	    No know Bugs
	*/
	void SetPosition(sf::Vector2f pos);
	/**
	  * @brief      Returns the min distance for an agent to catch the flag
	  * @bug	    No know Bugs
	*/
	float GetRadious();

	/**
	  * @brief      Asks if the flag can be picked up
	  * @bug	    No know Bugs
	*/
	bool CanBePickedUp();

private:
	// shape
	sf::RectangleShape m_shape;

	// min distance to be picked up
	float m_radious = 20;

	// Agent carrying
	Agent* m_carrier = nullptr;

	// Time until it can be picked up again
	float m_timeTillUp = 0.0f;
};

