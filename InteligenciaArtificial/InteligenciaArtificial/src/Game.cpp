#include "Game.h"
#include "Globals.h"

void Game::Run()
{
	Init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->isOpen())
	{
		ProcessEvents();

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			ProcessEvents();
			gl::DeltaTime::Update(timePerFrame.asSeconds());
			Update();
			gl::Input::Update();
		}

		if (timeSinceLastUpdate > sf::Time::Zero)
			ImGui::SFML::Update(*m_window, timeSinceLastUpdate);
		else
			ImGui::NewFrame();

		Render();
	}

	Destroy();
}

void Game::Init()
{
	/* Utility */

	m_windowSize = {1024, 1024};
	m_window = GetGameWindow(m_windowSize.x, m_windowSize.y);
	ImGui::SFML::Init(*m_window);

	m_radious = m_windowSize.x < m_windowSize.y ? m_windowSize.x / 2 : m_windowSize.y / 2;
	m_center = {m_windowSize.x / 2.f, m_windowSize.y / 2.f};

	m_camera.Init(sf::FloatRect{0,0,(float)m_windowSize.x,(float)m_windowSize.y}, 1.5f);


	/* Resources */
	// Textures
	gl::CTexture::AddTexture("Flag", "Flag.png");
	gl::CTexture::AddTexture("Agent", "Animaciones2.png");
	gl::CTexture::AddTexture("Stage", "stage.png");
	gl::CTexture::AddTexture("Player", "PlayerAnimSet.png", sf::Color(0, 255, 255));

	// Fonts
	gl::CFont::AddFont("Points", "Caramel Sweets.ttf");


	/* Actors */

	m_flag.Init({ (float)m_windowSize.x / 2, (float)m_windowSize.y / 2 });
	m_agentsStateMachine.Init();
	m_agentsAnimMachine.Init();
	m_manager.Init(&m_agentsStateMachine, &m_agentsAnimMachine);
	

	/* Teams */

	AddTeam("Sip", sf::Color::Red);
	AddTeam("Nop", sf::Color::Blue);
	/*AddTeam("Meh", sf::Color::Green);
	AddTeam("Yup", sf::Color::Magenta);
	AddTeam("Sup", sf::Color::Yellow);
	AddTeam("Lol", sf::Color::Cyan);*/

	AddTeammates("Sip", 10);
	AddTeammates("Nop", 10);
	/*AddTeammates("Meh", 10);
	AddTeammates("Yup", 10);
	AddTeammates("Sup", 10);
	AddTeammates("Lol", 10);*/


	/* Winning text */

	m_titleText.setFont(*gl::CFont::GetFont("Points"));
	m_titleText.setCharacterSize(100);
	m_titleText.setString("The winner is");
	m_titleText.setOrigin({ m_titleText.getGlobalBounds().width / 2, m_titleText.getGlobalBounds().height / 2 });
	m_titleText.setPosition({ (float)(m_windowSize.x / 2), (float)(m_windowSize.y / 2) - 50 });

	m_winnerText.setFont(*gl::CFont::GetFont("Points"));
	m_winnerText.setCharacterSize(100);
	m_winnerText.setOrigin({ m_winnerText.getGlobalBounds().width / 2, m_winnerText.getGlobalBounds().height / 2 });
	m_winnerText.setPosition({ (float)(m_windowSize.x / 2), (float)(m_windowSize.y / 2) + 50 });
}

void Game::Update()
{
	/* Utility */

	m_camera.Update(m_window);


	/* Actors */

	m_manager.Update();
	m_flag.Update();



	/* Score */

	Agent* carrier = m_flag.GetCarrier();
	if (carrier != nullptr && !m_finished)
	{
		for (Team& t : m_teams)
		{
			if (carrier->GetTeam() == t.m_name && t.m_safeZone.intersects(sf::IntRect(carrier->getPosition().x - 1, carrier->getPosition().y - 1, 2, 2)))
			{
				t.m_points++;
				if (!CheckWin(t))
				{
					Restart();
				}
			}
		}
	}
	

	/* Visuals */

	for (int i = 0; i < m_teams.size(); i++)
	{
		m_pointsTexts[i].setString(to_string(m_teams[i].m_points));
		m_pointsTexts[i].setOrigin({ m_pointsTexts[i].getGlobalBounds().width / 2, 0 });
	}


	/* Win */

	if (m_finished)
	{
		static float winTime = 0.0f;
		winTime += gl::DeltaTime::Time();

		if (winTime >= 5.0f)
		{
			for (Team& t : m_teams)
			{
				t.m_points = 0;
			}
			m_finished = false;
			winTime = 0.0f;
			Restart();
		}
	}


	/* Restart */

	sf::Vector2f flagPos = m_flag.GetPosition();
	if (flagPos.x <= m_center.x - m_radious || flagPos.x >= m_center.x + m_radious || flagPos.y <= m_center.y - m_radious || flagPos.y >= m_center.y + m_radious)
	{
		Restart();
	}
}

