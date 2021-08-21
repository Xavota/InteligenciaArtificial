#include "Grid.h"
#include "Globals.h"

Grid::Grid(sf::Vector2i tiles, sf::Vector2f size)
{
	Init(tiles, size);
}

void Grid::Init(sf::Vector2i tiles, sf::Vector2f size)
{
	RestartAll();

	m_cellSize = size;
	m_nodeGrid.clear();
	for (int i = 0; i < tiles.x; i++)
	{
		m_nodeGrid.push_back(std::vector<Node>());
		for (int j = 0; j < tiles.y; j++)
		{
			m_nodeGrid[i].push_back(Node({ size.x * i, size.y * j }, { size.x, size.y }));
		}
	}

	for (int i = 0; i < tiles.x; i++)
	{
		for (int j = 0; j < tiles.y; j++)
		{
			if (i > 0)
			{
				int weight = rand() % 10;
				Node* temp = &m_nodeGrid[i][j];
				Node* temp2 = &m_nodeGrid[i - 1][j];
				temp->m_left = temp2;
				temp->m_leftWeight = weight;
				temp2->m_right = temp;
				temp2->m_rightWeight = weight;
			}
			if (j > 0)
			{
				int weight = rand() % 10;
				Node* temp = &m_nodeGrid[i][j];
				Node* temp2 = &m_nodeGrid[i][j - 1];
				temp->m_up = temp2;
				temp->m_upWeight = weight;
				temp2->m_down = temp;
				temp2->m_downWeight = weight;
			}
		}
	}

	m_nodeGrid[tiles.x / 8][tiles.y / 2].ChangeState(eNODE_STATE::START);
	m_start = &m_nodeGrid[tiles.x / 8][tiles.y / 2];
	m_nodeGrid[tiles.x * 7 / 8][tiles.y / 2].ChangeState(eNODE_STATE::END);
	m_end = &m_nodeGrid[tiles.x * 7 / 8][tiles.y / 2];
}

void Grid::Init(sf::Vector2i tiles, sf::Vector2f size, std::vector<std::vector<int>> grid, 
                std::vector<std::vector<bool>> wallGrid, PathFindingAgentManager* manager)
{
	RestartAll();

	m_manager = manager;


	m_cellSize = size;
	m_nodeGrid.clear();
	for (int i = 0; i < tiles.x; i++)
	{
		m_nodeGrid.push_back(std::vector<Node>());
		for (int j = 0; j < tiles.y; j++)
		{
			m_nodeGrid[i].push_back(Node({ size.x * i, size.y * j }, { size.x, size.y }, 
			                                         eNODE_PATH_TYPE(grid[j][i]), wallGrid[j][i]));
		}
	}

	for (int i = 0; i < tiles.x; i++)
	{
		for (int j = 0; j < tiles.y; j++)
		{
			if (i > 0)
			{
				int weight = rand() % 10;
				Node* temp = &m_nodeGrid[i][j];
				Node* temp2 = &m_nodeGrid[i - 1][j];
				temp->m_left = temp2;
				temp->m_leftWeight = GetWeight(temp2->GetTileType());
				temp2->m_right = temp;
				temp2->m_rightWeight = GetWeight(temp->GetTileType());
			}
			if (j > 0)
			{
				int weight = rand() % 10;
				Node* temp = &m_nodeGrid[i][j];
				Node* temp2 = &m_nodeGrid[i][j - 1];
				temp->m_up = temp2;
				temp->m_upWeight = GetWeight(temp2->GetTileType());;
				temp2->m_down = temp;
				temp2->m_downWeight = GetWeight(temp->GetTileType());;
			}
		}
	}

	m_nodeGrid[tiles.x / 8][tiles.y / 2].ChangeState(eNODE_STATE::START);
	m_start = &m_nodeGrid[tiles.x / 8][tiles.y / 2];
	m_nodeGrid[tiles.x * 7 / 8][tiles.y / 2].ChangeState(eNODE_STATE::END);
	m_end = &m_nodeGrid[tiles.x * 7 / 8][tiles.y / 2];

	m_manager->SetAgentPosition(m_nodeGrid[tiles.x / 8][tiles.y / 2].GetPosition());
}

