#include "Grid.h"
#include "Globals.h"

Grid::Grid(sf::IntRect rect, sf::Vector2i tiles)
{
	Init(rect, tiles);
}

void Grid::Init(sf::IntRect rect, sf::Vector2i tiles)
{
	for (int i = 0; i < tiles.x; i++)
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
	GetFromDoubleList(&m_nodeGrid, 17, 10)->ChangeState(eNODE_STATE::END);
}

void Grid::Update(sf::RenderWindow* window)
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
	}
	else if (!m_found)
	{
		for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
		{
			for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
			{
				itj->Update(window);
			}
		}
	}

}

void Grid::Render(sf::RenderWindow* window)
{
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->Render(window);
		}
	}

	if (m_found)
	{
		for (sf::RectangleShape& rec : m_linesToTarget)
		{
			window->draw(rec);
		}
	}

	sf::Text weights;
	weights.setFont(*gl::CFont::GetFont("Numbers"));
	weights.setOutlineColor(sf::Color::White);
	weights.setOutlineThickness(2);
	weights.setFillColor(sf::Color::Black);
	weights.setCharacterSize(15);
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
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
	}
}

void Grid::Destroy()
{
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->Destroy();
		}
	}
}

void Grid::BreathFirstSearch()
{
	RestartSearch();
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
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
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
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
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
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
	}

	if (m_start != nullptr && m_end != nullptr)
	{
		m_paths.push_back(std::vector<sUnion>());
		m_paths[0].push_back(sUnion{nullptr, 0, m_start});

		m_isSearching = true;
		m_searchType = eSEARCH_TYPE::DIJSTRA;
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
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->RestartSearch();
		}
	}
	m_isSearching = false;
	m_found = false;
	m_order.clear();
	m_start = nullptr;
	m_end = nullptr;
	i = 0;
	m_linesToTarget.clear();
}

void Grid::RestartAll()
{
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->RestartAll();
		}
	}
	m_isSearching = false;
	m_found = false;
	m_order.clear();
	m_start = nullptr;
	m_end = nullptr;
	i = 0;
	m_linesToTarget.clear();


	GetFromDoubleList(&m_nodeGrid, 3, 10)->ChangeState(eNODE_STATE::START);
	GetFromDoubleList(&m_nodeGrid, 17, 10)->ChangeState(eNODE_STATE::END);
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
	if (m_order[i]->GetState() != eNODE_STATE::END)
	{
		if (m_order[i]->m_up != m_order[i]->m_parent && m_order[i]->m_up != nullptr
			&& !m_order[i]->m_up->m_searched && m_order[i]->m_up->m_parent == nullptr
			&& m_order[i]->m_up->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[i]->m_up);
			m_order[i]->m_up->SetParent(m_order[i]);
		}
		if (m_order[i]->m_right != m_order[i]->m_parent && m_order[i]->m_right != nullptr
			&& !m_order[i]->m_right->m_searched && m_order[i]->m_right->m_parent == nullptr
			&& m_order[i]->m_right->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[i]->m_right);
			m_order[i]->m_right->SetParent(m_order[i]);
		}
		if (m_order[i]->m_down != m_order[i]->m_parent && m_order[i]->m_down != nullptr
			&& !m_order[i]->m_down->m_searched && m_order[i]->m_down->m_parent == nullptr
			&& m_order[i]->m_down->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[i]->m_down);
			m_order[i]->m_down->SetParent(m_order[i]);
		}
		if (m_order[i]->m_left != m_order[i]->m_parent && m_order[i]->m_left != nullptr
			&& !m_order[i]->m_left->m_searched && m_order[i]->m_left->m_parent == nullptr
			&& m_order[i]->m_left->GetState() != eNODE_STATE::WALL)
		{
			m_order.push_back(m_order[i]->m_left);
			m_order[i]->m_left->SetParent(m_order[i]);
		}
		m_order[i]->Searched();
		i++;

		if (i >= m_order.size())
		{
			m_isSearching = false;
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
			m_current->m_up->m_parent = m_current;
			m_current = m_current->m_up;
			break;
		}
		else if (m_current->m_right != nullptr && m_current->m_right->GetState() != eNODE_STATE::WALL
			&& !m_current->m_right->m_searched && m_current->m_right->GetState() != eNODE_STATE::START)
		{
			m_current->m_right->m_parent = m_current;
			m_current = m_current->m_right;
			break;
		}
		else if (m_current->m_down != nullptr && m_current->m_down->GetState() != eNODE_STATE::WALL
			&& !m_current->m_down->m_searched && m_current->m_down->GetState() != eNODE_STATE::START)
		{
			m_current->m_down->m_parent = m_current;
			m_current = m_current->m_down;
			break;
		}
		else if (m_current->m_left != nullptr && m_current->m_left->GetState() != eNODE_STATE::WALL
			&& !m_current->m_left->m_searched && m_current->m_left->GetState() != eNODE_STATE::START)
		{
			m_current->m_left->m_parent = m_current;
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
		m_current->m_searched = true;
		m_current->SetColor(sf::Color::Blue);
	}

	return false;
}

void Grid::DijstraSearchUpdate()
{
	/*int im = 0, jm = 0, dm = 0;
	float wm = 4294967295;

	for (int i = 0; i < m_paths.size(); i++)
	{
		float lineWeight = 0;
		for (int j = 0; j < m_paths[i].size(); j++)
		{
			if (m_paths[i][j].m_end->m_left != nullptr && lineWeight + m_paths[i][j].m_end->m_leftWeight < wm)
			{
				wm = lineWeight + m_paths[i][j].m_end->m_leftWeight;
			}
		}
	}*/

	Node* temp = m_start;

	float minWeight = 999;
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


	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->m_searched = false;
			itj->m_facesSeen = 0;
		}
	}
}
