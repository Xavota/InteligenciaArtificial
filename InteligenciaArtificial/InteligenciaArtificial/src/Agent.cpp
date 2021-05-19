#include "Agent.h"
#include "Globals.h"

Agent::Agent(float x, float y, sf::Color color)
{
	Init(x, y, color);
}

void Agent::Init(float x, float y, sf::Color color)
{
	m_shape.setPosition(x, y);
	m_shape.setSize({10, 10});
	m_shape.setFillColor(color);
	m_shape.setOrigin({m_shape.getSize().x / 2, m_shape.getSize().y / 2 });


	m_orientationVector.setFillColor(sf::Color::Green);
	m_orientationVector.setOrigin({ 1.5,0 });
	m_finalForce.setFillColor(sf::Color::Magenta);
	m_finalForce.setOrigin({ 1.5,0 });
}

Agent::~Agent()
{
}

void Agent::Update()
{
	m_forces.clear();
	sf::Vector2f forceSum = {0,-1};

	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		switch(b)
		{
		case eBEHAVIOUR::SEEK:
			for (sf::Vector2f& s : m_seekTargets)
			{
				forceSum += Seek(s);
			}
			break;
		case eBEHAVIOUR::FLEE:
			for (sf::Vector2f& f : m_fleeTargets)
			{
				forceSum += Flee(f);
			}
			m_fleeTargets.clear();
			break;
		case eBEHAVIOUR::WANDER:
			forceSum += Wander();
			break;
		case eBEHAVIOUR::PURSUIT:
			for (EvadePursuitData& f : m_pursuitTargets)
			{
				forceSum += Pursuit(f.agentPos, f.agentVelocity);
			}
			m_pursuitTargets.clear();
			break;
		case eBEHAVIOUR::EVADE:
			for (EvadePursuitData& f : m_evadeTargets)
			{
				forceSum += Evade(f.agentPos, f.agentVelocity);
			}
			m_evadeTargets.clear();
			break;
		}
	}
	m_currentBehaviours.clear();

	placeLineFromTwoPoints(m_finalForce, m_shape.getPosition(), m_shape.getPosition() + forceSum);

	forceSum = normalizeVector(forceSum) * m_mass * gl::DeltaTime::Time();
	m_orientation += forceSum;
	m_orientation = normalizeVector(m_orientation);

	float arriveMult = 1;
	for (sf::Vector2f& s : m_seekTargets)
	{
		arriveMult *= Arrive(s, 25);
	}
	m_seekTargets.clear();

	Move(m_orientation * m_force * gl::DeltaTime::Time() * arriveMult);

	sf::Vector2f directionMark = m_shape.getPosition() + sf::Vector2f{m_orientation.x * 50, m_orientation.y * 50};
	placeLineFromTwoPoints(m_orientationVector, m_shape.getPosition(), directionMark);

	//directionMark = m_shape.getPosition() + truncateVector(forceSum, 50);
	//placeLineFromTwoPoints(m_finalForce, m_shape.getPosition(), directionMark);
}

void Agent::Move(sf::Vector2f velocity)
{
	m_shape.setPosition(m_shape.getPosition() + velocity);
}

void Agent::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
	//window->draw(m_orientationVector);
	for (sf::RectangleShape& s : m_forces)
	{
	//	window->draw(s);
	}
	//window->draw(m_finalForce);
}

void Agent::Destroy()
{
}

void Agent::AddSeekTarget(sf::Vector2f target)
{
	m_seekTargets.push_back(target);
	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		if (b == eBEHAVIOUR::SEEK)
			break;
	}
	m_currentBehaviours.push_back(eBEHAVIOUR::SEEK);
}

void Agent::AddFleeTarget(sf::Vector2f target)
{
	m_fleeTargets.push_back(target);
	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		if (b == eBEHAVIOUR::FLEE)
			break;
	}
	m_currentBehaviours.push_back(eBEHAVIOUR::FLEE);
}

void Agent::AddWanderBehaviour()
{
	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		if (b == eBEHAVIOUR::WANDER)
			break;
	}
	m_currentBehaviours.push_back(eBEHAVIOUR::WANDER);
}

void Agent::AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity)
{
	m_pursuitTargets.push_back(EvadePursuitData{target, velocity});
	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		if (b == eBEHAVIOUR::PURSUIT)
			break;
	}
	m_currentBehaviours.push_back(eBEHAVIOUR::PURSUIT);
}

void Agent::AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity)
{
	m_evadeTargets.push_back(EvadePursuitData{ target, velocity });
	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		if (b == eBEHAVIOUR::EVADE)
			break;
	}
	m_currentBehaviours.push_back(eBEHAVIOUR::EVADE);
}

