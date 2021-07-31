#include "Game_FP.h"
#include "MouseInfo.h"
#include "Globals.h"

void Game_FP::Run()
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

void Game_FP::Init()
{
	m_gridSize = { 51,51 };
	m_cellsSize = { 32.f,32.f };

	/* Utility */

	m_windowSize = { 1024, 1024 };
	m_window = new sf::RenderWindow(sf::VideoMode(m_windowSize.x, m_windowSize.y), "Path Finding");
	ImGui::SFML::Init(*m_window);

	//m_camera.Init(sf::FloatRect{ 0, 0,(float)m_windowSize.x,(float)m_windowSize.y }, 1.5f);
	float size = m_gridSize.x * m_cellsSize.x > m_gridSize.y * m_cellsSize.y ? m_gridSize.x * m_cellsSize.x : m_gridSize.y * m_cellsSize.y;
	m_camera.Init(sf::FloatRect{ 0, 0,(float)size,(float)size }, 1.5f);


	/* Resources */
	// Textures


	// Fonts
	gl::CFont::AddFont("Numbers", "Cubest-Medium.otf");

	// UI
	gl::UI::Init(m_window);


	/* Actors */

	m_grid.Init(m_gridSize, m_cellsSize);

}

void Game_FP::Update()
{
	/* Utility */

	m_camera.Update(m_window);

	MouseInfo::Update();
	gl::UI::Update();

	if (gl::Input::GetKeyPressed(sf::Keyboard::Enter));
	{
		m_notFound = m_grid.Update(m_window);
	}
}

void Game_FP::ProcessEvents()
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

void Game_FP::Render()
{
	m_window->clear(); // Clean window

	gl::UI::Render(m_window);

	m_grid.Render(m_window);
	/* ImGui */

	ImguiRender();

	m_window->display(); // Swap chain
}

void Game_FP::ImguiRender()
{
	static bool AddingTeam = false;
	if (ImGui::Begin("Path Findig"))
	{
		if (ImGui::Button("Breath First Search"))
		{
			m_grid.BreathFirstSearch();
		}
		if (ImGui::Button("Depth First Search"))
		{
			m_grid.DepthFirstSearch();
		}
		if (ImGui::Button("Dijstra Search"))
		{
			m_grid.DijstraSearch();
		}
		if (ImGui::Button("Best First Search"))
		{
			m_grid.BestFirstSearch();
		}
		if (ImGui::Button("Restart search"))
		{
			m_grid.RestartSearch();
		}
		if (ImGui::Button("Restart"))
		{
			m_grid.RestartAll();
		}

		static bool showLines = true;
		if (ImGui::Checkbox("Show Lines", &showLines))
		{
			m_grid.ShowLines(showLines);
		}
		static bool showWeights = false;
		if (ImGui::Checkbox("Show Weights", &showWeights))
		{
			m_grid.ShowWeights(showWeights);
		}
	}
	ImGui::End();
	if (!m_notFound)
	{
		if (ImGui::Begin("Error"))
		{
			ImGui::Text("Path not found");
			if (ImGui::Button("Ok"))
			{
				m_grid.RestartSearch();
			}
		}
		ImGui::End();
	}

	ImGui::SFML::Render(*m_window);
	ImGui::EndFrame();
}

void Game_FP::Destroy()
{
	ImGui::SFML::Shutdown();

	delete m_window;
}

Game_FP* getGame_FP()
{
	static Game_FP* g = nullptr;
	if (g == nullptr)
	{
		g = new Game_FP();
	}
	return g;
}