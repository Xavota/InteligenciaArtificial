#include "Agent.h"
#include "Globals.h"

Agent::Agent(int x, int y, sf::Color color, std::string teamName, sf::Vector2f basePos, Agent_StateMachine* stMachine, Agent_AnimMachine* animMachine)
{
	Init(x, y, color, teamName, basePos, stMachine, animMachine);
}

void Agent::Init(int x, int y, sf::Color color, std::string teamName, sf::Vector2f basePos, Agent_StateMachine* stMachine, Agent_AnimMachine* animMachine)
{
	m_teamName = teamName;

	m_shape.setPosition(x, y);
	m_shape.setSize({49, 68});
	m_shape.setFillColor(color);
	m_shape.setOrigin({m_shape.getSize().x / 2, m_shape.getSize().y / 2 });
	//m_shape.setTexture(gl::CTexture::GetTexture("Agent"));
	
	float angle = rand() % 360;
	m_orientation = normalizeVector(sf::Vector2f(cos(angle * 3.1415 / 180), sin(angle * 3.1415 / 180)));

	m_orientationVector.setFillColor(sf::Color::Green);
	m_orientationVector.setOrigin({ 1.5,0 });
	m_finalForce.setFillColor(sf::Color::Magenta);
	m_finalForce.setOrigin({ 1.5,0 });

	PP = sf::CircleShape(5);
	PP.setOrigin({5,5});
	PA = sf::CircleShape(3);
	PA.setOrigin({ 3,3 });
	PA.setFillColor(sf::Color::Blue);
	PB = sf::CircleShape(2);
	PB.setOrigin({ 2,2 });
	PC = sf::CircleShape(2);
	PC.setOrigin({ 2,2 });
	PD = sf::CircleShape(2);
	PD.setOrigin({ 2,2 });

	m_basePos = basePos;

	m_stateMachine = stMachine;
	m_animMachine = animMachine;
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
		case eBEHAVIOUR::PATH_FOLLOWING:
			forceSum += PathFollow();
			break;
		case eBEHAVIOUR::COLLITION_AVOIDANCE:
			forceSum += AvoidObstacles();
			m_avoidObstacles.clear();
			break;
		case eBEHAVIOUR::FLOCKING:
			forceSum += Flocking();
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

	m_stateMachine->Update(this);
	m_animMachine->Update(this);
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
		//window->draw(s);
	}
	//window->draw(m_finalForce);
	//window->draw(PP);
	//window->draw(PA);
	//window->draw(PB);
	//window->draw(PC);
	//window->draw(PD);
}

void Agent::Destroy()
{
}

void Agent::AddSeekTarget(sf::Vector2f target)
{
	m_seekTargets.push_back(target);
	if (!HasBehaviour(eBEHAVIOUR::SEEK)) 
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::SEEK);
	}
}

void Agent::AddFleeTarget(sf::Vector2f target)
{
	m_fleeTargets.push_back(target);
	if (!HasBehaviour(eBEHAVIOUR::FLEE))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::FLEE);
	}
}

void Agent::AddWanderBehaviour()
{
	if (!HasBehaviour(eBEHAVIOUR::WANDER))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::WANDER);
	}
}

void Agent::AddPursuitTarget(sf::Vector2f target, sf::Vector2f velocity)
{
	m_pursuitTargets.push_back(EvadePursuitData{ target, velocity });
	if (!HasBehaviour(eBEHAVIOUR::PURSUIT))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::PURSUIT);
	}
}

void Agent::AddEvadeTarget(sf::Vector2f target, sf::Vector2f velocity)
{
	m_evadeTargets.push_back(EvadePursuitData{ target, velocity });
	if (!HasBehaviour(eBEHAVIOUR::EVADE))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::EVADE);
	}
}

void Agent::AddObstacleToAvoid(sf::Vector2f obstacle, float radious)
{
	m_avoidObstacles.push_back(Obstacle{ obstacle, radious });
	if (!HasBehaviour(eBEHAVIOUR::COLLITION_AVOIDANCE))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::COLLITION_AVOIDANCE);
	}
}

