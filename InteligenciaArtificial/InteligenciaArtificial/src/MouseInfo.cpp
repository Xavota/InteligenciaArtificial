#include "MouseInfo.h"
#include "Globals.h"
#include <iostream>
#include <string>

eTYPE MouseInfo::m_state = eTYPE::WALL;
eTILE_TYPE MouseInfo::m_tileType = eTILE_TYPE::WALL;
Node* MouseInfo::m_currentNode = nullptr;
Node* MouseInfo::m_lastNode = nullptr;

void MouseInfo::ChageNode(Node* newNode)
{
	if (newNode == nullptr)
	{
		m_state = eTYPE::NONE;
		m_currentNode = nullptr;
		m_lastNode = nullptr;
		return;
	}

	if (newNode != m_currentNode)
	{
		m_currentNode = newNode;
		if (m_state == eTYPE::BLANK)
		{
			if (m_currentNode->GetState() != eNODE_STATE::START && m_currentNode->GetState() != eNODE_STATE::END)
			{
				m_currentNode->ChangeState(eNODE_STATE::BLANK);
				m_currentNode->ChangeTempState(eNODE_STATE::BLANK);
			}
			m_lastNode = m_currentNode;
		}
		else if (m_state == eTYPE::WALL)
		{
			if (m_currentNode->GetState() != eNODE_STATE::START && m_currentNode->GetState() != eNODE_STATE::END)
			{
				m_currentNode->ChangeState(eNODE_STATE::WALL);
				m_currentNode->ChangeTempState(eNODE_STATE::WALL);
			}
			m_lastNode = m_currentNode;
		}
		else if (m_state == eTYPE::START)
		{
			if (m_currentNode->GetState() != eNODE_STATE::END)
			{
				if (m_lastNode != nullptr)
				{
					m_lastNode->ChangeState(m_lastNode->GetTempState());
				}
				m_currentNode->ChangeState(eNODE_STATE::START);
				m_lastNode = m_currentNode;
			}
		}
		else if (m_state == eTYPE::END)
		{
			if (m_currentNode->GetState() != eNODE_STATE::START)
			{
				if (m_lastNode != nullptr)
				{
					m_lastNode->ChangeState(m_lastNode->GetTempState());
				}
				m_currentNode->ChangeState(eNODE_STATE::END);
				m_lastNode = m_currentNode;
			}
		}
	}
}

void MouseInfo::Update()
{
}

void MouseInfo::ChangeState(eTYPE state)
{
	m_state = state;
}

void MouseInfo::ChangeTileType(eTILE_TYPE type)
{
	m_tileType = type;
}

eTYPE MouseInfo::GetState()
{
	return m_state;
}

eTILE_TYPE MouseInfo::GetTileType()
{
	return m_tileType;
}
