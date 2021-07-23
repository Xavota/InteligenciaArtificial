#include "Grid.h"

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
				GetFromDoubleList(&m_nodeGrid, i, j)->m_left = GetFromDoubleList(&m_nodeGrid, i - 1, j);
				GetFromDoubleList(&m_nodeGrid, i - 1, j)->m_right = GetFromDoubleList(&m_nodeGrid, i, j);
			}
			if (j > 0)
			{
				GetFromDoubleList(&m_nodeGrid, i, j)->m_up = GetFromDoubleList(&m_nodeGrid, i, j - 1);
				GetFromDoubleList(&m_nodeGrid, i, j - 1)->m_down = GetFromDoubleList(&m_nodeGrid, i, j);
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

void Grid::StartSearch()
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

	Node* temp = m_order[i];
	while (temp->GetState() != eNODE_STATE::START)
	{
		sf::Vector2f pos1 = temp->GetPosition() + temp->GetSize() * .5f;
		sf::Vector2f pos2 = temp->m_parent->GetPosition() + temp->GetSize() * .5f;
		sf::Vector2f vec = pos2 - pos1;

		float distance = pow(pow(vec.x, 2) + pow(vec.y, 2), 0.5f);

		m_linesToTarget.push_back(sf::RectangleShape({distance, 2.0f}));
		m_linesToTarget[m_linesToTarget.size() - 1].setOrigin({0, 1.0f});
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
