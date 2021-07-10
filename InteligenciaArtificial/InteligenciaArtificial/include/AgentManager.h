#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Agent.h"

#include "Agent_StateMachine.h"

class AgentManager
{
public:
	AgentManager() = default;
	~AgentManager();

	/**
	  * @brief      Initialice
	  * @param      stMachine: the state machine that will be controlling the agents
	  * @param      animMachine: the animation machine the will be controlling the agents textures
	  * @bug	    No know Bugs
	*/
	void Init(Agent_StateMachine* stMachine, Agent_AnimMachine* animMachine);
	/**
	  * @brief      Replace all the agents and return them to FOLLOW_FLAG state
	  * @bug	    No know Bugs
	*/
	void Restart();
	/**
	  * @brief      Updates all the agents
	  * @bug	    No know Bugs
	*/
	void Update();
	/**
	  * @brief      Renders all the agents
	  * @param      window: the window to wich the agents will be rendered
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Initialice
	  * @bug	    No know Bugs
	*/
	void Destroy();

	/**
	  * @brief      Adds a number of agents of a certain team
	  * @param      agents: how many agents to add
	  * @param      aperanceRange: the rectangle where the agents can appear
	  * @param      color: the color of the agents
	  * @param      teamName: the team they are on
	  * @param      basePos: the point they has to take the flag
	  * @bug	    No know Bugs
	*/
	void AddAgents(unsigned int agents, sf::IntRect aperanceRange, sf::Color color, std::string teamName, sf::Vector2f basePos);
	/**
	  * @brief      Delete some agents of a team
	  * @param      agents: how many agents will be removed
	  * @param      teamName: the name of the team that will lose agents
	  * @bug	    No know Bugs
	*/
	void RemoveAgents(unsigned int agents, std::string teamName);
	/**
	  * @brief      Delete an agent of a certein index
	  * @param      agentIndex: the index of the removed agent
	  * @bug	    No know Bugs
	*/
	void RemoveAgent(unsigned int agentIndex);
	/**
	  * @brief      Returns a list of agents of a certain team or all the agents
	  * @param      teamName: the team that the agents come from (blank or "All" for all the agents)
	  * @bug	    No know Bugs
	*/
	std::vector<Agent*> GetAgents(std::string teamName = "All");

	/**
	  * @brief      Updates the range apperance of the team
	  * @param      teamName: the team to modify
	  * @param      range: the new range
	  * @bug	    No know Bugs
	*/
	void UpdateTeamAperianceRange(std::string teamName, sf::IntRect range);
	/**
	  * @brief      Updates the base position of the team
	  * @param      teamName: the team to modify
	  * @param      pos: the new position
	  * @bug	    No know Bugs
	*/
	void UpdateTeamBasePos(std::string teamName, sf::Vector2f pos);
	/**
	  * @brief      Updates the color of the team
	  * @param      teamName: the team to modify
	  * @param      color: the new color
	  * @bug	    No know Bugs
	*/
	void UpdateTeamColor(std::string teamName, sf::Color color);
	



	/**
	  * @brief		Adds a seek target to the agents given
	  * @param      target: the target added
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddSeekTarget(sf::Vector2f target, std::vector<Agent*> agents);
	/**
	  * @brief		Adds a flee target to the agents given
	  * @param      target: the target added
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddFleeTarget(sf::Vector2f target, std::vector<Agent*> agents);

	/**
	  * @brief		Adds the wander behaviour to the agents given
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddWanderBehaviour(std::vector<Agent*> agents);
	/**
	  * @brief		Adds a pursuit target to the agents given
	  * @param      target: the target added
	  * @param      velocity: the velocity of the target
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity, std::vector<Agent*> agents);
	/**
	  * @brief		Adds a evade target to the agents given
	  * @param      target: the target added
	  * @param      velocity: the velocity of the target
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity, std::vector<Agent*> agents);

	/**
	  * @brief		Adds an obstacle to avoid to the agents given
	  * @param      obstacle: the obstacle added
	  * @param      radious: the radious of the obstacle
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/	
	void AddObstacleToAvoid(sf::Vector2f obstacle, float radious, std::vector<Agent*> agents);

	/**
	  * @brief		Adds a point to the path to follow to the agents given
	  * @param      point: the position of the point added
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddFollowPathPoint(sf::Vector2f point, std::vector<Agent*> agents);
	/**
	  * @brief		Sets the type of follow path
	  * @param      type: the type of the follow path
	  * @param      agents: the agents that will be set to
	  * @bug	    No know Bugs
	*/
	void SetFollowPathMode(ePATH_FOLLOWING_TYPE type, std::vector<Agent*> agents);

	/**
	  * @brief		Adds the flocking behaviour to the agents given
	  * @param      agents: the agents that will be added to
	  * @bug	    No know Bugs
	*/
	void AddFlockingBehaviour(std::vector<Agent*> agents);

private:
	/**
	  * @brief		Sets the flocking behaviours to the agents thats has the property
	  * @bug	    No know Bugs
	*/
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
		std::string m_teamName;
		sf::Vector2f m_basePos;	
		sf::IntRect m_aperanceRange;
		sf::Color m_color;
	};

	std::list<AgentStruct> m_agents;
	std::vector<TeamsInfo> m_teams;


	Agent_StateMachine* m_stateMachine;
	Agent_AnimMachine* m_animMachine;
};