bool Grid::Update(sf::RenderWindow* window)
{
	if (m_isSearching)
	{
		if (m_searchType == eSEARCH_TYPE::BREATH_FIRST)
		{
			BreathFirstSearchUpdate();
		}
		else if (m_searchType == eSEARCH_TYPE::DEPTH_FIRST)
		{
			DepthFirstSearchUpdate();
		}
		else if (m_searchType == eSEARCH_TYPE::DIJSTRA)
		{
			DijstraSearchUpdate();
		}
		else if (m_searchType == eSEARCH_TYPE::BEST_FIRST)
		{
			BestFirstSearchUpdate();
		}
		else if (m_searchType == eSEARCH_TYPE::A_STAR)
		{
			AStarSearchUpdate();
		}
	}
	else if (!m_found && !m_error)
	{
		Node* under = GetNode(gl::Input::GetMousePositionInGame(window));
		if (under != nullptr)
		{
			under->SetColor(sf::Color(100, 100, 100, 255));

			if ((under->GetState() != eNODE_STATE::START && under->GetState() != eNODE_STATE::END)
			&&  (MouseInfo::GetState() != eTYPE::START && MouseInfo::GetState() != eTYPE::END))
			{
				if (MouseInfo::GetTileType() == eTILE_TYPE::WALL)
				{
					static bool pressed = false;
					if (gl::Input::GetMouseButton(0))
					{
						if (!pressed)
						{
							if (under->GetState() != eNODE_STATE::WALL)
							{
								MouseInfo::ChangeState(eTYPE::BLANK);
							}
							else if (under->GetState() != eNODE_STATE::BLANK)
							{
								MouseInfo::ChangeState(eTYPE::WALL);
							}
							pressed = true;
						}

						under->ChangeState(MouseInfo::GetState() == eTYPE::WALL ? 
						                                   eNODE_STATE::BLANK : eNODE_STATE::WALL);
					}
					else
					{
						pressed = false;
					}
				}
				else
				{
					if (gl::Input::GetMouseButton(0))
					{
						under->ChangeTileType(
							MouseInfo::GetTileType() == eTILE_TYPE::GRASS ? eNODE_PATH_TYPE::GRASS :
						   (MouseInfo::GetTileType() == eTILE_TYPE::SAND ? eNODE_PATH_TYPE::SAND :
						   (MouseInfo::GetTileType() == eTILE_TYPE::WATER ? eNODE_PATH_TYPE::WATER :
							eNODE_PATH_TYPE::NONE)));

						if (under->m_up != nullptr)
							under->m_up->m_downWeight = GetWeight(under->GetTileType());
						if (under->m_right != nullptr)
							under->m_right->m_leftWeight = GetWeight(under->GetTileType());
						if (under->m_down != nullptr)
							under->m_down->m_upWeight = GetWeight(under->GetTileType());
						if (under->m_left != nullptr)
							under->m_left->m_rightWeight = GetWeight(under->GetTileType());
					}
				}
			}
			else
			{
				if (gl::Input::GetMouseButton(0) && MouseInfo::GetState() != eTYPE::START 
				                                 && MouseInfo::GetState() != eTYPE::END)
				{
					MouseInfo::ChangeState(under->GetState() == eNODE_STATE::START ? eTYPE::START 
																				   : eTYPE::END);
				}
				if (gl::Input::GetMouseButton(0))
				{
					if (MouseInfo::GetState() == eTYPE::START
					 && under->GetState() != eNODE_STATE::END)
					{
						if (m_start != nullptr)
						{
							m_start->ChangeState(m_start->GetTempState());
							m_start = under;
							m_start->ChangeState(eNODE_STATE::START);
							m_manager->SetAgentPosition(m_start->GetPosition());
						}

					}
					if (MouseInfo::GetState() == eTYPE::END
					 && under->GetState() != eNODE_STATE::START)
					{
						if (m_end != nullptr)
						{
							m_end->ChangeState(m_end->GetTempState());
							m_end = under;
							m_end->ChangeState(eNODE_STATE::END);
						}

					}
				}
				else
				{
					MouseInfo::ChangeState(eTYPE::NONE);
				}

				
			}
		}

		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				m_nodeGrid[i][j].Update(window);
			}
		}/**/
}
	else if (m_error)
	{
		return false;
	}
	return true;
}

