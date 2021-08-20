#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;

#include "Agent_StateMachine.h"
#include "Agent_AnimMachine.h"

/**
  * @brief		The types of behaviours the agent can do
*/
enum class eBEHAVIOUR
{
	NONE = -1,
	SEEK,
	FLEE,
	WANDER,
	PURSUIT,
	EVADE,
	COLLITION_AVOIDANCE,
	PATH_FOLLOWING,
	FLOCKING,
	LEADER_FOLLOWING,
	QUEUE,
	COUNT
};

/**
  * @brief		The ways that the follow path can be done
*/
enum class ePATH_FOLLOWING_TYPE
{
	NONE = -1,
	FINITE,
	CYCLIC,
	RETURN,
	COUNT
};

/**
  * @brief		The agent, controlled by their own AI with steering behaviours
*/
class Agent
{
public:
	Agent() = default;
	/**
	  * @brief      Constructor
	  * @param      x: the position in x coordinate
	  * @param      y: the position in y coordinate
	  * @param      color: the color of the agent
	  * @param      teamName: the team it is on
	  * @param      basePos: the point it has to take the flag
	  * @param      stMachine: the state machine that will be controlling it
	  * @param      animMachine: the animation machine the will be controlling its textures
	  * @bug	    No know Bugs
	*/
	Agent(int x, int y, sf::Color color, std::string teamName, sf::Vector2f basePos, Agent_StateMachine* stMachine, Agent_AnimMachine* animMachine);
	~Agent();
	
	/**
	  * @brief      Initialice
	  * @param      x: the position in x coordinate
	  * @param      y: the position in y coordinate
	  * @param      color: the color of the agent
	  * @param      teamName: the team it is on
	  * @param      basePos: the point it has to take the flag
	  * @param      stMachine: the state machine that will be controlling it
	  * @param      animMachine: the animation machine the will be controlling its textures
	  * @bug	    No know Bugs
	*/
	void Init(int x, int y, sf::Color color, std::string teamName, sf::Vector2f basePos, Agent_StateMachine* stMachine, Agent_AnimMachine* animMachine);

	/**
	  * @brief      Updates the agent
	  * @bug	    No know Bugs
	*/
	void Update();

	/**
	  * @brief      Moves the agent
	  * @param      velocity: the velocity in pixels per second of the movement
	  * @bug	    No know Bugs
	*/
	void Move(sf::Vector2f velocity);
	
	/**
	  * @brief      Returns the position of the agent
	  * @bug	    No know Bugs
	*/
	sf::Vector2f getPosition() { return m_shape.getPosition(); }

	/**
	  * @brief      Sets the position of the agent
	  * @param      pos: the new position
	  * @bug	    No know Bugs
	*/
	void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }

	/**
	  * @brief      Retursn the current velocity of the agent
	  * @bug	    No know Bugs
	*/
	sf::Vector2f getVelocity() { return m_orientation * m_force; }

	/**
	  * @brief      Returns the direccion of the agent
	  * @bug	    No know Bugs
	*/
	sf::Vector2f getOrientation() { return m_orientation; }

	/**
	  * @brief      Renders the agent and its components
	  * @param      window: the window to wich it will be rendered
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);

	/**
	  * @brief      Free memory if needed
	  * @bug	    No know Bugs
	*/
	void Destroy();


	/**
	  * @brief      Adds a target to the seek behaviour
	  * @param      target: the position it will seek
	  * @bug	    No know Bugs
	*/
	void AddSeekTarget(sf::Vector2f target);

	/**
	  * @brief      Adds a target to the flee behaviour
	  * @param      target: the position it will flee of
	  * @bug	    No know Bugs
	*/
	void AddFleeTarget(sf::Vector2f target);


	/**
	  * @brief      Adds the wander behaviour
	  * @bug	    No know Bugs
	*/
	void AddWanderBehaviour();

	/**
	  * @brief      Adds a target to the pursuit behaviour
	  * @param      target: the position it will pursue
	  * @param      velocity: the velocity of the target
	  * @bug	    No know Bugs
	*/
	void AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity);

	/**
	  * @brief      Adds a target to the evade behaviour
	  * @param      target: the position it will evade
	  * @param      velocity: the velocity of the target
	  * @bug	    No know Bugs
	*/
	void AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity);


	/**
	  * @brief      Adds a target to the obstacle behaviour
	  * @param      obstacle: the position of the obstacle
	  * @param      radious: the radious of the obstacle
	  * @bug	    No know Bugs
	*/
	void AddObstacleToAvoid(sf::Vector2f obstacle, float radious);


	/**
	  * @brief      Adds a target to the follow path behaviour
	  * @param      target: the position of the next path point
	  * @bug	    No know Bugs
	*/
	void AddFollowPathPoint(sf::Vector2f point);

	/**
	  * @brief      Sets the type of the follow path behaviour
	  * @param      type: the kind of follow path
	  * @bug	    No know Bugs
	*/
	void SetFollowPathMode(ePATH_FOLLOWING_TYPE type);


	/**
	  * @brief      Adds the flocking behaviour
	  * @bug	    No know Bugs
	*/
	void AddFlockingBehaviour();

	/**
	  * @brief      Sets the flocking gruop for the agent
	  * @param      agents: the agents of its flocking group
	  * @bug	    No know Bugs
	*/
	void SetFlockingAgentsGroup(vector<Agent*> agents);

	/**
	  * @brief      Returns true if the agent has the flocking behaviour
	  * @bug	    No know Bugs
	*/
	bool IsFlocking();

	/**
	  * @brief      Returns the radiuos of the flocking behaviour gruop
	  * @bug	    No know Bugs
	*/
	float GetFlockingGroupRadious();


	/**
	  * @brief      Returns the name of the team he is on
	  * @bug	    No know Bugs
	*/
	std::string GetTeam() { return m_teamName; }


	/**
	  * @brief      Set true if its neer a wall and it's seeing it
	  * @param      wall: is seeing wall
	  * @bug	    No know Bugs
	*/
	void SetIsSeeingWall(bool wall) { m_isSeeingWall = wall; }

	/**
	  * @brief      Returns true if it's seeing a wall
	  * @bug	    No know Bugs
	*/
	bool GetIsSeeingWall() { return m_isSeeingWall; }

