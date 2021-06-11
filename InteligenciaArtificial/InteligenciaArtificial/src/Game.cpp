#include "Game.h"
#include "Globals.h"

void Game::run()
{
	init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			gl::DeltaTime::Update(timePerFrame.asSeconds());
			update();
			gl::Input::Update();
		}
		render();
	}

	destroy();
}

void Game::init()
{
	m_window = getGameWindow(1920, 1080);
	gl::CTexture::AddTexture("Flag", "Flag.png");
	gl::CTexture::AddTexture("Agent", "corredor.png");
	gl::CTexture::AddTexture("Stage", "stage.png");

	m_stage.setSize({1920, 1080});
	m_stage.setTexture(gl::CTexture::GetTexture("Stage"));

	m_manager.AddAgents(50, sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(955, 1070)), sf::Color::Blue, "left");
	m_manager.AddAgents(50, sf::IntRect(sf::Vector2i(955, 0), sf::Vector2i(955, 1070)), sf::Color::Red, "right");

	m_flag.Init({ 960, 540 });
	gl::CFont::AddFont("Points", "Caramel Sweets.ttf");
	m_pointsText.setFont(*gl::CFont::GetFont("Points"));
	m_pointsText.setCharacterSize(75);

	m_pointsText.setPosition({ 960, 10 });
	m_pointsText.setString("0 | 0");

	m_pointsText.setOrigin({ m_pointsText.getGlobalBounds().width / 2, 0});


}