void Grid::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].Render(window);
		}
	}

	if (m_found)
	{
		for (sf::RectangleShape& rec : m_linesToTarget)
		{
			window->draw(rec);
		}
	}

	if(m_showWeghts)
	{
		sf::Text weights;
		weights.setFont(*gl::CFont::GetFont("Numbers"));
		weights.setOutlineColor(sf::Color::White);
		weights.setOutlineThickness(2);
		weights.setFillColor(sf::Color::Black);
		weights.setCharacterSize(10);/**/

		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				if (m_nodeGrid[i][j].m_right != nullptr)
				{
					weights.setString(to_string((int)m_nodeGrid[i][j].m_rightWeight));
					weights.setOrigin({ weights.getGlobalBounds().width / 2, 
					                    weights.getGlobalBounds().height / 2 });
					weights.setPosition((m_nodeGrid[i][j].GetPosition() + 
					                     m_nodeGrid[i][j].m_right->GetPosition() + 
										 m_nodeGrid[i][j].GetSize()) * 0.5f);
					window->draw(weights);
				}
				if (m_nodeGrid[i][j].m_down != nullptr)
				{
					weights.setString(to_string((int)m_nodeGrid[i][j].m_downWeight));
					weights.setOrigin({ weights.getGlobalBounds().width / 2, 
					                    weights.getGlobalBounds().height / 2 });
					weights.setPosition((m_nodeGrid[i][j].GetPosition() + 
					                     m_nodeGrid[i][j].m_down->GetPosition() + 
										 m_nodeGrid[i][j].GetSize()) * 0.5f);
					window->draw(weights);
				}
			}
		}/**/
	}
}

void Grid::Destroy()
{
	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].Destroy();
		}
	}

}



void Grid::RemoveWalls()
{
	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			if (m_nodeGrid[i][j].GetState() != eNODE_STATE::START
			 && m_nodeGrid[i][j].GetState() != eNODE_STATE::END)
			{
				m_nodeGrid[i][j].ChangeState(eNODE_STATE::BLANK);
			}
		}
	}
}

void Grid::RestartSearch()
{
	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].RestartSearch();
		}
	}

	m_isSearching = false;
	m_found = false;
	m_error = false;
	m_searchType = eSEARCH_TYPE::NONE;

	m_order.clear();
	m_i = 0;

	m_current = nullptr;

	m_linesToTarget.clear();

	if (m_manager != nullptr && m_start != nullptr)
	{
		m_manager->SetAgentPosition(m_start->GetPosition());
	}
}

void Grid::RestartAll()
{
	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].RestartAll();
		}
	}

	m_isSearching = false;
	m_found = false;
	m_error = false;
	m_searchType = eSEARCH_TYPE::NONE;

	m_order.clear();
	m_i = 0;

	m_current = nullptr;

	m_linesToTarget.clear();


	if (m_nodeGrid.size() > 1 && m_nodeGrid[0].size() > 1)
	{
		m_nodeGrid[m_nodeGrid.size() / 8][m_nodeGrid[0].size() / 2].ChangeState(eNODE_STATE::START);
		m_start = &m_nodeGrid[m_nodeGrid.size() / 8][m_nodeGrid[0].size() / 2];
		m_nodeGrid[m_nodeGrid.size() * 7 / 8][m_nodeGrid[0].size() / 2].ChangeState(eNODE_STATE::END);
		m_end = &m_nodeGrid[m_nodeGrid.size() * 7 / 8][m_nodeGrid[0].size() / 2];
	}
	if (m_manager != nullptr && m_start != nullptr)
	{
		m_manager->SetAgentPosition(m_start->GetPosition());
	}
}

Node* Grid::GetNode(sf::Vector2i pos)
{
	int x = pos.x / m_cellSize.x;
	int y = pos.y / m_cellSize.y;
	if (x < m_nodeGrid.size() && y < m_nodeGrid[0].size())
	{
		return &m_nodeGrid[x][y];
	}
	else
	{
		return nullptr;
	}
}

