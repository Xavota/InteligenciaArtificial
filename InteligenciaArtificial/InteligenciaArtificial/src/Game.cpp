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

	m_manager.Init(2, 1910, 1070, sf::Color::Red);
	//m_manager.Init(50, 1910, 1070, sf::Color::Blue);
}

void Game::update()
{
	static bool uno = false;
	if (gl::DeltaTime::TimerExist("test"))
	{
		cout << gl::DeltaTime::GetTimer("test") << "\t" << gl::DeltaTime::GetTimer("test2") << endl;
		if (gl::DeltaTime::GetTimer("test") > 5)
		{
			if (!uno)
			{
				gl::DeltaTime::RestartTimer("test");
				uno = true;
				gl::DeltaTime::StopTimer("test");
				gl::DeltaTime::StartTimer("test2");
			}
			else
			{
				gl::DeltaTime::DeleteTimer("test");
			}
		}
		if (gl::DeltaTime::GetTimer("test2") > 3)
		{
			gl::DeltaTime::RestartTimer("test2");
			gl::DeltaTime::StopTimer("test2");
			gl::DeltaTime::StartTimer("test");
		}
	}
	m_manager.Update();
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
	static sf::CircleShape m1(5.f);
	m1.setPosition({500, 500});
	m1.setFillColor(sf::Color::Green);
	static sf::CircleShape m2(5.f);
	m2.setPosition({ 1000, 500 });
	m2.setFillColor(sf::Color::Green);
	static sf::CircleShape m3(5.f);
	m3.setPosition({ 1000, 1000 });
	m3.setFillColor(sf::Color::Green);
	static sf::CircleShape m4(5.f);
	m4.setPosition({ 500, 1000 });
	m4.setFillColor(sf::Color::Green);
	static sf::CircleShape m5(5.f);
	m5.setPosition({ 750, 750 });
	m5.setFillColor(sf::Color::Yellow);
	m_window->clear();
	m_window->draw(m1);
	m_window->draw(m2);
	m_window->draw(m3);
	m_window->draw(m4);
	m_window->draw(m5);
	m_manager.Render(m_window);
	m_window->display();
}

void Game::destroy()
{
	m_manager.Destroy();
	delete m_window;
}

sf::RenderWindow* getGameWindow(int x, int y)
{
	static sf::RenderWindow* window = nullptr;
	if (window == nullptr)
		window = new sf::RenderWindow(sf::VideoMode(x, y), "AI");
	return window;
}