void Agent::AddFollowPathPoint(sf::Vector2f point)
{
	m_followPathPoints.push_back(point);
}

void Agent::SetFollowPathMode(ePATH_FOLLOWING_TYPE type)
{
	m_followPathType = type;
	if (!HasBehaviour(eBEHAVIOUR::PATH_FOLLOWING))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::PATH_FOLLOWING);
	}
}

void Agent::AddFlockingBehaviour()
{
	if (!HasBehaviour(eBEHAVIOUR::FLOCKING))
	{
		m_currentBehaviours.push_back(eBEHAVIOUR::FLOCKING);
	}
}

void Agent::SetFlockingAgentsGroup(vector<Agent*> agents)
{
	m_flockingGroup = agents;
}

bool Agent::IsFlocking()
{
	return HasBehaviour(eBEHAVIOUR::FLOCKING);
}

float Agent::GetFlockingGroupRadious()
{
	return m_flockignGroupRadious;
}

bool Agent::HasBehaviour(eBEHAVIOUR behaviour)
{
	for (eBEHAVIOUR b : m_currentBehaviours)
	{
		if (b == behaviour)
			return true;
	}
	return false;
}

sf::Vector2f Agent::Seek(sf::Vector2f target)
{
	sf::Vector2f desiredDirection = target - m_shape.getPosition();
	sf::Vector2f steering = truncateVector(normalizeVector(desiredDirection) + m_orientation, vectorLength(desiredDirection));
	/*m_forces.push_back(sf::RectangleShape());
	placeLineFromTwoPoints(m_forces[m_forces.size()-1], m_shape.getPosition(), m_shape.getPosition() + steering);
	m_forces[m_forces.size() - 1].setFillColor(sf::Color(255, 255, 125));/**/
	return steering;
}