bool Game::CheckWin(Team& team)
{
	if (team.m_points >= m_maxPoints)
	{
		m_finished = true;
		m_winnerTeam = team.m_name;

		m_titleText.setPosition({ (float)(m_camera.GetCenter().x), (float)(m_camera.GetCenter().y) - 50 });

		m_winnerText.setString(m_winnerTeam);
		m_winnerText.setOrigin({ m_winnerText.getGlobalBounds().width / 2, m_winnerText.getGlobalBounds().height / 2 });
		m_winnerText.setFillColor(team.m_color);
		m_winnerText.setPosition({ (float)(m_camera.GetCenter().x), (float)(m_camera.GetCenter().y) + 50 });

		return true;
	}
	return false;
}

void Game::Restart()
{
	m_restart = true;

	m_flag.SetCarrier(nullptr);
	m_flag.SetPosition(m_center);

	m_manager.Restart();
	m_manager.Update();

	m_restart = false;
}

void Game::ProcessEvents()
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

		ImGui::SFML::ProcessEvent(event);
	}
}

void Game::Render()
{
	m_window->clear(); // Clean window


	/* Team zones */

	static sf::RectangleShape shape;
	for (int i = 0; i < m_teams.size(); i++)
	{
		shape.setPosition({ (float)m_teams[i].m_spawnZone.left, (float)m_teams[i].m_spawnZone.top });
		shape.setSize({ (float)m_teams[i].m_spawnZone.width, (float)m_teams[i].m_spawnZone.height });
		shape.setFillColor(sf::Color(m_teams[i].m_color.r, m_teams[i].m_color.g, m_teams[i].m_color.b, 64));

		m_window->draw(shape);


		shape.setPosition({ (float)m_teams[i].m_safeZone.left, (float)m_teams[i].m_safeZone.top });
		shape.setSize({ (float)m_teams[i].m_safeZone.width, (float)m_teams[i].m_safeZone.height });
		shape.setFillColor(sf::Color(m_teams[i].m_color.r, m_teams[i].m_color.g, m_teams[i].m_color.b, 127));

		m_window->draw(shape);


		shape.setPosition(m_teams[i].m_seekPoint);
		shape.setSize({ 10, 10 });
		shape.setFillColor(sf::Color(m_teams[i].m_color.r, m_teams[i].m_color.g, m_teams[i].m_color.b, 255));

		m_window->draw(shape);
	}

	shape.setPosition(m_center - sf::Vector2f{(float)m_radious, (float)m_radious});
	shape.setSize({ m_radious * 2.f, m_radious * 2.f });
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color(255, 255, 255, 255));
	shape.setOutlineThickness(5);

	m_window->draw(shape);

	shape.setOutlineColor(sf::Color::Transparent);


	/* Actors */

	m_manager.Render(m_window);
	m_flag.Render(m_window);


	/* Texts */

	if (!m_finished)
	{
		for (sf::Text& text : m_pointsTexts)
		{
			m_window->draw(text);
		}
	}
	else
	{
		m_window->draw(m_titleText);
		m_window->draw(m_winnerText);
	}


	/* ImGui */

	ImguiRender();


	m_window->display(); // Swap chain
}

