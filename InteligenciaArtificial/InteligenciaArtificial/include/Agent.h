#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;

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

enum class ePATH_FOLLOWING_TYPE
{
	NONE = -1,
	FINITE,
	CYCLIC,
	RETURN,
	COUNT
};

class Agent
{
public:
	Agent() = default;
	Agent(int x, int y, sf::Color color, std::string teamName);
	~Agent();
	
	/**
	  * @brief      Initialice
	  * @param      x: the position in x coordinate
	  * @param      y: the position in y coordinate
	  * @param      color: the color of the agent
	  * @param      teamName: the team it is on
	  * @bug	    No know Bugs
	*/
	void Init(int x, int y, sf::Color color, std::string teamName);

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
	  * @bug	    No know Bugs
	*/
	void AddSeekTarget(sf::Vector2f target);

	/**
	  * @brief      Adds a target to the flee behaviour
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
	  * @bug	    No know Bugs
	*/
	void AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity);

	/**
	  * @brief      Adds a target to the evade behaviour
	  * @bug	    No know Bugs
	*/
	void AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity);


	/**
	  * @brief      Adds a target to the obstacle behaviour
	  * @bug	    No know Bugs
	*/
	void AddObstacleToAvoid(sf::Vector2f obstacle, float radious);


	/**
	  * @brief      Adds a target to the follow path behaviour
	  * @bug	    No know Bugs
	*/
	void AddFollowPathPoint(sf::Vector2f point);

	/**
	  * @brief      Sets the type of the follow path behaviour
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
	  * @bug	    No know Bugs
	*/
	bool HasBehaviour(eBEHAVIOUR behaviour);


	/**
	  * @brief      Gets the force for the seek behaviour to the given target
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Seek(sf::Vector2f target);

	/**
	  * @brief      Gets the force for the flee behaviour to the given target
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Flee(sf::Vector2f target);

	/**
	  * @brief      Gets the movement multiply value of the arrive behaviour
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
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Pursuit(sf::Vector2f target, sf::Vector2f velocity);

	/**
	  * @brief      Gets the force for the evade behaviour to the given target
	  * @bug	    No know Bugs
	*/
	sf::Vector2f Evade(sf::Vector2f target, sf::Vector2f velocity);


	/**
	  * @brief      Gets the force for the collition avoidance behaviour
	  * @bug	    No know Bugs
	*/
	sf::Vector2f AvoidObstacles();

	/**
	  * @brief      Returns true if is seeing the obstacle given
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

	static float vectorLength(sf::Vector2f vec);
	static sf::Vector2f normalizeVector(sf::Vector2f vec);
	static sf::Vector2f truncateVector(sf::Vector2f vec, float length);
	static float distanceVector(sf::Vector2f vec1, sf::Vector2f vec2);
	static float dot(sf::Vector2f vec1, sf::Vector2f vec2);
	static sf::Vector2f rightVector(sf::Vector2f vec);

	void placeLineFromTwoPoints(sf::RectangleShape& line, sf::Vector2f pos1, sf::Vector2f pos2);

private:
	struct EvadePursuitData
	{
		sf::Vector2f agentPos;
		sf::Vector2f agentVelocity;
	};

	struct Obstacle
	{
		sf::Vector2f obstaclePos;
		float obstacleRadious;
	};
	
	sf::RectangleShape m_shape;
	vector<eBEHAVIOUR> m_currentBehaviours;
	vector<sf::Vector2f> m_seekTargets;
	vector<sf::Vector2f> m_fleeTargets;
	vector<EvadePursuitData> m_pursuitTargets;
	vector<EvadePursuitData> m_evadeTargets;
	vector<Obstacle> m_avoidObstacles;
	

	sf::Vector2f m_orientation = {0, -1};
	float m_force = 100;
	float m_mass = 20.f;

	sf::RectangleShape m_orientationVector;
	vector<sf::RectangleShape> m_forces;
	sf::RectangleShape m_finalForce;

	float m_wanderCircleRadious = 200;
	float m_wanderCircleDistance = 250;
	int m_wanderTimerIndex = -1;
	float m_wanderAnglesChange = 120;

	vector<sf::Vector2f> m_followPathPoints;
	ePATH_FOLLOWING_TYPE m_followPathType = ePATH_FOLLOWING_TYPE::NONE;
	unsigned int m_followPathIndex = 0;
	float m_followPathMinDistance = 20.0f;

	float m_maxSeeAhead = 200;
	float m_maxAvoidForce = 1000000;
	float m_extraRectangleWidth = 5;
	sf::CircleShape PA, PB, PC, PD, PP;

	float m_flockignGroupRadious = 500;
	vector<Agent*> m_flockingGroup;
	float m_flockingForce = 1000;

	std::string m_teamName;

	bool m_isSeeingWall = false;
};

