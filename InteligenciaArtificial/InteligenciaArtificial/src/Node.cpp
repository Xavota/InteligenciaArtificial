#include "Node.h"
#include "Globals.h"
#include "MouseInfo.h"

std::map<eNODE_STATE, sf::Color> Node::m_colors;
Node::Node(sf::Vector2f pos, sf::Vector2f size)
{
	Init(pos, size);
}

Node::Node(sf::Vector2f pos, sf::Vector2f size, eNODE_PATH_TYPE initState, bool wall)
{
	Init(pos, size,  initState, wall);
}

Node::~Node()
{
}

void Node::Init(sf::Vector2f pos, sf::Vector2f size)
{
	if (m_colors.size() == 0)
	{
		for (int i = 0; i < (int)eNODE_STATE::COUNT; i++)
		{
			switch ((eNODE_STATE)i)
			{
			case eNODE_STATE::BLANK:
				m_colors[(eNODE_STATE)i] = sf::Color::White;
				break;
			case eNODE_STATE::WALL:
				m_colors[(eNODE_STATE)i] = sf::Color::White;
				break;
			case eNODE_STATE::START:
				m_colors[(eNODE_STATE)i] = sf::Color::Red;
				break;
			case eNODE_STATE::END:
				m_colors[(eNODE_STATE)i] = sf::Color::Green;
				break;
			}
		}
	}

	m_shape.setPosition(pos);
	m_shape.setSize(size);
	m_shape.setFillColor(sf::Color::White);
	m_shape.setOutlineThickness(2.0f);
	m_shape.setOutlineColor(sf::Color::Black);

	m_wall.setPosition(pos);
	m_wall.setSize(size);
	m_wall.setTexture(gl::CTexture::GetTexture("Wall"));
	m_wall.setTextureRect({352, 0, 32, 32});

	m_state = eNODE_STATE::BLANK;
}

void Node::Init(sf::Vector2f pos, sf::Vector2f size, eNODE_PATH_TYPE initState, bool wall)
{
	Init(pos, size);

	m_pathType = initState;

	if (m_pathType == eNODE_PATH_TYPE::GRASS)
	{
		m_shape.setTexture(gl::CTexture::GetTexture("Grass"));
		m_shape.setTextureRect({800, 192, 32, 32});
	}
	else if (m_pathType == eNODE_PATH_TYPE::WATER)
	{
		m_shape.setTexture(gl::CTexture::GetTexture("Water"));
		m_shape.setTextureRect({ 256, 192, 32, 32 });
	}
	else if (m_pathType == eNODE_PATH_TYPE::SAND)
	{
		m_shape.setTexture(gl::CTexture::GetTexture("Sand"));
		m_shape.setTextureRect({ 0, 0, 32, 32 });
	}

	if (wall)
		m_state = eNODE_STATE::WALL;
}

void Node::Update(sf::RenderWindow* window)
{
	m_shape.setFillColor(m_colors[m_state]);
}

void Node::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);

	if (m_state == eNODE_STATE::WALL)
	{
		window->draw(m_wall);
	}
}

void Node::Destroy()
{
}


/* Editor */

void Node::ChangeState(eNODE_STATE state)
{
	m_state = state;
	m_shape.setFillColor(m_colors[m_state]);
	if (state == eNODE_STATE::BLANK)
	{
		m_tempSate = m_state;
	}
	else if (state == eNODE_STATE::WALL)
	{
		m_tempSate = m_state;
	}
}

void Node::ChangeTempState(eNODE_STATE state)
{
	m_tempSate = state;
}

eNODE_STATE Node::GetState()
{
	return m_state;
}

eNODE_STATE Node::GetTempState()
{
	return m_tempSate;
}


/* Search */

sf::Vector2f Node::GetPosition()
{
	return m_shape.getPosition();
}

sf::Vector2f Node::GetSize()
{
	return m_shape.getSize();
}

void Node::SetColor(sf::Color color)
{
	m_shape.setFillColor(color);
}

void Node::SetParent(Node* parent)
{
	m_parent = parent;
	if (m_state != eNODE_STATE::END)
	{
		//SetColor(sf::Color(127, 127, 255, 255));
		SetColor(sf::Color(200, 200, 200, 255));
	}
}

void Node::Searched()
{
	m_searched = true;
	SetColor(sf::Color(150, 150, 150, 255));
}

void Node::RestartSearch()
{
	m_parent = nullptr;
	m_parentWeight = 0;
	m_shape.setFillColor(m_colors[m_state]);
	m_searched = false;
	m_facesSeen = 0;
	m_ucledianDistance = 0;
}

void Node::RestartAll()
{
	RestartSearch();
	m_state = eNODE_STATE::BLANK;
	m_shape.setFillColor(m_colors[m_state]);
}

void Node::ShowLines(bool active)
{
	if (active)
	{
		m_shape.setOutlineThickness(2.0f);
	}
	else
	{
		m_shape.setOutlineThickness(0);
	}
}