bool Grid::GetIsSearching()
{
	return m_isSearching;
}

bool Grid::GetHasFound()
{
	return m_found;
}

bool Grid::GetGotError()
{
	return m_error;
}

std::vector<Node*> Grid::GetPathToEnd()
{
	return m_path;
}

std::vector<std::vector<Node>>* Grid::GetNodeGrid()
{
	return &m_nodeGrid;
}



void Grid::ShowLines(bool active)
{
	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].ShowLines(active);
		}
	}
}

void Grid::ShowWeights(bool active)
{
	m_showWeghts = active;
}



void Grid::CreateLinesToTarget()
{
	m_linesToTarget.clear();
	m_path.clear();

	Node* temp = m_end;
	m_path.push_back(m_end);
	while (temp->GetState() != eNODE_STATE::START)
	{
		sf::Vector2f pos1 = temp->GetPosition() + temp->GetSize() * .5f;
		sf::Vector2f pos2 = temp->m_parent->GetPosition() + temp->GetSize() * .5f;
		sf::Vector2f vec = pos2 - pos1;

		float distance = pow(pow(vec.x, 2) + pow(vec.y, 2), 0.5f);

		m_linesToTarget.push_back(sf::RectangleShape({ distance, 5.0f }));
		m_linesToTarget[m_linesToTarget.size() - 1].setOrigin({ 0, 2.5f });
		m_linesToTarget[m_linesToTarget.size() - 1].setFillColor(sf::Color::Magenta);

		m_linesToTarget[m_linesToTarget.size() - 1].setPosition(pos1);

		float angle = 0;
		if (vec.x != 0)
		{
			angle = atan(vec.y / vec.x) * 180 / 3.1416;

			if (vec.x < 0)
			{
				angle += 180;
			}
			else if (vec.y < 0)
			{
				angle += 360;
			}
		}
		else
		{
			if (vec.y < 0)
			{
				angle = 270;
			}
			else
			{
				angle = 90;
			}
		}

		m_linesToTarget[m_linesToTarget.size() - 1].setRotation(angle);

		temp = temp->m_parent;

		m_path.push_back(temp);
		for (int i = m_path.size() - 1; i > 0; i--)
		{
			Node* t = m_path[i];
			m_path[i] = m_path[i - 1];
			m_path[i - 1] = t;
		}
	}
}



void Grid::BreathFirstSearch()
{
	RestartSearch();

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			if (m_nodeGrid[i][j].GetState() == eNODE_STATE::START)
			{
				m_start = &m_nodeGrid[i][j];
			}
			else if (m_nodeGrid[i][j].GetState() == eNODE_STATE::END)
			{
				m_end = &m_nodeGrid[i][j];
			}
		}
	}

	if (m_start != nullptr && m_end != nullptr)
	{
		if (m_start->m_up != nullptr && m_start->m_up->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_up);
			m_start->m_up->SetParent(m_start);
		}
		if (m_start->m_right != nullptr && m_start->m_right->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_right);
			m_start->m_right->SetParent(m_start);
		}
		if (m_start->m_down != nullptr && m_start->m_down->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_down);
			m_start->m_down->SetParent(m_start);
		}
		if (m_start->m_left != nullptr && m_start->m_left->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_left);
			m_start->m_left->SetParent(m_start);
		}

		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::BREATH_FIRST;
	}
}

void Grid::DepthFirstSearch()
{
	RestartSearch();

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			if (m_nodeGrid[i][j].GetState() == eNODE_STATE::START)
			{
				m_start = &m_nodeGrid[i][j];
			}
			else if (m_nodeGrid[i][j].GetState() == eNODE_STATE::END)
			{
				m_end = &m_nodeGrid[i][j];
			}
		}
	}

	if (m_start != nullptr && m_end != nullptr)
	{
		m_current = m_start;

		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::DEPTH_FIRST;
	}
}