void Game::ImguiRender()
{	
	static bool AddingTeam = false;
	if (ImGui::Begin("Teams"))
	{
		if (ImGui::CollapsingHeader("Teams"))
		{
			for (int i = 0; i < m_teams.size(); i++)
			{
				ImGui::Text("  "); 
				ImGui::SameLine();
				if (ImGui::CollapsingHeader(m_teams[i].m_name.c_str()))
				{
					/* Points */
					ImGui::PushID((i * 4) + 0);
					ImGui::Text("    "); ImGui::SameLine();	
					if (ImGui::Button("-")) 
					{
						if (m_teams[i].m_points != 0)
						{
							m_teams[i].m_points--;
						}
					}
					ImGui::SameLine();
					ImGui::Text(to_string(m_teams[i].m_points).c_str()); ImGui::SameLine();
					if (ImGui::Button("+"))
					{
						m_teams[i].m_points++;
						CheckWin(m_teams[i]);
					}
					ImGui::PopID();

					/* Teammates */
					ImGui::PushID((i * 4) + 1);
					ImGui::Text("    "); ImGui::SameLine();
					if (ImGui::Button("-"))
					{
						if (m_teams[i].m_teamMembers != 0)
						{
							RemoveTeammates(m_teams[i].m_name, 1);
						}
					}
					ImGui::SameLine();
					ImGui::Text(to_string(m_teams[i].m_teamMembers).c_str()); ImGui::SameLine();
					if (ImGui::Button("+"))
					{
						AddTeammates(m_teams[i].m_name, 1);
					}
					ImGui::PopID();


					ImGui::Text("");


					float color[3] = { (float)m_teams[i].m_color.r / 255, (float)m_teams[i].m_color.g / 255, (float)m_teams[i].m_color.b / 255 };
					ImGui::PushID((i * 4) + 2);
					ImGui::Text("    "); ImGui::SameLine();
					if (ImGui::ColorPicker3("Team color", color))
					{
						UpdateTeamColor(m_teams[i].m_name, sf::Color(color[0] * 255, color[1] * 255, color[2] * 255, 255));
					}
					ImGui::PopID();


					ImGui::Text("");


					ImGui::PushID((i * 4) + 3);
					ImGui::Text("    "); ImGui::SameLine();
					if (ImGui::Button("Delete team"))
					{
						RemoveTeam(m_teams[i].m_name);
						ImGui::PopID();
						break;
					}
					ImGui::PopID();
				}
			}
		}
		if (ImGui::Button("AddTeam"))
		{
			AddingTeam = true;
		}
	}
	ImGui::End();
	if (AddingTeam)
	{
		if (ImGui::Begin("Team Info"))
		{
			static char teamName[255];
			static int members;
			static float color[3];

			ImGui::InputText("Team Name", teamName, 255);
			ImGui::DragInt("Initial members", &members, 1, 0, 50);
			ImGui::Text("");
			ImGui::ColorPicker3("Team color", color);

			if (ImGui::Button("Add Team"))
			{
				if (teamName != "" && members <= 50 && members >= 0)
				{
					AddTeam(teamName, sf::Color(color[0] * 255, color[1] * 255, color[2] * 255, 255));
					AddTeammates(teamName, members);
					AddingTeam = false;
				}
			}

			if (ImGui::Button("Cancel"))
			{
				AddingTeam = false;
			}
		}
		ImGui::End();
	}

	if (ImGui::Begin("Game"))
	{
		if (ImGui::DragInt("MaxPoints", &m_maxPoints, 1, 1, 100))
		{
			for (Team& t : m_teams)
			{
				CheckWin(t);
			}
		}

		if (ImGui::DragInt("Radious", &m_radious, 1, 100, 4096))
		{
			UpdateTeamsZones();
		}

		static float center[2] = {m_center.x, m_center.y};
		if (ImGui::DragFloat2("Center", center, 1, -4096, 4096))
		{
			m_center = {center[0], center[1]};
			UpdateTeamsZones();
		}
	}
	ImGui::End();

	ImGui::SFML::Render(*m_window);
	ImGui::EndFrame();
}

void Game::Destroy()
{
	m_manager.Destroy();
	m_flag.Destroy();

	m_agentsStateMachine.Destroy();
	m_agentsAnimMachine.Destroy();

	ImGui::SFML::Shutdown();

	delete m_window;
}

void Game::AddTeam(std::string teamName, sf::Color teamColor)
{
	/* Check existance */

	for (Team& t : m_teams)
	{
		if (t.m_name == teamName)
		{
			std::cout << "Team name already exist" << std::endl;
			return;
		}
	}


	/* Add team */

	m_teams.push_back(Team());

	size_t teamsCount = m_teams.size();

	m_teams[teamsCount - 1].m_name = teamName;
	m_teams[teamsCount - 1].m_color = teamColor;

	// Adds its points text
	m_pointsTexts.push_back(sf::Text("0", *gl::CFont::GetFont("Points"), 75));
	m_pointsTexts[m_pointsTexts.size() - 1].setOrigin({ m_pointsTexts[m_pointsTexts.size() - 1].getGlobalBounds().width / 2, 0 });


	/* Update zones of all teams */

	UpdateTeamsZones();
}

