#pragma once
#include "Agent_PathFindingStateMachine.h"
#include "Agent_PathFindingAnimMachine.h"

#include <SFML/Graphics.hpp>

class PathFindingAgent
{
public: 
	PathFindingAgent();
	~PathFindingAgent();

	void Init(sf::Vector2f pos, Agent_PathFindingStateMachine* stateMachine,
	                            Agent_PathFindingAnimMachine* animMachine);
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();


	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	

	eAGENT_PATH_FINDING_STATE_TYPE GetState();
	void SetState(eAGENT_PATH_FINDING_STATE_TYPE state);
	eAGENT_PATH_FINDING_ANIM_STATE_TYPE GetAnimState();
	void SetAnimState(eAGENT_PATH_FINDING_ANIM_STATE_TYPE state);


	void SetPathFollowPoints(std::vector<sf::Vector2f> points, bool restartCurrent = true);

	void IsFollowing();

	
	void SetOrientation(sf::Vector2f orientation);
	sf::Vector2f GetOrientation();
	void CanMove(bool can);

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

