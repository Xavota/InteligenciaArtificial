#include "Grid.h"
#include "Globals.h"

Grid::Grid(sf::Vector2i tiles, sf::Vector2f size)
{
	Init(tiles, size);
}

void Grid::Init(sf::Vector2i tiles, sf::Vector2f size)
{
	/*for (int i = 0; i < tiles.x; i++)
	{
		m_nodeGrid.push_back(std::list<Node>());
		for (int j = 0; j < tiles.y; j++)
		{
			GetFromList(&m_nodeGrid, i)->push_back(Node({ ((float)rect.width / tiles.x) * i, ((float)rect.height / tiles.y) * j },
										 { ((float)rect.width / tiles.x),     ((float)rect.height / tiles.y) }));

			if (i > 0)
			{
				int weight = rand() % 10;
				Node * temp = GetFromDoubleList(&m_nodeGrid, i, j);
				Node * temp2 = GetFromDoubleList(&m_nodeGrid, i - 1, j);
				temp->m_left = temp2;
				temp->m_leftWeight = weight;
				temp2->m_right = temp;
				temp2->m_rightWeight = weight;
			}
			if (j > 0)
			{
				int weight = rand() % 10;
				Node* temp = GetFromDoubleList(&m_nodeGrid, i, j);
				Node* temp2 = GetFromDoubleList(&m_nodeGrid, i, j - 1);
				temp->m_up = temp2;
				temp->m_upWeight = weight;
				temp2->m_down = temp;
				temp2->m_downWeight = weight;
			}
		}
	}

	GetFromDoubleList(&m_nodeGrid, 3, 10)->ChangeState(eNODE_STATE::START);
	GetFromDoubleList(&m_nodeGrid, 17, 10)->ChangeState(eNODE_STATE::END);*/

	m_nodeGrid.clear();
	for (int i = 0; i < tiles.x; i++)
	{
		m_nodeGrid.push_back(std::vector<Node>());
		for (int j = 0; j < tiles.y; j++)
		{
			//m_nodeGrid[i].push_back(Node({ ((float)rect.width / tiles.x) * i, ((float)rect.height / tiles.y) * j },
			//	{ ((float)rect.width / tiles.x),     ((float)rect.height / tiles.y) }));
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
	m_nodeGrid[tiles.x * 7 / 8][tiles.y / 2].ChangeState(eNODE_STATE::END);
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
		/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
		{
			for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
			{
				itj->Update(window);
			}
		}/**/
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
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->Render(window);
		}
	}/**/

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
		/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
		{
			for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
			{
				if (itj->m_right != nullptr)
				{
					weights.setString(to_string((int)itj->m_rightWeight));
					weights.setOrigin({weights.getGlobalBounds().width / 2, weights.getGlobalBounds().height / 2});
					weights.setPosition((itj->GetPosition() + itj->m_right->GetPosition() + itj->GetSize()) * 0.5f);
					window->draw(weights);
				}
				if (itj->m_down != nullptr)
				{
					weights.setString(to_string((int)itj->m_downWeight));
					weights.setOrigin({ weights.getGlobalBounds().width / 2, weights.getGlobalBounds().height / 2 });
					weights.setPosition((itj->GetPosition() + itj->m_down->GetPosition() + itj->GetSize()) * 0.5f);
					window->draw(weights);
				}
			}
		}/**/

		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				if (m_nodeGrid[i][j].m_right != nullptr)
				{
					weights.setString(to_string((int)m_nodeGrid[i][j].m_rightWeight));
					weights.setOrigin({ weights.getGlobalBounds().width / 2, weights.getGlobalBounds().height / 2 });
					weights.setPosition((m_nodeGrid[i][j].GetPosition() + m_nodeGrid[i][j].m_right->GetPosition() + m_nodeGrid[i][j].GetSize()) * 0.5f);
					window->draw(weights);
				}
				if (m_nodeGrid[i][j].m_down != nullptr)
				{
					weights.setString(to_string((int)m_nodeGrid[i][j].m_downWeight));
					weights.setOrigin({ weights.getGlobalBounds().width / 2, weights.getGlobalBounds().height / 2 });
					weights.setPosition((m_nodeGrid[i][j].GetPosition() + m_nodeGrid[i][j].m_down->GetPosition() + m_nodeGrid[i][j].GetSize()) * 0.5f);
					window->draw(weights);
				}
			}
		}/**/
	}
}

