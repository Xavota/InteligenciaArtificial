#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Agent.h"
class AgentManager
{
public:
	AgentManager() = default;
	~AgentManager();

	void Init();
	void Restart();
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();

	void AddAgents(unsigned int agents, sf::IntRect aperanceRange, sf::Color color, std::string teamName);
	std::vector<Agent*> GetAgents(std::string teamName = "All");

	void AddSeekTarget(sf::Vector2f target, std::vector<Agent*> agents);
	void AddFleeTarget(sf::Vector2f target, std::vector<Agent*> agents);

	void AddWanderBehaviour(std::vector<Agent*> agents);
	void AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity, std::vector<Agent*> agents);
	void AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity, std::vector<Agent*> agents);

	void AddObstacleToAvoid(sf::Vector2f obstacle, float radious, std::vector<Agent*> agents);

	void AddFollowPathPoint(sf::Vector2f point, std::vector<Agent*> agents);
	void SetFollowPathMode(ePATH_FOLLOWING_TYPE type, std::vector<Agent*> agents);

	void AddFlockingBehaviour(std::vector<Agent*> agents);

	std::string GetTeamName(Agent* agent);

private:
	void SetFlockingBehaviours();

private:
	struct AgentStruct
	{
		Agent m_agent;
		std::string m_teamName;
		sf::Vector2f m_initPos;
	};

	struct TeamsInfo
	{
		std::string teamName;
		sf::IntRect aperanceRange;
		sf::Color color;
	};

	std::vector<AgentStruct> m_agents;
	std::vector<TeamsInfo> m_teams;
};

