#pragma once
#include "Agent_AnimState.h"

/**
  * @brief		Animation state. Excecutes when the agent wins the game
*/
class Agent_AnimWinState : public Agent_AnimState
{
public:
	/**
	  * @brief      Creates the state
	  * @param      sequence: the order and texture rects of the animation, taken of the texture given
	  * @param      atlasMap: the texture with all the images of the animation
	  * @param      fps: the speed of the animation (frames per second)
	  * @param      repeat: if the animation should end or repeat
	  * @bug	    No know Bugs
	*/
	Agent_AnimWinState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat);
	~Agent_AnimWinState();

	/**
	  * @brief      The start of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	void Enter(class Agent* agent);
	/**
	  * @brief      The update of the state. Returns the new state to the machine
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	eAGENT_ANIM_STATE_TYPE Update(class Agent* agent);
	/**
	  * @brief      The end of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	void Exit(class Agent* agent);
};