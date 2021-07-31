#include "Node.h"
#include "Globals.h"
#include "MouseInfo.h"

std::map<eNODE_STATE, sf::Color> Node::m_colors;
Node::Node(sf::Vector2f pos, sf::Vector2f size)
{
	Init(pos, size);
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
				m_colors[(eNODE_STATE)i] = sf::Color(100, 100, 100);
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

	m_state = eNODE_STATE::BLANK;
}

void Node::Update(sf::RenderWindow* window)
{
	m_shape.setFillColor(m_colors[m_state]);
	sf::Vector2i mousePos = gl::Input::GetMousePositionInGame(window);
	if (mousePos.x >= m_shape.getPosition().x
		&& mousePos.x <= m_shape.getPosition().x + m_shape.getSize().x
		&& mousePos.y >= m_shape.getPosition().y
		&& mousePos.y <= m_shape.getPosition().y + m_shape.getSize().y)
	{
		m_shape.setFillColor(m_shape.getFillColor() - sf::Color(30, 30, 30, 0));
		if (gl::Input::GetMouseButtonDown(0))
		{
			if (m_state == eNODE_STATE::BLANK)
			{
				MouseInfo::m_state = eTYPE::WALL;
			}
			else if (m_state == eNODE_STATE::WALL)
			{
				MouseInfo::m_state = eTYPE::BLANK;
			}
			else if (m_state == eNODE_STATE::START)
			{
				MouseInfo::m_state = eTYPE::START;
			}
			else if (m_state == eNODE_STATE::END)
			{
				MouseInfo::m_state = eTYPE::END;
			}
		}

		if (gl::Input::GetMouseButton(0))
		{
			MouseInfo::ChageNode(this);
		}
	}/**/
}

void Node::Render(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

void Node::Destroy()
{
}

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
		SetColor(sf::Color(127, 127, 255, 255));
	}
}

void Node::Searched()
{
	m_searched = true;
	SetColor(sf::Color(0, 0, 255, 255));
}

void Node::RestartSearch()
{
	m_parent = nullptr;
	m_shape.setFillColor(m_colors[m_state]);
	m_searched = false;
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
