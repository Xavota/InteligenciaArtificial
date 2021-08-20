#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class PathFindingAgent;

/**
  * @brief		The diferent animation states. Its used to identify in what state is an agent.
*/
enum class eAGENT_PATH_FINDING_ANIM_STATE_TYPE
{
	NONE = -1,
	WAITING,
	FOLLIWING_UP,
	FOLLIWING_RIGHT,
	FOLLIWING_DOWN,
	FOLLIWING_LEFT,
	ARRIVE,
	COUNT
};

/**
  * @brief		The father of all the animation states.
*/
class Agent_PathFindingAnimState
{
public:
	Agent_PathFindingAnimState() = default;
	virtual ~Agent_PathFindingAnimState() = default;

	/**
	  * @brief      The start of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	virtual void Enter(PathFindingAgent* agent);
	/**
	  * @brief      The update of the state. Returns the new state to the machine
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	virtual eAGENT_PATH_FINDING_ANIM_STATE_TYPE Update(PathFindingAgent* agent);
	/**
	  * @brief      The end of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	virtual void Exit(PathFindingAgent* agent);
protected:
	std::vector<sf::IntRect> m_sequenceRects;
	sf::Texture* m_atlasMap = nullptr;

	float m_fps = 0;
	bool m_repeat = false;
};