void Game::update()
{
	static bool first = true;
	if (first)
	{
		gl::DeltaTime::AddTimer("CatchFlag");
		gl::DeltaTime::SetTimer("CatchFlag", 1.0f);
		first = false;
	}

	if (!m_Finished)
	{
		int TimerCounter = 0;
		for (Agent* a : m_manager.GetAgents())
		{
			sf::Vector2f position = a->getPosition();

			sf::Vector2f limit;

			sf::Vector2f orientation = a->getOrientation();
			if (orientation.x > 0)
			{	
				float X = 1920;
				float Ax = position.x;
				float Ay = position.y;
				float ax = orientation.x;
				float ay = orientation.y;
				float lenb = abs(X - Ax);

				float distFact = lenb / abs(ax);

				float Y = Ay + ay * distFact;

				if (Y >= 0 && Y <= 1080)
				{
					limit = sf::Vector2f(X, Y);
					float distanceToWall = Agent::distanceVector(position, limit);
					//m_manager.AddFleeTarget(limit, { a });

					if (!gl::DeltaTime::TimerExist("WallAvoid" + to_string(TimerCounter)))
					{
						gl::DeltaTime::AddTimer("WallAvoid" + to_string(TimerCounter));
					}
					
					if (gl::DeltaTime::GetTimer("WallAvoid" + to_string(TimerCounter)) >= 0.5f && distanceToWall < 300)
					{
						sf::Vector2f seekPos = limit + sf::Vector2f(-1, 0) * (10000 / lenb);
						m_manager.AddSeekTarget(seekPos, { a });
						gl::DeltaTime::RestartTimer("WallAvoid" + to_string(TimerCounter));
					}

					if (distanceToWall <= 400)
					{
						a->SetIsSeeingWall(true);
					}
					else
					{
						a->SetIsSeeingWall(false);
					}
					continue;
				}
			}
			else if (orientation.x < 0)
			{
				float X = 0;
				float Ax = position.x;
				float Ay = position.y;
				float ax = orientation.x;
				float ay = orientation.y;
				float lenb = abs(X - Ax);

				float distFact = lenb / abs(ax);

				float Y = Ay + ay * distFact;

				if (Y >= 0 && Y <= 1080)
				{
					limit = sf::Vector2f(X, Y);
					float distanceToWall = Agent::distanceVector(position, limit);
					//m_manager.AddFleeTarget(limit, { a });
					if (!gl::DeltaTime::TimerExist("WallAvoid" + to_string(TimerCounter)))
					{
						gl::DeltaTime::AddTimer("WallAvoid" + to_string(TimerCounter));
					}

					if (gl::DeltaTime::GetTimer("WallAvoid" + to_string(TimerCounter)) >= 0.5f && distanceToWall < 300)
					{
						sf::Vector2f seekPos = limit + sf::Vector2f(1, 0) * (10000 / lenb);
						m_manager.AddSeekTarget(seekPos, { a });
						gl::DeltaTime::RestartTimer("WallAvoid" + to_string(TimerCounter));
					}

					if (distanceToWall <= 400)
					{
						a->SetIsSeeingWall(true);
					}
					else
					{
						a->SetIsSeeingWall(false);
					}
					continue;
				}
			}

			if (orientation.y > 0)
			{
				float Y = 1080;
				float Ax = position.x;
				float Ay = position.y;
				float ax = orientation.x;
				float ay = orientation.y;
				float lenb = abs(Y - Ay);

				float distFact = lenb / abs(ay);

				float X = Ax + ax * distFact;

				if (X >= 0 && X <= 1920)
				{
					limit = sf::Vector2f(X, Y);

					float distanceToWall = Agent::distanceVector(position, limit);
					//m_manager.AddFleeTarget(limit, { a });
					if (!gl::DeltaTime::TimerExist("WallAvoid" + to_string(TimerCounter)))
					{
						gl::DeltaTime::AddTimer("WallAvoid" + to_string(TimerCounter));
					}

					if (gl::DeltaTime::GetTimer("WallAvoid" + to_string(TimerCounter)) >= 0.5f && distanceToWall < 300)
					{
						sf::Vector2f seekPos = limit + sf::Vector2f(0, -1) * (10000 / lenb);
						m_manager.AddSeekTarget(seekPos, { a });
						gl::DeltaTime::RestartTimer("WallAvoid" + to_string(TimerCounter));
					}
					if (distanceToWall <= 400)
					{
						a->SetIsSeeingWall(true);
					}
					else
					{
						a->SetIsSeeingWall(false);
					}
					continue;
				}
			}
			else if (orientation.y < 0)
			{
				float Y = 0;
				float Ax = position.x;
				float Ay = position.y;
				float ax = orientation.x;
				float ay = orientation.y;
				float lenb = abs(Y - Ay);

				float distFact = lenb / abs(ay);

				float X = Ax + ax * distFact;

				if (X >= 0 && X <= 1920)
				{
					limit = sf::Vector2f(X, Y);
					float distanceToWall = Agent::distanceVector(position, limit);
					//m_manager.AddFleeTarget(limit, { a });
					if (!gl::DeltaTime::TimerExist("WallAvoid" + to_string(TimerCounter)))
					{
						gl::DeltaTime::AddTimer("WallAvoid" + to_string(TimerCounter));
					}

					if (gl::DeltaTime::GetTimer("WallAvoid" + to_string(TimerCounter)) >= 0.5f && distanceToWall < 300)
					{
						sf::Vector2f seekPos = limit + sf::Vector2f(0, 1) * (10000 / lenb);
						m_manager.AddSeekTarget(seekPos, { a });
						gl::DeltaTime::RestartTimer("WallAvoid" + to_string(TimerCounter));
					}

					if (distanceToWall <= 400)
					{
						a->SetIsSeeingWall(true);
					}
					else
					{
						a->SetIsSeeingWall(false);
					}
					continue;
				}
			}
			TimerCounter++;
		}

		std::vector<Agent*> agents = m_manager.GetAgents();
		for (Agent* a : agents)
		{
			if ((Agent::distanceVector(a->getPosition(), m_flag.GetPosition()) <= m_flag.GetRadious() 
				&& (m_flag.GetCarrier() == nullptr 
					|| (a->GetTeam() != m_flag.GetCarrier()->GetTeam() 
						&& gl::DeltaTime::GetTimer("CatchFlag") >= 1.0f)))
				&& !a->GetIsSeeingWall())
			{
				m_flag.SetCarrier(a);
				std::cout << "Team: " << a->GetTeam() << "\tTime: " << gl::DeltaTime::GetTimer("CatchFlag") << endl;
				gl::DeltaTime::RestartTimer("CatchFlag");
			}
		}

		Agent* carrier = m_flag.GetCarrier();
		if (carrier != nullptr)
		{
			std::string team = carrier->GetTeam();
			if (team == "left")
			{
				for (Agent* a : m_manager.GetAgents("right"))
				{
					if (!a->GetIsSeeingWall())
						m_manager.AddPursuitTarget(carrier->getPosition(), carrier->getVelocity(), { a });
					m_manager.AddEvadeTarget(a->getPosition(), a->getVelocity(), {carrier});
				}
				m_manager.AddSeekTarget({100, 540}, { carrier });
				m_manager.AddWanderBehaviour(m_manager.GetAgents("left"));
			}
			else if(team == "right")
			{

				for (Agent* a : m_manager.GetAgents("left"))
				{
					if (!a->GetIsSeeingWall())
						m_manager.AddPursuitTarget(carrier->getPosition(), carrier->getVelocity(), { a });
					m_manager.AddEvadeTarget(a->getPosition(), a->getVelocity(), { carrier });
				}
				m_manager.AddSeekTarget({ 1820, 540 }, { carrier });
				m_manager.AddWanderBehaviour(m_manager.GetAgents("right"));
			}
		}
		else
		{
			for (Agent*& a : agents)
			{
				if (!a->GetIsSeeingWall())
					m_manager.AddSeekTarget(m_flag.GetPosition(), { a });
			}
		}

		for (Agent* a : m_manager.GetAgents("left"))
		{
			for (Agent* b : m_manager.GetAgents("right"))
			{
				if (Agent::distanceVector(a->getPosition(), b->getPosition()) <= 50 && a != carrier && b != carrier)
				{	
					if (!b->GetIsSeeingWall())
						m_manager.AddFleeTarget(a->getPosition(), { b });
					if (!a->GetIsSeeingWall())
						m_manager.AddFleeTarget(b->getPosition(), { a });
				}
			}
		}

		m_manager.Update();
		m_flag.Update();

		if (carrier != nullptr)
		{
			if (m_flag.GetPosition().x < 0 || m_flag.GetPosition().x > 1920
				|| m_flag.GetPosition().y < 0 || m_flag.GetPosition().y > 1080)
			{
				Restart();
			}
				
			if (carrier->GetTeam() == "left" && m_flag.GetPosition().x < 300)
			{
				Restart();
				m_leftPoints++;

				m_pointsText.setString(to_string(m_leftPoints) + " | " + to_string(m_rightPoints));

				m_pointsText.setOrigin({ m_pointsText.getGlobalBounds().width / 2, 0 });

				if (m_leftPoints == 5)
				{
					m_Finished = true;
					m_pointsText.setString("Left Wins!");
					m_pointsText.setOrigin({ m_pointsText.getGlobalBounds().width / 2, 0 });
				}
			}
			else if (carrier->GetTeam() == "right" && m_flag.GetPosition().x > 1620)
			{
				Restart();
				m_rightPoints++;

				m_pointsText.setString(to_string(m_leftPoints) + " | " + to_string(m_rightPoints));

				m_pointsText.setOrigin({ m_pointsText.getGlobalBounds().width / 2, 0 });

				if (m_rightPoints == 5)
				{
					m_Finished = true;
					m_pointsText.setString("Right Wins!");
					m_pointsText.setOrigin({ m_pointsText.getGlobalBounds().width / 2, 0 });
				}
			}
		}
	}
	else
	{
		if (!gl::DeltaTime::TimerExist("Finished"))
		{
			gl::DeltaTime::AddTimer("Finished");
		}
		else
		{
			gl::DeltaTime::StartTimer("Finished");
		}

		if (gl::DeltaTime::GetTimer("Finished") > 3.0f)
		{
			gl::DeltaTime::RestartTimer("Finished");
			gl::DeltaTime::StopTimer("Finished");
			gl::DeltaTime::RestartTimer("CatchFlag");
			m_rightPoints = 0;
			m_leftPoints = 0;

			m_pointsText.setString("0 | 0");
			m_pointsText.setOrigin({ m_pointsText.getGlobalBounds().width / 2, 0 });

			Restart();

			m_Finished = false;
		}
	}

}

void Game::Restart()
{
	m_flag.SetCarrier(nullptr);
	m_flag.SetPosition({960,540});
	m_manager.Restart();
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			gl::Input::HandleInputs(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			gl::Input::HandleInputs(event.key.code, false);
			break;
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}
}

void Game::render()
{
	m_window->clear();
	m_window->draw(m_stage);
	m_manager.Render(m_window);
	m_flag.Render(m_window);
	m_window->draw(m_pointsText);
	m_window->display();
}

void Game::destroy()
{
	m_manager.Destroy();
	m_flag.Destroy();
	delete m_window;
}

sf::RenderWindow* getGameWindow(int x, int y)
{
	static sf::RenderWindow* window = nullptr;
	if (window == nullptr)
		window = new sf::RenderWindow(sf::VideoMode(x, y), "AI");
	return window;
}
