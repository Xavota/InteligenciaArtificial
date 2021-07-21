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
	for (std::list<std::list<Node>>::iterator iti = m_nodeGrid.begin(); iti != m_nodeGrid.end(); iti++)
	{
		for (std::list<Node>::iterator itj = iti->begin(); itj != iti->end(); itj++)
		{
			itj->Update(window);
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
