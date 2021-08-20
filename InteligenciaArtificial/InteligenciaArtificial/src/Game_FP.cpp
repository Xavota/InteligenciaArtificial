#include "Game_FP.h"
#include "MouseInfo.h"
#include "Globals.h"

#include "MapEditorMenu.h"

#include <fstream>
#include <sstream>

void Game_FP::Run()
{
	Init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->isOpen())
	{
		ProcessEvents();

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate.asMicroseconds() > 5000000)
		{
			timeSinceLastUpdate = sf::Time::Zero;
		}
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
	m_gridSize = { 81,81 };
	m_cellsSize = { 32.f,32.f };

	/* Utility */

	m_windowSize = { 1024, 1024 };
	m_window = new sf::RenderWindow(sf::VideoMode(m_windowSize.x, m_windowSize.y), "Path Finding");
	ImGui::SFML::Init(*m_window);

	m_camera.Init(sf::FloatRect{ 0, 0,(float)m_windowSize.x,(float)m_windowSize.y }, 1.5f);


	/* Resources */
	// Textures
	gl::CTexture::AddTexture("Anim", "AnimacionesFindPath.png");

	gl::CTexture::AddTexture("Grass", "All.png");
	gl::CTexture::AddTexture("Water", "All.png");
	gl::CTexture::AddTexture("Sand", "All.png");
	gl::CTexture::AddTexture("Wall", "Walls.png");

	// Fonts
	gl::CFont::AddFont("Numbers", "Cubest-Medium.otf");

	// UI
	gl::UI::Init(m_window);
	gl::UI::ChangeUI(new MapEditorMenu());


	/* Actors */
	m_stateMachine.Init();
	m_animMachine.Init();
	m_manager.Init(&m_stateMachine, &m_animMachine);

	OpenMapFile("Map1.txt");
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
	m_manager.Update();
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


	/* Everything */

	m_grid.Render(m_window);

	m_manager.Render(m_window);


	/* UI */

	gl::UI::Render(m_window);


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
		if (ImGui::Button("A Star Search"))
		{
			m_grid.AStarSearch();
		}
		ImGui::Separator();
		ImGui::Separator();
		if (ImGui::Button("Remove Walls"))
		{
			m_grid.RemoveWalls();
		}
		if (ImGui::Button("Restart search"))
		{
			m_grid.RestartSearch();
		}
		if (ImGui::Button("Restart"))
		{
			m_grid.RestartAll();
		}
	}

	ImGui::End();
	if (ImGui::Begin("Maping"))
	{
		if (ImGui::Button("Open Map"))
		{
			OpenMapFile(OpenFileGetName());
		}
		if (ImGui::Button("Save Map"))
		{
			SaveMapFile(SaveFileGetName());
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
	m_manager.Destroy();
	m_grid.Destroy();

	ImGui::SFML::Shutdown();

	delete m_window;
}

void Game_FP::OpenMapFile(std::string mapName)
{
	ifstream mapFile(mapName);
	if (!mapFile)
	{
		return;
	}
	

	std::vector<std::vector<int>> grid;
	std::vector<std::vector<bool>> wallGrid;

	bool readingGrid = true;


	while (!mapFile.eof())
	{
		std::string line;
		getline(mapFile, line);

		std::stringstream ss(line);
		line = "";
		ss >> line;

		if (line == "@Size")
		{
			int sizeX = 0;
			int sizeY = 0;

			ss >> sizeX;
			ss >> sizeY;
			m_gridSize = {sizeX, sizeY};
		}
		else if (line == "@Grid")
		{
			readingGrid = true;
		}
		else if (line == "@Walls")
		{
			readingGrid = false;
		}
		else
		{
			if (readingGrid)
			{
				grid.push_back(std::vector<int>());
				int number = atoi(line.c_str());
				grid[grid.size() - 1].push_back(number);

				while (!ss.eof())
				{
					ss >> number;
					grid[grid.size() - 1].push_back(number);
				}
			}
			else
			{
				wallGrid.push_back(std::vector<bool>());
				int number = atoi(line.c_str());
				wallGrid[wallGrid.size() - 1].push_back(number == 0 ? false : true);

				while (!ss.eof())
				{
					ss >> number;
					wallGrid[wallGrid.size() - 1].push_back(number == 0 ? false : true);
				}
			}
		}
	}

	m_grid.Init(m_gridSize, m_cellsSize, grid, wallGrid, &m_manager);

	float size = m_gridSize.x * m_cellsSize.x > m_gridSize.y * m_cellsSize.y ? 
	             m_gridSize.x * m_cellsSize.x : m_gridSize.y * m_cellsSize.y;
	m_camera.Init(sf::FloatRect{ 0, 0,(float)size,(float)size }, 1.5f);

}

void Game_FP::SaveMapFile(std::string mapName)
{
	std::ofstream file(mapName);
	if (!file)
	{
		return;
	}

	std::vector<std::vector<Node>>* nodeGrid = m_grid.GetNodeGrid();

	file << "@Size ";
	file << nodeGrid->size();
	file << " ";
	file << (*nodeGrid)[0].size();

	file << "\n@Grid\n";
	for (int i = 0; i < nodeGrid->size(); i++)
	{
		for (int j = 0; j < (*nodeGrid)[i].size(); j++)
		{
			file << ((*nodeGrid)[j][i].GetTileType() == eNODE_PATH_TYPE::GRASS ? 0 :
					((*nodeGrid)[j][i].GetTileType() == eNODE_PATH_TYPE::SAND  ? 2 :
					((*nodeGrid)[j][i].GetTileType() == eNODE_PATH_TYPE::WATER ? 1 : 3)));
			file << " ";
		}
		file << "\n";
	}

	file << "\n@Walls\n";
	for (int i = 0; i < nodeGrid->size(); i++)
	{
		for (int j = 0; j < (*nodeGrid)[i].size(); j++)
		{
			file << ((*nodeGrid)[j][i].GetState() == eNODE_STATE::WALL ? 1 : 0);
			file << " ";
		}
		file << "\n";
	}

	file.close();
}

void Game_FP::Grass(std::vector<void*> params)
{
	Game_FP* g = (Game_FP*)params[0];
	MouseInfo::ChangeTileType(eTILE_TYPE::GRASS);
}

void Game_FP::Sand(std::vector<void*> params)
{
	Game_FP* g = (Game_FP*)params[0];
	MouseInfo::ChangeTileType(eTILE_TYPE::SAND);
}

void Game_FP::Water(std::vector<void*> params)
{
	Game_FP* g = (Game_FP*)params[0];
	MouseInfo::ChangeTileType(eTILE_TYPE::WATER);
}

void Game_FP::Wall(std::vector<void*> params)
{
	Game_FP* g = (Game_FP*)params[0];
	MouseInfo::ChangeTileType(eTILE_TYPE::WALL);
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

std::string OpenFileGetName(HWND owner)
{

	// common dialog box structure, setting all fields to 0 is important
	OPENFILENAME ofn = { 0 };
	TCHAR szFile[260] = { 0 };

	// Initialize remaining fields of OPENFILENAME structure
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = owner;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return szFile;
	}
	return "";
}

std::string SaveFileGetName(HWND owner)
{

	// common dialog box structure, setting all fields to 0 is important
	OPENFILENAME ofn = { 0 };
	TCHAR szFile[260] = { 0 };

	// Initialize remaining fields of OPENFILENAME structure
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = owner;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		return szFile;
	}
	return "";
}