private:

	/**
	  * @brief      Returns true if the agent has the behaviuor is passing
	  * @param      behaviour: the behaviour checking
	  * @bug	    No know Bugs
	*/
	bool HasBehaviour(eBEHAVIOUR behaviour);


	/**
	  * @brief      Gets the force for the seek behaviour to the given target
	  * @param      target: the position it will seek
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Seek(sf::Vector2f target);

	/**
	  * @brief      Gets the force for the flee behaviour to the given target
	  * @param      target: the position it will flee of
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Flee(sf::Vector2f target);

	/**
	  * @brief      Gets the movement multiply value of the arrive behaviour
	  * @param      target: the position it will arrive
	  * @param      radious: the radious for stoping
	  * @bug	    No know Bugs
	*/
	float Arrive(sf::Vector2f target, float radious);


	/**
	  * @brief      Gets the force for the wander behaviour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Wander();

	/**
	  * @brief      Gets the force for the pursuit behaviour to the given target
	  * @param      target: the position it will pursue
	  * @param      velocity: the velocity of the target
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Pursuit(sf::Vector2f target, sf::Vector2f velocity);

	/**
	  * @brief      Gets the force for the evade behaviour to the given target
	  * @param      target: the position it will evade
	  * @param      velocity: the velocity of the target
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Evade(sf::Vector2f target, sf::Vector2f velocity);


	/**
	  * @brief      Gets the force for the collition avoidance behaviour
	  * @param      obstacle: the position of the obstacle
	  * @param      radious: the radious of the obstacle
	  * @bug	    No know Bugs
	*/
	sf::Vector2f AvoidObstacles();

	/**
	  * @brief      Returns true if is seeing the obstacle given
	  * @param      obsPos: the position of the obstacle
	  * @param      obsRad: the radious of the obstacle
	  * @param      out_ortoVec: the returned ortogonal vector between the agent and the obstacle
	  * @bug	    No know Bugs
	*/
	bool IsSeeingObstacle(sf::Vector2f obsPos, float obsRad, sf::Vector2f& out_ortoVec);


	/**
	  * @brief      Gets the force for the follow path behaiour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f PathFollow();

	/**
	  * @brief      Gets the force for the flocking behaiour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Flocking();

	/**
	  * @brief      Gets the force for the separation behaiour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Separation();

	/**
	  * @brief      Gets the force for the cohesion behaiour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Cohesion();

	/**
	  * @brief      Gets the force for the alignment behaiour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Alignment();

public:

	/**
	  * @brief      Returns the length of the vector
	  * @param      vec: the vector checking
	  * @bug	    No know Bugs
	*/
	static float vectorLength(sf::Vector2f vec);
	/**
	  * @brief      Returns the vector normalized
	  * @param      vec: the vector checking
	  * @bug	    No know Bugs
	*/
	static sf::Vector2f normalizeVector(sf::Vector2f vec);
	/**
	  * @brief      Returns the vector with the length specified
	  * @param      vec: the vector checking
	  * @param      length: the new length of the vector
	  * @bug	    No know Bugs
	*/
	static sf::Vector2f truncateVector(sf::Vector2f vec, float length);
	/**
	  * @brief      Returns the distance between two vectors
	  * @param      vec1: the first vector checking
	  * @param      vec2: the second vector checking
	  * @bug	    No know Bugs
	*/
	static float distanceVector(sf::Vector2f vec1, sf::Vector2f vec2);
	/**
	  * @brief      Returns the dot product between 2 vectors
	  * @param      vec1: the first vector checking
	  * @param      vec2: the second vector checking
	  * @bug	    No know Bugs
	*/
	static float dot(sf::Vector2f vec1, sf::Vector2f vec2);
	/**
	  * @brief      Returns the right vector of the vector passed
	  * @param      vec: the vector checking
	  * @bug	    No know Bugs
	*/
	static sf::Vector2f rightVector(sf::Vector2f vec);

	/**
	  * @brief      Returns the right vector of the vector passed
	  * @param      line: the rectangle shape the will be turning into the line needed
	  * @param      pos1: start position
	  * @param      pos2: end position
	  * @bug	    No know Bugs
	*/
	void placeLineFromTwoPoints(sf::RectangleShape& line, sf::Vector2f pos1, sf::Vector2f pos2);


	/* Capture the flag */
	/**
	  * @brief      Returns the position of the agents base
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetBasePos();
	/**
	  * @brief      Updates the position of the agent's base
	  * @param      pos: the new position of the base
	  * @bug	    No know Bugs
	*/
	void UpdateBasePos(sf::Vector2f pos);
	/**
	  * @brief      Returns the color of the agent
	  * @bug	    No know Bugs
	*/
	sf::Color GetColor();
	/**
	  * @brief      Updates the color of the agent
	  * @param      color: the new color
	  * @bug	    No know Bugs
	*/
	void UpdateColor(sf::Color color);

	/* State machines */
	// Function
	/**
	  * @brief      Returns the current state
	  * @bug	    No know Bugs
	*/
	eAGENT_STATE_TYPE GetState();
	/**
	  * @brief      Updates the current state
	  * @param      stae: the new state
	  * @bug	    No know Bugs
	*/
	void SetState(eAGENT_STATE_TYPE state);

	// Animation
	/**
	  * @brief      Returns the current state of the animation
	  * @bug	    No know Bugs
	*/
	eAGENT_ANIM_STATE_TYPE GetAnimState();
	/**
	  * @brief      Updates the current state of the animation
	  * @param      pos: the new state
	  * @bug	    No know Bugs
	*/
	void SetAnimState(eAGENT_ANIM_STATE_TYPE state);

	/**
	  * @brief      Sets the texture of the agent
	  * @param      tec: the new texture
	  * @bug	    No know Bugs
	*/
	void SetTexture(sf::Texture* tex);
	/**
	  * @brief      Sets the texture rect of the texture on the agent
	  * @param      rect: the texture rect
	  * @bug	    No know Bugs
	*/
	void SetTextureRect(sf::IntRect rect);