void Grid::DijstraSearch()
{
	RestartSearch();

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			if (m_nodeGrid[i][j].GetState() == eNODE_STATE::START)
			{
				m_start = &m_nodeGrid[i][j];
			}
			else if (m_nodeGrid[i][j].GetState() == eNODE_STATE::END)
			{
				m_end = &m_nodeGrid[i][j];
			}
		}
	}

	if (m_start != nullptr && m_end != nullptr)
	{
		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::DIJSTRA;
	}
}

void Grid::BestFirstSearch()
{
	RestartSearch();

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			if (m_nodeGrid[i][j].GetState() == eNODE_STATE::START)
			{
				m_start = &m_nodeGrid[i][j];
			}
			else if (m_nodeGrid[i][j].GetState() == eNODE_STATE::END)
			{
				m_end = &m_nodeGrid[i][j];
			}
		}
	}

	if (m_start != nullptr && m_end != nullptr)
	{
		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				m_nodeGrid[i][j].m_ucledianDistance = pow(pow(m_end->GetPosition().x - 
				   m_nodeGrid[i][j].GetPosition().x, 2) + pow(m_end->GetPosition().y - 
				   m_nodeGrid[i][j].GetPosition().y, 2), 0.5f);
			}
		}/**/


		if (m_start->m_up != nullptr && m_start->m_up->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_up);
			m_start->m_up->SetParent(m_start);
		}
		if (m_start->m_right != nullptr && m_start->m_right->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_right);
			m_start->m_right->SetParent(m_start);
		}
		if (m_start->m_down != nullptr && m_start->m_down->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_down);
			m_start->m_down->SetParent(m_start);
		}
		if (m_start->m_left != nullptr && m_start->m_left->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_start->m_left);
			m_start->m_left->SetParent(m_start);
		}

		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::BEST_FIRST;
	}
}

void Grid::AStarSearch()
{
	RestartSearch();

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			if (m_nodeGrid[i][j].GetState() == eNODE_STATE::START)
			{
				m_start = &m_nodeGrid[i][j];
			}
			else if (m_nodeGrid[i][j].GetState() == eNODE_STATE::END)
			{
				m_end = &m_nodeGrid[i][j];
			}
		}
	}

	if (m_start != nullptr && m_end != nullptr)
	{
		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				m_nodeGrid[i][j].m_ucledianDistance = pow(
				pow((m_end->GetPosition().x - m_nodeGrid[i][j].GetPosition().x) / m_cellSize.x, 2) 
			  + pow((m_end->GetPosition().y - m_nodeGrid[i][j].GetPosition().y) / m_cellSize.y, 2), 
			                                          0.5f);
			}
		}/**/

		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::A_STAR;
	}
}



bool Grid::BreathFirstSearchUpdate()
{
	if (m_order[m_i]->GetState() != eNODE_STATE::END)
	{
		if (m_order[m_i]->m_up != m_order[m_i]->m_parent && m_order[m_i]->m_up != nullptr
			&& !m_order[m_i]->m_up->m_searched && m_order[m_i]->m_up->m_parent == nullptr
			&& m_order[m_i]->m_up->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[m_i]->m_up);
			m_order[m_i]->m_up->SetParent(m_order[m_i]);
		}
		if (m_order[m_i]->m_right != m_order[m_i]->m_parent && m_order[m_i]->m_right != nullptr
			&& !m_order[m_i]->m_right->m_searched && m_order[m_i]->m_right->m_parent == nullptr
			&& m_order[m_i]->m_right->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[m_i]->m_right);
			m_order[m_i]->m_right->SetParent(m_order[m_i]);
		}
		if (m_order[m_i]->m_down != m_order[m_i]->m_parent && m_order[m_i]->m_down != nullptr
			&& !m_order[m_i]->m_down->m_searched && m_order[m_i]->m_down->m_parent == nullptr
			&& m_order[m_i]->m_down->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[m_i]->m_down);
			m_order[m_i]->m_down->SetParent(m_order[m_i]);
		}
		if (m_order[m_i]->m_left != m_order[m_i]->m_parent && m_order[m_i]->m_left != nullptr
			&& !m_order[m_i]->m_left->m_searched && m_order[m_i]->m_left->m_parent == nullptr
			&& m_order[m_i]->m_left->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[m_i]->m_left);
			m_order[m_i]->m_left->SetParent(m_order[m_i]);
		}
		m_order[m_i]->Searched();
		m_i++;

		if (m_i >= m_order.size())
		{
			m_isSearching = false;
			m_error = true;
		}
	}
	else
	{
		m_isSearching = false;
		m_found = true;
		CreateLinesToTarget();
	}
	return false;
}

