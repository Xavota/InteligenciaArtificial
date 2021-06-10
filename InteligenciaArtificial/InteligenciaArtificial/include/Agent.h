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

	void Init(int x, int y, sf::Color color, std::string teamName);
	void Update();
	void Move(sf::Vector2f velocity);
	sf::Vector2f getPosition() { return m_shape.getPosition(); }
	void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }
	sf::Vector2f getVelocity() { return m_orientation * m_force; }
	sf::Vector2f getOrientation() { return m_orientation; }
	void Render(sf::RenderWindow* window);
	void Destroy();

	void AddSeekTarget(sf::Vector2f target);
	void AddFleeTarget(sf::Vector2f target);

	void AddWanderBehaviour();
	void AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity);
	void AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity);

	void AddObstacleToAvoid(sf::Vector2f obstacle, float radious);

	void AddFollowPathPoint(sf::Vector2f point);
	void SetFollowPathMode(ePATH_FOLLOWING_TYPE type);

	void AddFlockingBehaviour();
	void SetFlockingAgentsGroup(vector<Agent*> agents);
	bool IsFlocking();
	float GetFlockingGroupRadious();

	std::string GetTeam() { return m_teamName; }

	void SetIsSeeingWall(bool wall) { m_isSeeingWall = wall; }
	bool GetIsSeeingWall() { return m_isSeeingWall; }

private:
	bool HasBehaviour(eBEHAVIOUR behaviour);

	sf::Vector2f Seek(sf::Vector2f target);
	sf::Vector2f Flee(sf::Vector2f target);
	float Arrive(sf::Vector2f target, float radious);

	sf::Vector2f Wander();
	sf::Vector2f Pursuit(sf::Vector2f target, sf::Vector2f velocity);
	sf::Vector2f Evade(sf::Vector2f target, sf::Vector2f velocity);

	sf::Vector2f AvoidObstacles();
	bool IsSeeingObstacle(sf::Vector2f obsPos, float obsRad, sf::Vector2f& out_ortoVec);

	sf::Vector2f PathFollow();

	sf::Vector2f Flocking();
	sf::Vector2f Separation();
	sf::Vector2f Cohesion();
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