void Grid::Destroy()
{
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->Destroy();
		}
	}/**/

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].Destroy();
		}
	}

}

void Grid::BreathFirstSearch()
{
	RestartSearch();
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			if (itj->GetState() == eNODE_STATE::START)
			{
				m_start = &*itj;
			}
			else if (itj->GetState() == eNODE_STATE::END)
			{
				m_end = &*itj;
			}
		}
	}/**/

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
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			if (itj->GetState() == eNODE_STATE::START)
			{
				m_start = &*itj;
			}
			else if (itj->GetState() == eNODE_STATE::END)
			{
				m_end = &*itj;
			}
		}
	}/**/

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
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			if (itj->GetState() == eNODE_STATE::START)
			{
				m_start = &*itj;
			}
			else if (itj->GetState() == eNODE_STATE::END)
			{
				m_end = &*itj;
			}
		}
	}/**/

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
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			if (itj->GetState() == eNODE_STATE::START)
			{
				m_start = &*itj;
			}
			else if (itj->GetState() == eNODE_STATE::END)
			{
				m_end = &*itj;
			}
		}
	}/**/

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
		/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
		{
			for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
			{
				itj->m_ucledianDistance = pow(pow(m_end->GetPosition().x - itj->GetPosition().x, 2) + pow(m_end->GetPosition().y - itj->GetPosition().y, 2), 0.5f);
			}
		}/**/

		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				m_nodeGrid[i][j].m_ucledianDistance = pow(pow(m_end->GetPosition().x - m_nodeGrid[i][j].GetPosition().x, 2) + pow(m_end->GetPosition().y - m_nodeGrid[i][j].GetPosition().y, 2), 0.5f);
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
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			if (itj->GetState() == eNODE_STATE::START)
			{
				m_start = &*itj;
			}
			else if (itj->GetState() == eNODE_STATE::END)
			{
				m_end = &*itj;
			}
		}
	}/**/

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
		/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
		{
			for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
			{
				itj->m_ucledianDistance = pow(pow(m_end->GetPosition().x - itj->GetPosition().x, 2) + pow(m_end->GetPosition().y - itj->GetPosition().y, 2), 0.5f);
			}
		}/**/

		for (int i = 0; i < m_nodeGrid.size(); i++)
		{
			for (int j = 0; j < m_nodeGrid[i].size(); j++)
			{
				m_nodeGrid[i][j].m_ucledianDistance = pow(pow(m_end->GetPosition().x - m_nodeGrid[i][j].GetPosition().x, 2) + pow(m_end->GetPosition().y - m_nodeGrid[i][j].GetPosition().y, 2), 0.5f);
			}
		}/**/

		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::A_STAR;
	}
}

std::list<Node>* Grid::GetFromList(std::list<std::list<Node>>* list, int i)
{
	int in = 0;
	for (std::list<std::list<Node>>::iterator iti = list->begin(); iti != list->end(); iti++)
	{
		if (in == i)
		{
			return &*iti;
		}
		in++;
	}
	return nullptr;
}

Node* Grid::GetFromDoubleList(std::list<std::list<Node>>* list, int i, int j)
{
	int in = 0, jn = 0;
	for (std::list<std::list<Node>>::iterator iti = list->begin(); iti != list->end(); iti++)
	{
		jn = 0;
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			if (in == i && jn == j)
			{
				return &*itj;
			}
			jn++;
		}
		in++;
	}
	return nullptr;
}

void Grid::RestartSearch()
{
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->RestartSearch();
		}
	}/**/

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].RestartSearch();
		}
	}

	m_isSearching = false;
	m_start = nullptr;
	m_end = nullptr;
	m_found = false;
	m_error = false;
	m_searchType = eSEARCH_TYPE::NONE;

	m_order.clear();
	m_i = 0;

	m_current = nullptr;

	m_linesToTarget.clear();
}

