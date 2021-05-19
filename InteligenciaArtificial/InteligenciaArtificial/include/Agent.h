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
	LEADER_FOLLOWING,
	QUEUE
};

class Agent
{
public:
	Agent() = default;
	Agent(float x, float y, sf::Color color);
	~Agent();

	void Init(float x, float y, sf::Color color);
	void Update();
	void Move(sf::Vector2f velocity);
	sf::Vector2f getPosition() { return m_shape.getPosition(); }
	sf::Vector2f getVelocity() { return m_orientation * m_force; }
	void Render(sf::RenderWindow* window);
	void Destroy();

	void AddSeekTarget(sf::Vector2f target);
	void AddFleeTarget(sf::Vector2f target);
	void AddWanderBehaviour();
	void AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity);
	void AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity);

private:
	sf::Vector2f Seek(sf::Vector2f target);
	sf::Vector2f Flee(sf::Vector2f target);
	float Arrive(sf::Vector2f target, float radious);

	sf::Vector2f Wander();
	sf::Vector2f Pursuit(sf::Vector2f target, sf::Vector2f velocity);
	sf::Vector2f Evade(sf::Vector2f target, sf::Vector2f velocity);

	float vectorLength(sf::Vector2f vec);
	sf::Vector2f normalizeVector(sf::Vector2f vec);
	sf::Vector2f truncateVector(sf::Vector2f vec, float length);

	void placeLineFromTwoPoints(sf::RectangleShape& line, sf::Vector2f pos1, sf::Vector2f pos2);

private:
	struct EvadePursuitData
	{
		sf::Vector2f agentPos;
		sf::Vector2f agentVelocity;
	};
	
	sf::RectangleShape m_shape;
	vector<eBEHAVIOUR> m_currentBehaviours;
	vector<sf::Vector2f> m_seekTargets;
	vector<sf::Vector2f> m_fleeTargets;
	vector<EvadePursuitData> m_pursuitTargets;
	vector<EvadePursuitData> m_evadeTargets;
	

	sf::Vector2f m_orientation = {0, -1};
	float m_force = 50;
	float m_mass = 10.f;

	sf::RectangleShape m_orientationVector;
	vector<sf::RectangleShape> m_forces;
	sf::RectangleShape m_finalForce;

	float m_wanderCircleRadious = 200;
	float m_wanderCircleDistance = 250;
	int m_wanderTimerIndex = -1;
	float m_wanderAnglesChange = 120;
};