bool Grid::DepthFirstSearchUpdate()
{
	while (true)
	{
		if (m_current->m_up != nullptr 
		 && m_current->m_up->GetState() != eNODE_STATE::WALL
		 &&!m_current->m_up->m_searched 
		 && m_current->m_up->GetState() != eNODE_STATE::START)
		{
			m_current->m_up->SetParent(m_current);
			m_current = m_current->m_up;
			break;
		}
		else if (m_current->m_right != nullptr 
		      && m_current->m_right->GetState() != eNODE_STATE::WALL
			  &&!m_current->m_right->m_searched 
			  && m_current->m_right->GetState() != eNODE_STATE::START)
		{
			m_current->m_right->SetParent(m_current);
			m_current = m_current->m_right;
			break;
		}
		else if (m_current->m_down != nullptr 
		      && m_current->m_down->GetState() != eNODE_STATE::WALL
		 	  &&!m_current->m_down->m_searched 
			  && m_current->m_down->GetState() != eNODE_STATE::START)
		{
			m_current->m_down->SetParent(m_current);
			m_current = m_current->m_down;
			break;
		}
		else if (m_current->m_left != nullptr 
		      && m_current->m_left->GetState() != eNODE_STATE::WALL
			  &&!m_current->m_left->m_searched 
			  && m_current->m_left->GetState() != eNODE_STATE::START)
		{
			m_current->m_left->SetParent(m_current);
			m_current = m_current->m_left;
			break;
		}
		else
		{
			if (m_current->m_parent != nullptr)
			{
				m_current = m_current->m_parent;
			}
			else
			{
				m_isSearching = false;
				m_error = true;
				break;
			}
		}
	}


	if (m_current->GetState() == eNODE_STATE::END)
	{
		m_isSearching = false;
		m_found = true;
		CreateLinesToTarget();
		return true;
	}
	else
	{
		m_current->Searched();
	}

	return false;
}

