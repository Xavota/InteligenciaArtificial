#include "Game_FP.h"
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
	/* Utility */

	m_windowSize = { 1024, 1024 };
	m_window = new sf::RenderWindow(sf::VideoMode(m_windowSize.x, m_windowSize.y), "Path Finding");
	ImGui::SFML::Init(*m_window);

	m_camera.Init(sf::FloatRect{ 0,0,(float)m_windowSize.x,(float)m_windowSize.y }, 1.5f);


	/* Resources */
	// Textures


	// Fonts


	// UI
	gl::UI::Init(m_window);


	/* Actors */

	m_grid.Init({0,0,1024,1024},{21,21});

	



}

void Game_FP::Update()
{
	/* Utility */

	m_camera.Update(m_window);

	gl::UI::Update();

	m_grid.Update(m_window);
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

	}
	ImGui::End();

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