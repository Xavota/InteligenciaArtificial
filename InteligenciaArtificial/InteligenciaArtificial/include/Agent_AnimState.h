#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Agent;

/**
  * @brief		The diferent animation states. Its used to identify in what state is an agent.
*/
enum class eAGENT_ANIM_STATE_TYPE
{
	NONE = -1,
	RUNNING,
	HAS_FLAG,
	WIN,
	LOSE,
	COUNT
};

/**
  * @brief		The father of all the animation states.
*/
class Agent_AnimState
{
public:
	Agent_AnimState() = default;
	virtual ~Agent_AnimState() = default;

	/**
	  * @brief      The start of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	virtual void Enter(Agent* agent);
	/**
	  * @brief      The update of the state. Returns the new state to the machine
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	virtual eAGENT_ANIM_STATE_TYPE Update(Agent* agent);
	/**
	  * @brief      The end of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	virtual void Exit(Agent* agent);
protected:
	std::vector<sf::IntRect> m_sequenceRects;
	sf::Texture* m_atlasMap = nullptr;

	float m_fps = 0;
	bool m_repeat = false;
};