void Grid::DijstraSearchUpdate()
{
	Node* temp = m_start;

	float minWeight = 99999;
	Node* son = nullptr, *father = nullptr;
	float fatherWeight = 0;

	float tempWeight = 0;
	int face = 0;
	while (true)
	{
		if (temp == m_start || temp->m_parent != nullptr)
		{
			if (temp->m_up != nullptr  && temp->m_up->GetState() != eNODE_STATE::WALL
			&& (temp->m_up->m_parent == nullptr || temp->m_up->m_parent == temp)
			&&  temp->m_up->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 1) != 1)
			{
				tempWeight += temp->m_upWeight;
				temp->m_facesSeen |= 1;
				temp = temp->m_up;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 0;
				continue;
			}
			else if (temp->m_right != nullptr  && temp->m_right->GetState() != eNODE_STATE::WALL
				 && (temp->m_right->m_parent == nullptr || temp->m_right->m_parent == temp)
				 &&  temp->m_right->GetState() != eNODE_STATE::START 
				 && (temp->m_facesSeen & 2) != 2)
			{
				tempWeight += temp->m_rightWeight;
				temp->m_facesSeen |= 2;
				temp = temp->m_right;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 1;
				continue;
			}
			else if (temp->m_down != nullptr  && temp->m_down->GetState() != eNODE_STATE::WALL
				 && (temp->m_down->m_parent == nullptr || temp->m_down->m_parent == temp)
				 &&  temp->m_down->GetState() != eNODE_STATE::START 
				 && (temp->m_facesSeen & 4) != 4)
			{
				tempWeight += temp->m_downWeight;
				temp->m_facesSeen |= 4;
				temp = temp->m_down;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 2;
				continue;
			}
			else if (temp->m_left != nullptr  && temp->m_left->GetState() != eNODE_STATE::WALL
				 && (temp->m_left->m_parent == nullptr || temp->m_left->m_parent == temp)
				 &&  temp->m_left->GetState() != eNODE_STATE::START 
				 && (temp->m_facesSeen & 8) != 8)
			{
				tempWeight += temp->m_leftWeight;
				temp->m_facesSeen |= 8;
				temp = temp->m_left;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 3;
				continue;
			}
			else
			{
				if (temp->m_parent != nullptr)
				{
					tempWeight -= temp->m_parentWeight;
					temp = temp->m_parent;
					continue;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			if (tempWeight < minWeight)
			{
				minWeight = tempWeight;
				son = temp;
				father = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : 
				        (face == 2 ? temp->m_up   : (face == 3 ? temp->m_right : nullptr)));
				fatherWeight = face == 0 ? temp->m_down->m_upWeight : 
				              (face == 1 ? temp->m_left->m_rightWeight : 
				              (face == 2 ? temp->m_up->m_downWeight : 
				              (face == 3 ? temp->m_right->m_leftWeight : 0)));
			}

			tempWeight -= face == 0 ? temp->m_down->m_upWeight : 
			             (face == 1 ? temp->m_left->m_rightWeight : 
						 (face == 2 ? temp->m_up->m_downWeight : 
						 (face == 3 ? temp->m_right->m_leftWeight : 0)));
			temp = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : 
			      (face == 2 ? temp->m_up   : (face == 3 ? temp->m_right : nullptr)));

			continue;
		}
	}

	if (son != nullptr && father != nullptr)
	{
		son->m_parent = father;
		if (son->GetState() == eNODE_STATE::END)
		{
			m_isSearching = false;
			m_found = true;
			CreateLinesToTarget();
			return;
		}
		else
		{
			son->m_parentWeight = fatherWeight;
			son->SetColor(sf::Color(150, 150, 150, 255));
		}
	}
	else
	{
		m_isSearching = false;
		m_error = true;
	}



	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].m_searched = false;
			m_nodeGrid[i][j].m_facesSeen = 0;
		}
	}
}

void Grid::BestFirstSearchUpdate()
{
	int index = 0;
	float minDistance = 999999;
	for (int i = 0; i < m_order.size(); i++)
	{
		float d = pow(pow(m_end->GetPosition().x - m_order[i]->GetPosition().x, 2) + 
		          pow(m_end->GetPosition().y - m_order[i]->GetPosition().y, 2), 0.5f);
		if (d < minDistance)
		{
			minDistance = d;
			index = i;
		}
	}

	if (m_order[index]->GetState() != eNODE_STATE::END)
	{
		if (m_order[index]->m_up != m_order[index]->m_parent 
		 && m_order[index]->m_up != nullptr
		 &&!m_order[index]->m_up->m_searched && m_order[index]->m_up->m_parent == nullptr
		 && m_order[index]->m_up->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_up);
			m_order[index]->m_up->SetParent(m_order[index]);
		}
		if (m_order[index]->m_right != m_order[index]->m_parent 
		 && m_order[index]->m_right != nullptr
		 &&!m_order[index]->m_right->m_searched && m_order[index]->m_right->m_parent == nullptr
		 && m_order[index]->m_right->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_right);
			m_order[index]->m_right->SetParent(m_order[index]);
		}
		if (m_order[index]->m_down != m_order[index]->m_parent 
		 && m_order[index]->m_down != nullptr
		 &&!m_order[index]->m_down->m_searched && m_order[index]->m_down->m_parent == nullptr
		 && m_order[index]->m_down->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_down);
			m_order[index]->m_down->SetParent(m_order[index]);
		}
		if (m_order[index]->m_left != m_order[index]->m_parent 
		 && m_order[index]->m_left != nullptr
		 &&!m_order[index]->m_left->m_searched && m_order[index]->m_left->m_parent == nullptr
		 && m_order[index]->m_left->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_left);
			m_order[index]->m_left->SetParent(m_order[index]);
		}
		m_order[index]->Searched();
		m_order.erase(m_order.begin() + index);

		if (m_order.size() == 0)
		{
			m_isSearching = false;
			m_error = true;
		}
	}
	else
	{
		m_isSearching = false;
		m_found = true;
		CreateLinesToTarget();
	}
}