private:
	/**
	  * @brief		Data for the evade/pursuit behaviours
	*/
	struct EvadePursuitData
	{
		sf::Vector2f agentPos;
		sf::Vector2f agentVelocity;
	};

	/**
	  * @brief		Data for the obstacles
	*/
	struct Obstacle
	{
		sf::Vector2f obstaclePos;
		float obstacleRadious;
	};

	sf::RectangleShape m_shape;
	

	/* Steering behaviours */
	// utility
	sf::Vector2f m_orientation = { 0, -1 };
	float m_force = 100;
	float m_maxForce = 100;
	float m_mass = 20.f;

	vector<eBEHAVIOUR> m_currentBehaviours;

	// Visuals
	sf::RectangleShape m_orientationVector;
	vector<sf::RectangleShape> m_forces;
	sf::RectangleShape m_finalForce;

	// fists
	vector<sf::Vector2f> m_seekTargets;
	vector<sf::Vector2f> m_fleeTargets;

	vector<EvadePursuitData> m_pursuitTargets;
	vector<EvadePursuitData> m_evadeTargets;


	// Wander
	float m_wanderCircleRadious = 200;
	float m_wanderCircleDistance = 250;
	int m_wanderTimerIndex = -1;
	float m_wanderAnglesChange = 120;

	// Follow path
	vector<sf::Vector2f> m_followPathPoints;
	ePATH_FOLLOWING_TYPE m_followPathType = ePATH_FOLLOWING_TYPE::NONE;
	unsigned int m_followPathIndex = 0;
	float m_followPathMinDistance = 20.0f;

	// Avoid obstacles
	vector<Obstacle> m_avoidObstacles;
	float m_maxSeeAhead = 200;
	float m_maxAvoidForce = 1000000;
	float m_extraRectangleWidth = 5;
	sf::CircleShape PA, PB, PC, PD, PP;

	// Flocking
	float m_flockignGroupRadious = 500;
	vector<Agent*> m_flockingGroup;
	float m_flockingForce = 1000;


	/* Capture the flag */

	// Varaibles
	bool m_isSeeingWall = false;

	std::string m_teamName;
	sf::Vector2f m_basePos;



	/* State machines */
	// Function
	friend class Agent_WinLoseState;

	Agent_StateMachine* m_stateMachine;
	eAGENT_STATE_TYPE m_functStateType = eAGENT_STATE_TYPE::NONE;


	// Animation
	friend class Agent_AnimState;
	friend class Agent_AnimHasFlagState;
	friend class Agent_AnimRunningState;
	friend class Agent_AnimRunningState;
	friend class Agent_AnimWinState;

	friend class Agent_PathFindingAnimState;

	Agent_AnimMachine* m_animMachine;
	eAGENT_ANIM_STATE_TYPE m_animStateType = eAGENT_ANIM_STATE_TYPE::NONE;

	float m_animTimer = 0.0f;
	unsigned int m_animFrame = 0;
};