sf::Vector2f Agent::Seek(sf::Vector2f target)
{
	sf::Vector2f desiredDirection = target - m_shape.getPosition();
	sf::Vector2f steering = truncateVector(normalizeVector(desiredDirection) + m_orientation, vectorLength(desiredDirection));
	m_forces.push_back(sf::RectangleShape());
	placeLineFromTwoPoints(m_forces[m_forces.size()-1], m_shape.getPosition(), m_shape.getPosition() + steering);
	m_forces[m_forces.size() - 1].setFillColor(sf::Color(255, 255, 125));
	return steering;
}

sf::Vector2f Agent::Flee(sf::Vector2f target)
{
	sf::Vector2f desiredDirection = m_shape.getPosition() - target;
	sf::Vector2f steering = truncateVector(normalizeVector(desiredDirection) + m_orientation, 50000 / vectorLength(desiredDirection));
	m_forces.push_back(sf::RectangleShape());
	placeLineFromTwoPoints(m_forces[m_forces.size() - 1], m_shape.getPosition(), m_shape.getPosition() + steering);
	m_forces[m_forces.size() - 1].setFillColor(sf::Color(255, 255, 255));
	return steering;
}

float Agent::Arrive(sf::Vector2f target, float radious)
{
	float distance = vectorLength(target - m_shape.getPosition());
	float r = distance / radious;
	return r < 1 ? r : 1;
}

sf::Vector2f Agent::Wander()
{
	static sf::Vector2f newWander;
	static float wanderAngle = 0;
	if (m_wanderTimerIndex == -1)
	{
		while (true)
		{
			m_wanderTimerIndex++;
			if (!gl::DeltaTime::TimerExist("WanderTimer" + to_string(m_wanderTimerIndex)))
			{
				gl::DeltaTime::AddTimer("WanderTimer" + to_string(m_wanderTimerIndex));
				break;
			}
		}
		wanderAngle += ((rand() % 100) / 100.f) * m_wanderAnglesChange - m_wanderAnglesChange * .5;
		sf::Vector2f circleCenter = m_shape.getPosition() + m_orientation * m_wanderCircleDistance;
		sf::Vector2f wanderDirection = sf::Vector2f{ cos(wanderAngle * 3.141592f / 180.f), sin(wanderAngle * 3.141592f / 180.f) };
		newWander = circleCenter + normalizeVector(wanderDirection) * m_wanderCircleDistance;
	}
	else
	{
		if (gl::DeltaTime::GetTimer("WanderTimer" + to_string(m_wanderTimerIndex)) > 1.0f || vectorLength(m_shape.getPosition() - newWander) < 5.f)
		{
			wanderAngle += ((rand() % 100) / 100.f) * m_wanderAnglesChange - m_wanderAnglesChange * .5;
			sf::Vector2f circleCenter = m_shape.getPosition() + m_orientation * m_wanderCircleDistance;
			sf::Vector2f wanderDirection = sf::Vector2f{ cos(wanderAngle * 3.141592f / 180), sin(wanderAngle * 3.141592f / 180) };
			newWander = circleCenter + normalizeVector(wanderDirection) * m_wanderCircleDistance;

			gl::DeltaTime::RestartTimer("WanderTimer" + to_string(m_wanderTimerIndex));
		}
	}
	
	return Seek(newWander);
}

sf::Vector2f Agent::Pursuit(sf::Vector2f target, sf::Vector2f velocity)
{
	float T = vectorLength(m_shape.getPosition() - target) / m_force;

	return Seek(target + velocity * T);
}

sf::Vector2f Agent::Evade(sf::Vector2f target, sf::Vector2f velocity)
{
	float T = vectorLength(m_shape.getPosition() - target) / m_force;

	return Flee(target + velocity * T);
}

float Agent::vectorLength(sf::Vector2f vec)
{
	return pow(vec.x * vec.x + vec.y * vec.y, .5f);
}

sf::Vector2f Agent::normalizeVector(sf::Vector2f vec)
{
	return vec / vectorLength(vec);
}

sf::Vector2f Agent::truncateVector(sf::Vector2f vec, float length)
{
	return normalizeVector(vec) * length;
}

void Agent::placeLineFromTwoPoints(sf::RectangleShape& line, sf::Vector2f pos1, sf::Vector2f pos2)
{
	line.setPosition(pos1);
	sf::Vector2f ori = pos2 - pos1;
	line.setSize({3.f, vectorLength(ori)});
	float angle = atan((ori.y) / (ori.x)) * 180 / 3.14159265;
	if (ori.x < 0)
	{
		angle += 180;
	}
	else if (ori.y < 0)
	{
		angle += 360;
	}

	line.setRotation(angle - 90);/**/
}
