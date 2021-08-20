#include "PathFindingAgent.h"
#include "Globals.h"

PathFindingAgent::PathFindingAgent()
{
}

PathFindingAgent::~PathFindingAgent()
{
}

void PathFindingAgent::Init(sf::Vector2f pos, Agent_PathFindingStateMachine* stateMachine, Agent_PathFindingAnimMachine* animMachine)
{
	m_shape.setPosition(pos);
	m_shape.setSize({32, 32});

	m_stateMachine = stateMachine;
	m_animMachine = animMachine;
}

void PathFindingAgent::Update()
{
	sf::Vector2f forceSum = { 0, 0 };

	if (m_isFollowing)
	{
		forceSum += PathFollow();
		m_isFollowing = false;
	}

	forceSum = gl::MathF::normalizeVector(forceSum) * m_mass * gl::DeltaTime::Time();
	m_orientation += forceSum;
	m_orientation = gl::MathF::normalizeVector(m_orientation);

	float arriveMult = 1;
	if (m_followPathPoints.size() > 0)
	{
		arriveMult = Arrive(m_followPathPoints[m_followPathPoints.size() - 1], 20);
	}
	m_shape.setPosition(m_shape.getPosition() + m_orientation * m_force * gl::DeltaTime::Time() 
	                                                                    * arriveMult * m_canMove);

	m_stateMachine->Update(this);
	m_animMachine->Update(this);
}

void PathFindingAgent::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void PathFindingAgent::Destroy()
{
}

void PathFindingAgent::SetPosition(sf::Vector2f pos)
{
	m_shape.setPosition(pos);
}

sf::Vector2f PathFindingAgent::GetPosition()
{
	return m_shape.getPosition();
}

eAGENT_PATH_FINDING_STATE_TYPE PathFindingAgent::GetState()
{
	return m_state;
}

void PathFindingAgent::SetState(eAGENT_PATH_FINDING_STATE_TYPE state)
{
	m_state = state;
}

eAGENT_PATH_FINDING_ANIM_STATE_TYPE PathFindingAgent::GetAnimState()
{
	return m_animState;
}

void PathFindingAgent::SetAnimState(eAGENT_PATH_FINDING_ANIM_STATE_TYPE state)
{
	m_animState = state;
}


sf::Vector2f PathFindingAgent::Seek(sf::Vector2f target)
{
	sf::Vector2f desiredDirection = target - m_shape.getPosition();
	sf::Vector2f steering = gl::MathF::truncateVector(gl::MathF::normalizeVector(desiredDirection) 
	                                 + m_orientation, gl::MathF::vectorLength(desiredDirection));
	return steering;
}

float PathFindingAgent::Arrive(sf::Vector2f target, float radious)
{
	float distance = gl::MathF::vectorLength(target - m_shape.getPosition());
	float r = distance / radious;
	return r < 1 ? r : 1;
}

sf::Vector2f PathFindingAgent::PathFollow()
{
	size_t pathCount = m_followPathPoints.size();
	unsigned int regresion = (m_followPathIndex < pathCount ? 0 : 
	                         (m_followPathIndex - pathCount + 1) * 2);
	sf::Vector2f pathPoint = m_followPathPoints[m_followPathIndex - regresion];

	float distance = gl::MathF::vectorLength(m_shape.getPosition() - pathPoint);
	if (distance <= m_followPathMinDistance)
	{
		if (m_followPathIndex + 1 < pathCount)
		{
			m_followPathIndex++;
		}
	}

	regresion = (m_followPathIndex < pathCount ? 0 : (m_followPathIndex - pathCount + 1) * 2);
	return Seek(m_followPathPoints[m_followPathIndex - regresion]);
}

void PathFindingAgent::SetPathFollowPoints(std::vector<sf::Vector2f> points, bool restartCurrent)
{
	if (restartCurrent)
	{
		m_followPathIndex = 0;
	}
	else
	{
		m_followPathIndex = m_followPathIndex % points.size();
	}

	m_followPathPoints = points;
}

void PathFindingAgent::IsFollowing()
{
	m_isFollowing = true;
}

void PathFindingAgent::SetOrientation(sf::Vector2f orientation)
{
	m_orientation = gl::MathF::normalizeVector(orientation);
}

sf::Vector2f PathFindingAgent::GetOrientation()
{
	return m_orientation;
}

void PathFindingAgent::CanMove(bool can)
{
	m_canMove = can ? 1 : 0;
}