void Grid::RestartAll()
{
	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->RestartAll();
		}
	}/**/

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].RestartAll();
		}
	}

	m_isSearching = false;
	m_start = nullptr;
	m_end = nullptr;
	m_found = false;
	m_error = false;
	m_searchType = eSEARCH_TYPE::NONE;

	m_order.clear();
	m_i = 0;

	m_current = nullptr;

	m_linesToTarget.clear();


	m_nodeGrid[m_nodeGrid.size() / 8][m_nodeGrid[0].size() / 2].ChangeState(eNODE_STATE::START);
	m_nodeGrid[m_nodeGrid.size() * 7 / 8][m_nodeGrid[0].size() / 2].ChangeState(eNODE_STATE::END);
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

	Node* temp = m_end;
	while (temp->GetState() != eNODE_STATE::START)
	{
		sf::Vector2f pos1 = temp->GetPosition() + temp->GetSize() * .5f;
		sf::Vector2f pos2 = temp->m_parent->GetPosition() + temp->GetSize() * .5f;
		sf::Vector2f vec = pos2 - pos1;

		float distance = pow(pow(vec.x, 2) + pow(vec.y, 2), 0.5f);

		m_linesToTarget.push_back(sf::RectangleShape({distance, 5.0f}));
		m_linesToTarget[m_linesToTarget.size() - 1].setOrigin({0, 2.5f});
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
		if (m_current->m_up != nullptr && m_current->m_up->GetState() != eNODE_STATE::WALL
		 && !m_current->m_up->m_searched && m_current->m_up->GetState() != eNODE_STATE::START)
		{
			m_current->m_up->SetParent(m_current);
			m_current = m_current->m_up;
			break;
		}
		else if (m_current->m_right != nullptr && m_current->m_right->GetState() != eNODE_STATE::WALL
			&& !m_current->m_right->m_searched && m_current->m_right->GetState() != eNODE_STATE::START)
		{
			m_current->m_right->SetParent(m_current);
			m_current = m_current->m_right;
			break;
		}
		else if (m_current->m_down != nullptr && m_current->m_down->GetState() != eNODE_STATE::WALL
			&& !m_current->m_down->m_searched && m_current->m_down->GetState() != eNODE_STATE::START)
		{
			m_current->m_down->SetParent(m_current);
			m_current = m_current->m_down;
			break;
		}
		else if (m_current->m_left != nullptr && m_current->m_left->GetState() != eNODE_STATE::WALL
			&& !m_current->m_left->m_searched && m_current->m_left->GetState() != eNODE_STATE::START)
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
					temp->SetColor(sf::Color(127, 127, 255, 255));
				face = 0;
				continue;
			}
			else if (temp->m_right != nullptr  && temp->m_right->GetState() != eNODE_STATE::WALL
				 && (temp->m_right->m_parent == nullptr || temp->m_right->m_parent == temp)
				 &&  temp->m_right->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 2) != 2)
			{
				tempWeight += temp->m_rightWeight;
				temp->m_facesSeen |= 2;
				temp = temp->m_right;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(127, 127, 255, 255));
				face = 1;
				continue;
			}
			else if (temp->m_down != nullptr  && temp->m_down->GetState() != eNODE_STATE::WALL
				 && (temp->m_down->m_parent == nullptr || temp->m_down->m_parent == temp)
				 &&  temp->m_down->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 4) != 4)
			{
				tempWeight += temp->m_downWeight;
				temp->m_facesSeen |= 4;
				temp = temp->m_down;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(127, 127, 255, 255));
				face = 2;
				continue;
			}
			else if (temp->m_left != nullptr  && temp->m_left->GetState() != eNODE_STATE::WALL
				 && (temp->m_left->m_parent == nullptr || temp->m_left->m_parent == temp)
				 &&  temp->m_left->GetState() != eNODE_STATE::START && (temp->m_facesSeen & 8) != 8)
			{
				tempWeight += temp->m_leftWeight;
				temp->m_facesSeen |= 8;
				temp = temp->m_left;
				temp->m_searched = true;
				if (temp->m_parent == nullptr && temp->GetState() != eNODE_STATE::END)
					temp->SetColor(sf::Color(127, 127, 255, 255));
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
				father = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : (face == 2 ? temp->m_up : (face == 3 ? temp->m_right : nullptr)));
				fatherWeight = face == 0 ? temp->m_downWeight : (face == 1 ? temp->m_leftWeight : (face == 2 ? temp->m_upWeight : (face == 3 ? temp->m_rightWeight : 0)));
			}

			tempWeight -= face == 0 ? temp->m_downWeight : (face == 1 ? temp->m_leftWeight : (face == 2 ? temp->m_upWeight : (face == 3 ? temp->m_rightWeight : 0)));
			temp = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : (face == 2 ? temp->m_up : (face == 3 ? temp->m_right : nullptr)));

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
			son->SetColor(sf::Color::Blue);
		}
	}
	else
	{
		m_isSearching = false;
		m_error = true;
	}


	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->m_searched = false;
			itj->m_facesSeen = 0;
		}
	}/**/

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
		float d = pow(pow(m_end->GetPosition().x - m_order[i]->GetPosition().x, 2) + pow(m_end->GetPosition().y - m_order[i]->GetPosition().y, 2), 0.5f);
		if (d < minDistance)
		{
			minDistance = d;
			index = i;
		}
	}

	if (m_order[index]->GetState() != eNODE_STATE::END)
	{
		if (m_order[index]->m_up != m_order[index]->m_parent && m_order[index]->m_up != nullptr
			&& !m_order[index]->m_up->m_searched && m_order[index]->m_up->m_parent == nullptr
			&& m_order[index]->m_up->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_up);
			m_order[index]->m_up->SetParent(m_order[index]);
		}
		if (m_order[index]->m_right != m_order[index]->m_parent && m_order[index]->m_right != nullptr
			&& !m_order[index]->m_right->m_searched && m_order[index]->m_right->m_parent == nullptr
			&& m_order[index]->m_right->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_right);
			m_order[index]->m_right->SetParent(m_order[index]);
		}
		if (m_order[index]->m_down != m_order[index]->m_parent && m_order[index]->m_down != nullptr
			&& !m_order[index]->m_down->m_searched && m_order[index]->m_down->m_parent == nullptr
			&& m_order[index]->m_down->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[index]->m_down);
			m_order[index]->m_down->SetParent(m_order[index]);
		}
		if (m_order[index]->m_left != m_order[index]->m_parent && m_order[index]->m_left != nullptr
			&& !m_order[index]->m_left->m_searched && m_order[index]->m_left->m_parent == nullptr
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
					temp->SetColor(sf::Color(127, 127, 255, 255));
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
					temp->SetColor(sf::Color(127, 127, 255, 255));
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
					temp->SetColor(sf::Color(127, 127, 255, 255));
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
					temp->SetColor(sf::Color(127, 127, 255, 255));
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
				father = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : (face == 2 ? temp->m_up : (face == 3 ? temp->m_right : nullptr)));
				fatherWeight = face == 0 ? temp->m_downWeight : (face == 1 ? temp->m_leftWeight : (face == 2 ? temp->m_upWeight : (face == 3 ? temp->m_rightWeight : 0)));
			}

			tempWeight -= face == 0 ? temp->m_downWeight : (face == 1 ? temp->m_leftWeight : (face == 2 ? temp->m_upWeight : (face == 3 ? temp->m_rightWeight : 0)));
			temp = face == 0 ? temp->m_down : (face == 1 ? temp->m_left : (face == 2 ? temp->m_up : (face == 3 ? temp->m_right : nullptr)));

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
			son->SetColor(sf::Color::Blue);
		}
	}
	else
	{
		m_isSearching = false;
		m_error = true;
	}


	/*for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->m_searched = false;
			itj->m_facesSeen = 0;
		}
	}/**/

	for (int i = 0; i < m_nodeGrid.size(); i++)
	{
		for (int j = 0; j < m_nodeGrid[i].size(); j++)
		{
			m_nodeGrid[i][j].m_searched = false;
			m_nodeGrid[i][j].m_facesSeen = 0;
		}
	}
}