sf::Vector2f Agent::Flee(sf::Vector2f target)
{
	sf::Vector2f desiredDirection = m_shape.getPosition() - target;
	sf::Vector2f steering = truncateVector(normalizeVector(desiredDirection) + m_orientation, 50000 / vectorLength(desiredDirection));
	/*m_forces.push_back(sf::RectangleShape());
	placeLineFromTwoPoints(m_forces[m_forces.size() - 1], m_shape.getPosition(), m_shape.getPosition() + steering);
	m_forces[m_forces.size() - 1].setFillColor(sf::Color(255, 255, 255));/**/
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

sf::Vector2f Agent::AvoidObstacles()
{
	Obstacle mostThreateningObstacle = Obstacle{{0,0}, 0};
	sf::Vector2f ortoVec;

	for (Obstacle& o : m_avoidObstacles)
	{
		sf::Vector2f oV;
		bool intersect = IsSeeingObstacle(o.obstaclePos, o.obstacleRadious, oV);

		if (intersect &&
		   (mostThreateningObstacle.obstacleRadious == 0 ||
		   distanceVector(m_shape.getPosition(), o.obstaclePos) < 
		   distanceVector(m_shape.getPosition(), mostThreateningObstacle.obstaclePos)))
		{
			mostThreateningObstacle = o;
			ortoVec = oV;
		}
	}

	if (mostThreateningObstacle.obstacleRadious != 0)
	{
		return truncateVector(ortoVec, m_maxAvoidForce / ((distanceVector(m_shape.getPosition(), mostThreateningObstacle.obstaclePos) - mostThreateningObstacle.obstacleRadious)));
	}

	return sf::Vector2f();
}

bool Agent::IsSeeingObstacle(sf::Vector2f obsPos, float obsRad, sf::Vector2f& out_ortoVec)
{
	sf::Vector2f E = obsPos;

	sf::Vector2f rightVec = rightVector(m_orientation);
	sf::Vector2f A = m_shape.getPosition() + rightVec * (m_shape.getSize().x / 2 + m_extraRectangleWidth) - m_orientation * (m_shape.getSize().y / 2);
	sf::Vector2f B = A + m_orientation * m_maxSeeAhead;
	sf::Vector2f C = B + -rightVec * (m_shape.getSize().x + 2 * m_extraRectangleWidth);
	sf::Vector2f D = A + -rightVec * (m_shape.getSize().x + 2 * m_extraRectangleWidth);
	PP.setPosition(m_shape.getPosition());
	PA.setPosition(A);
	PB.setPosition(B);
	PC.setPosition(C);
	PD.setPosition(D);

	if (distanceVector(A, E) < obsRad)
	{
		out_ortoVec = E - A;
		return true;
	}
	else if (distanceVector(B, E) < obsRad)
	{
		out_ortoVec = E - B;
		return true;
	}
	else if (distanceVector(C, E) < obsRad)
	{
		out_ortoVec = E - C;
		return true;
	}
	else if (distanceVector(D, E) < obsRad)
	{
		out_ortoVec = E - D;
		return true;
	}
	else
	{	
		sf::Vector2f AB = B - A;
		sf::Vector2f AE = E - A;
		float lenghtAF = dot(AB, AE) / vectorLength(AB);
		if (lenghtAF > 0 && lenghtAF <= m_maxSeeAhead)
		{
			sf::Vector2f AF = normalizeVector(AB) * lenghtAF;
			sf::Vector2f F = A + AF;
			if (distanceVector(F, E) < obsRad)
			{
				out_ortoVec = F - E;
				return true;
			}			
		}


		sf::Vector2f CD = D - C;
		sf::Vector2f CE = E - C;
		float lenghtCH = dot(CD, CE) / vectorLength(CD);
		if (lenghtCH > 0 && lenghtCH <= m_maxSeeAhead)
		{
			sf::Vector2f CH = normalizeVector(CD) * lenghtCH;
			sf::Vector2f H = C + CH;
			if (distanceVector(H, E) < obsRad)
			{
				out_ortoVec = H - E;
				return true;
			}
		}


		sf::Vector2f BC = C - B;
		sf::Vector2f BE = E - B;
		float lenghtBG = dot(BC, BE) / vectorLength(BC);
		if (lenghtBG > 0 && lenghtBG <= m_shape.getSize().x + m_extraRectangleWidth)
		{
			sf::Vector2f BG = normalizeVector(BC) * lenghtBG;
			sf::Vector2f G = B + BG;
			if (distanceVector(G, E) < obsRad)
			{
				out_ortoVec = G - E;
				return true;
			}
		}


		sf::Vector2f DA = A - D;
		sf::Vector2f DE = E - D;
		float lenghtDI = dot(DA, DE) / vectorLength(DA);
		if (lenghtDI > 0 && lenghtDI <= m_shape.getSize().x + m_extraRectangleWidth)
		{
			sf::Vector2f DI = normalizeVector(DA) * lenghtDI;
			sf::Vector2f I = D + DI;
			if (distanceVector(I, E) < obsRad)
			{
				out_ortoVec = I - E;
				return true;
			}
		}
	}
	return false;
}

sf::Vector2f Agent::PathFollow()
{
	size_t pathCount = m_followPathPoints.size();
	unsigned int regresion = (m_followPathIndex < pathCount ? 0 : (m_followPathIndex - pathCount + 1) * 2);
	sf::Vector2f pathPoint = m_followPathPoints[m_followPathIndex - regresion];
	if (vectorLength(m_shape.getPosition() - pathPoint) <= m_followPathMinDistance)
	{
		switch (m_followPathType)
		{
		case ePATH_FOLLOWING_TYPE::FINITE:
			if (m_followPathIndex + 1 < pathCount)
			{
				m_followPathIndex++;
			}
			break;
		case ePATH_FOLLOWING_TYPE::CYCLIC:
			m_followPathIndex = (m_followPathIndex + 1) % pathCount;
			break;
		case ePATH_FOLLOWING_TYPE::RETURN:
			m_followPathIndex = (m_followPathIndex + 1) % ((pathCount - 1) * 2);
			break;
		}
	}
	regresion = (m_followPathIndex < pathCount ? 0 : (m_followPathIndex - pathCount + 1) * 2);
	return Seek(m_followPathPoints[m_followPathIndex - regresion]);

	//TODO: Agregar que la normal afecte a la fuerza
}

sf::Vector2f Agent::Flocking()
{
	if (m_flockingGroup.size() > 1)
	{
		sf::Vector2f flock = normalizeVector(Separation() + Cohesion() + Alignment()) * m_flockingForce;
		m_flockingGroup.clear();
		return flock;
	}
	else
	{
		return sf::Vector2f();
	}
}

sf::Vector2f Agent::Separation()
{
	sf::Vector2f fleeForce;
	for (Agent* a : m_flockingGroup)
	{
		if (a != this)
			fleeForce += Flee(a->getPosition());
	}
	fleeForce = sf::Vector2f{ fleeForce.x / m_flockingGroup.size(), fleeForce.y / m_flockingGroup.size() };
	//fleeForce = normalizeVector(fleeForce);
	return fleeForce;
}

sf::Vector2f Agent::Cohesion()
{
	sf::Vector2f fleeForce;
	for (Agent* a : m_flockingGroup)
	{
		fleeForce += a->getPosition();
	}
	fleeForce = sf::Vector2f{ fleeForce.x / m_flockingGroup.size(), fleeForce.y / m_flockingGroup.size() };
	fleeForce = Seek(fleeForce);
	//fleeForce = normalizeVector(fleeForce);
	return fleeForce;
}

sf::Vector2f Agent::Alignment()
{
	sf::Vector2f fleeForce;
	for (Agent* a : m_flockingGroup)
	{
		fleeForce += a->m_orientation * a->m_force;
	}
	fleeForce = sf::Vector2f{ fleeForce.x / m_flockingGroup.size(), fleeForce.y / m_flockingGroup.size() };
	//fleeForce = normalizeVector(fleeForce);
	return fleeForce;
}

float Agent::vectorLength(sf::Vector2f vec)
{
	return pow(vec.x * vec.x + vec.y * vec.y, .5f);
}

sf::Vector2f Agent::normalizeVector(sf::Vector2f vec)
{
	float len = vectorLength(vec);
	if (len == 0)
	{
		return sf::Vector2f(0,0);
	}
	return vec / len;
}

sf::Vector2f Agent::truncateVector(sf::Vector2f vec, float length)
{
	return normalizeVector(vec) * length;
}

float Agent::distanceVector(sf::Vector2f vec1, sf::Vector2f vec2)
{
	return vectorLength(vec2 - vec1);
}

float Agent::dot(sf::Vector2f vec1, sf::Vector2f vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

sf::Vector2f Agent::rightVector(sf::Vector2f vec)
{
	return sf::Vector2f(-vec.y, vec.x);
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

eAGENT_STATE_TYPE Agent::GetState()
{
	return m_functStateType;
}

void Agent::SetState(eAGENT_STATE_TYPE state)
{
	m_functStateType = state;
}

sf::Vector2f Agent::GetBasePos()
{
	return m_basePos;
}

void Agent::UpdateBasePos(sf::Vector2f pos)
{
	m_basePos = pos;
}

sf::Color Agent::GetColor()
{
	return m_shape.getFillColor();
}

void Agent::UpdateColor(sf::Color color)
{
	m_shape.setFillColor(color);
}

eAGENT_ANIM_STATE_TYPE Agent::GetAnimState()
{
	return m_animStateType;
}

void Agent::SetAnimState(eAGENT_ANIM_STATE_TYPE state)
{
	m_animStateType = state;
}

void Agent::SetTexture(sf::Texture* tex)
{
	m_shape.setTexture(tex);
}

void Agent::SetTextureRect(sf::IntRect rect)
{
	m_shape.setTextureRect(rect);
}