void Game::AddTeammates(std::string teamName, unsigned int count)
{
	/* Adds agents with the team info */
	for (int i = 0; i < m_teams.size(); i++)
	{
		if (m_teams[i].m_name == teamName)
		{
			m_manager.AddAgents(count, m_teams[i].m_spawnZone, m_teams[i].m_color, teamName, m_teams[i].m_seekPoint);

			m_teams[i].m_teamMembers += count;

			return;
		}
	}

	std::cout << "Team name doesn't exist" << std::endl;
}

void Game::RemoveTeam(std::string teamName)
{
	/* Deletes the team, teammates and points text */

	for (int i = 0; i < m_teams.size(); i++)
	{
		if (m_teams[i].m_name == teamName)
		{
			RemoveTeammates(teamName, m_teams[i].m_teamMembers);
			m_teams.erase(m_teams.begin() + i);
			m_pointsTexts.erase(m_pointsTexts.begin() + i);
			break;
		}
	}


	/* Update zones of all teams */

	UpdateTeamsZones();
}

void Game::RemoveTeammates(std::string teamName, unsigned int count)
{
	/* Gets some value of the carrier to check it later */
	
	eAGENT_STATE_TYPE state = eAGENT_STATE_TYPE::NONE;
	if (m_flag.GetCarrier() != nullptr)
		eAGENT_STATE_TYPE state = m_flag.GetCarrier()->GetState();


	/* Removes the agents of the team */

	for (int i = 0; i < m_teams.size(); i++)
	{
		if (m_teams[i].m_name == teamName)
		{
			if (m_teams[i].m_teamMembers >= count)
			{
				m_manager.RemoveAgents(count, teamName);
				m_teams[i].m_teamMembers -= count;
			}
			else
			{
				m_manager.RemoveAgents(m_teams[i].m_teamMembers, teamName);
				m_teams[i].m_teamMembers = 0;
			}
		}
	}


	/* Checks the previous saved value, to see if the carrier still exists */

	if (m_flag.GetCarrier() != nullptr && state != m_flag.GetCarrier()->GetState())
	{
		m_flag.SetCarrier(nullptr);
	}
}

void Game::UpdateTeamColor(std::string teamName, sf::Color color)
{
	for (int i = 0; i < m_teams.size(); i++)
	{
		if (m_teams[i].m_name == teamName)
		{
			m_teams[i].m_color = color;
			m_manager.UpdateTeamColor(m_teams[i].m_name, color);

			m_pointsTexts[i].setFillColor(color);
		}
	}
}

void Game::UpdateTeamsZones()
{
	/* Update zones of all teams */

	size_t teamsCount = m_teams.size();
	for (int i = 0; i < teamsCount; i++)
	{
		// Gets the angle around the center
		float angle = ((360 / teamsCount) * i) * (3.1416 / 180);

		// Updates seek point, safe zone and spawn zone
		m_teams[i].m_seekPoint = sf::Vector2f((m_radious - 100) * sin(angle) + (m_center.x),
			(m_radious - 100) * cos(angle) + (m_center.y));

		m_teams[i].m_safeZone = sf::IntRect(m_teams[i].m_seekPoint.x - 100, m_teams[i].m_seekPoint.y - 100, 200, 200);
		m_teams[i].m_spawnZone = sf::IntRect((m_radious / 2) * sin(angle) + (m_center.x) - (m_radious / 2),
			(m_radious / 2) * cos(angle) + (m_center.y) - (m_radious / 2),
			(m_radious), (m_radious));

		// Updates position of points texts
		m_pointsTexts[i].setPosition({ m_center.x - m_radious + (float)((m_radious * 2) / (m_pointsTexts.size() + 1)) * (i + 1), m_center.y - m_radious + 10 });
		m_pointsTexts[i].setFillColor(m_teams[i].m_color);

		// Tell the agents of its new data
		m_manager.UpdateTeamAperianceRange(m_teams[i].m_name, m_teams[i].m_spawnZone);
		m_manager.UpdateTeamBasePos(m_teams[i].m_name, m_teams[i].m_seekPoint);
	}
}

sf::RenderWindow* GetGameWindow(int x, int y)
{
	static sf::RenderWindow* window = nullptr;
	if (window == nullptr)
		window = new sf::RenderWindow(sf::VideoMode(x, y), "AI");
	return window;
}

Game* getGame()
{
	static Game* g = nullptr;
	if (g == nullptr)
	{
		g = new Game();
	}
	return g;
}