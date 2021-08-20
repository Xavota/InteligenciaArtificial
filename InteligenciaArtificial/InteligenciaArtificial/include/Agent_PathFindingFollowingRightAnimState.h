#pragma once
#include "Agent_PathFindingAnimState.h"

/**
  * @brief		Animation state. Excecutes when the agent is running to the flag or the carrier of it.
*/
class Agent_PathFindingFollowingRightAnimState : public Agent_PathFindingAnimState
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
	Agent_PathFindingFollowingRightAnimState(std::vector<sf::IntRect> sequence, sf::Texture* atlasMap, float fps, bool repeat);
	~Agent_PathFindingFollowingRightAnimState();

	/**
	  * @brief      The start of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	void Enter(class PathFindingAgent* agent);
	/**
	  * @brief      The update of the state. Returns the new state to the machine
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	eAGENT_PATH_FINDING_ANIM_STATE_TYPE Update(class PathFindingAgent* agent);
	/**
	  * @brief      The end of the state
	  * @param      agent: the agent to modify its textures
	  * @bug	    No know Bugs
	*/
	void Exit(class PathFindingAgent* agent);
};