void Grid::AStarSearchUpdate()
{
	Node* temp = m_start;

	float minWeight = 99999;
	Node* son = nullptr, * father = nullptr;
	float fatherWeight = 0;

	float tempWeight = 0;
	int face = 0;
	while (true)
	{
		if (temp == m_start || temp->m_parent != nullptr)
		{
			if (temp->m_up != nullptr && temp->m_up->GetState() != eNODE_STATE::WALL
				&& (temp->m_up->m_parent == nullptr || temp->m_up->m_parent == temp)
				&& temp->m_up->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 1) != 1)
			{
				tempWeight += temp->m_upWeight;
				temp->m_facesSeen |= 1;
				temp = temp->m_up;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 0;
				continue;
			}
			else if (temp->m_right != nullptr && temp->m_right->GetState() != eNODE_STATE::WALL
				&& (temp->m_right->m_parent == nullptr || temp->m_right->m_parent == temp)
				&& temp->m_right->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 2) != 2)
			{
				tempWeight += temp->m_rightWeight;
				temp->m_facesSeen |= 2;
				temp = temp->m_right;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 1;
				continue;
			}
			else if (temp->m_down != nullptr && temp->m_down->GetState() != eNODE_STATE::WALL
				&& (temp->m_down->m_parent == nullptr || temp->m_down->m_parent == temp)
				&& temp->m_down->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 4) != 4)
			{
				tempWeight += temp->m_downWeight;
				temp->m_facesSeen |= 4;
				temp = temp->m_down;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 2;
				continue;
			}
			else if (temp->m_left != nullptr && temp->m_left->GetState() != eNODE_STATE::WALL
				&& (temp->m_left->m_parent == nullptr || temp->m_left->m_parent == temp)
				&& temp->m_left->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 8) != 8)
			{
				tempWeight += temp->m_leftWeight;
				temp->m_facesSeen |= 8;
				temp = temp->m_left;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(200, 200, 200, 255));
				face = 3;
				continue;
			}
			else
			{
				if (temp->m_parent != nullptr)
				{
					tempWeight -= temp->m_parentWeight;
					temp = temp->m_parent;
					continue;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			if (tempWeight + temp->m_ucledianDistance < minWeight)
			{
				minWeight = tempWeight + temp->m_ucledianDistance;
				son = temp;
				father = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : 
				        (face == 2 ? temp->m_up   : (face == 3 ? temp->m_right : nullptr)));
				fatherWeight = face == 0 ? temp->m_down->m_upWeight : 
				              (face == 1 ? temp->m_left->m_rightWeight : 
							  (face == 2 ? temp->m_up->m_downWeight : 
							  (face == 3 ? temp->m_right->m_leftWeight : 0)));
			}

			tempWeight -= face == 0 ? temp->m_down->m_upWeight : 
			             (face == 1 ? temp->m_left->m_rightWeight : 
						 (face == 2 ? temp->m_up->m_downWeight : 
						 (face == 3 ? temp->m_right->m_leftWeight : 0)));
			temp = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : 
			      (face == 2 ? temp->m_up   : (face == 3 ? temp->m_right : nullptr)));

			continue;
		}
	}

	if (son != nullptr && father != nullptr)
	{
		son->m_parent = father;
		if (son->GetState() == eNODE_STATE::END)
		{
			m_isSearching = false;
			m_found = true;
			CreateLinesToTarget();
			return;
		}
		else
		{
			son->m_parentWeight = fatherWeight;
			son->SetColor(sf::Color(150, 150, 150, 255));
		}
	}
	else
	{
		m_isSearching = false;
		m_error = true;
	}

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].m_searched = false;
			m_nodeGrid[i][j].m_facesSeen = 0;
		}
	}
}

float Grid::GetWeight(eNODE_PATH_TYPE type)
{
	if (type == eNODE_PATH_TYPE::GRASS)
	{
		return 1.0f;
	}
	else if (type == eNODE_PATH_TYPE::SAND)
	{
		return 2.0f;
	}
	else if (type == eNODE_PATH_TYPE::WATER)
	{
		return 3.0f;
	}
	return 1.0f;
}
