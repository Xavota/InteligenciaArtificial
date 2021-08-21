#pragma once
#include "Agent_PathFindingStateMachine.h"
#include "Agent_PathFindingAnimMachine.h"

#include <SFML/Graphics.hpp>

class PathFindingAgent
{
public: 
	PathFindingAgent();
	~PathFindingAgent();

	/**
	  * @brief      Initializes the Agent
	  * @param      pos: the initial position of the agent
	  * @param      stateMachine: the functional state machine the will control the agent
	  * @param      animMachine: the animation state machine the will control the agent's image
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2f pos, Agent_PathFindingStateMachine* stateMachine,
	                            Agent_PathFindingAnimMachine* animMachine);
	/**
	  * @brief      Updates the Agent
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Renders the Agent
	  * @param      window: the window where is gonna be rendered
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();


	/**
	  * @brief      Places the agent on a new position
	  * @param      pos: the position of the agent
	  * @bug	    No know Bugs
	*/
	void SetPosition(sf::Vector2f pos);
	/**
	  * @brief      Returns the current position of the agent
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetPosition();
	

	/**
	  * @brief      Returns the current functiona state of the agent
	  * @bug	    No know Bugs
	*/
	eAGENT_PATH_FINDING_STATE_TYPE GetState();
	/**
	  * @brief      Sets the new functional state of the agent
	  * @param      state: the new state
	  * @bug	    No know Bugs
	*/
	void SetState(eAGENT_PATH_FINDING_STATE_TYPE state);
	/**
	  * @brief      Returns the new animation state of the agent
	  * @bug	    No know Bugs
	*/
	eAGENT_PATH_FINDING_ANIM_STATE_TYPE GetAnimState();
	/**
	  * @brief      Sets the new animation state of the agent
	  * @param      state: the new state
	  * @bug	    No know Bugs
	*/
	void SetAnimState(eAGENT_PATH_FINDING_ANIM_STATE_TYPE state);


	/**
	  * @brief      Set the set of points in order for the follow path behaviour
	  * @param      points: the new points to follow
	  * @param      restartCurrent: If is already following a path, true to restart the index of
	  *				the new point to follow.
	  * @bug	    No know Bugs
	*/
	void SetPathFollowPoints(std::vector<sf::Vector2f> points, bool restartCurrent = true);

	/**
	  * @brief      Turns on the follow path behaviour. Needed every frame.
	  * @bug	    No know Bugs
	*/
	void IsFollowing();


	/**
	  * @brief      Sets the new looking orientation of the agent
	  * @param      orientation: the new vectorial direction
	  * @bug	    No know Bugs
	*/
	void SetOrientation(sf::Vector2f orientation);
	/**
	  * @brief      Returns the new looking orientation of the agent
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetOrientation();
	/**
	  * @brief      Sets whether the agent can or cannot move.
	  * @param      can: true for free moving, false for no moving.
	  * @bug	    No know Bugs
	*/
	void CanMove(bool can);

	/**
	  * @brief      Sets the velocity for the movement of the agent
	  * @param      vel: the new velocity
	  * @bug	    No know Bugs
	*/
	void SetVelocity(float vel);

private:
	/**
	  * @brief      Gets the force for the seek behaviour to the given target
	  * @param      target: the position it will seek
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Seek(sf::Vector2f target);

	/**
	  * @brief      Gets the movement multiply value of the arrive behaviour
	  * @param      target: the position it will arrive
	  * @param      radious: the radious for stoping
	  * @bug	    No know Bugs
	*/
	float Arrive(sf::Vector2f target, float radious);

	/**
	  * @brief      Gets the force for the follow path behaiour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f PathFollow();
	

private:
	sf::RectangleShape m_shape;

	Agent_PathFindingStateMachine* m_stateMachine;
	eAGENT_PATH_FINDING_STATE_TYPE m_state = eAGENT_PATH_FINDING_STATE_TYPE::NONE;

	friend class Agent_PathFindingAnimState;

	Agent_PathFindingAnimMachine* m_animMachine;
	eAGENT_PATH_FINDING_ANIM_STATE_TYPE m_animState = eAGENT_PATH_FINDING_ANIM_STATE_TYPE::NONE;

	int m_animFrame = 0;
	float m_animTimer = 0;



	/* Steering behaviours */
	// utility
	sf::Vector2f m_orientation = { 0, -1 };
	float m_force = 100;
	float m_maxForce = 100;
	float m_mass = 20.f;
	float m_canMove = 1.0f;

	// seek
	std::vector<sf::Vector2f> m_seekTargets;

	// Follow Path
	std::vector<sf::Vector2f> m_followPathPoints;
	unsigned int m_followPathIndex = 0;
	float m_followPathMinDistance = 25.0f;
	bool m_isFollowing = false;
};

