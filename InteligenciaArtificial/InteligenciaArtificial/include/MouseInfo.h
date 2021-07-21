#pragma once
#include "Node.h"
enum class eTYPE
{
	NONE = -1,
	BLANK,
	WALL,
	START,
	END,
	COUNT
};
class MouseInfo
{
public:
	MouseInfo() = default;
	~MouseInfo() = default;

	static void ChageNode(Node* newNode);
	static void Update();

	static eTYPE m_state;
	static Node* m_currentNode;
	static Node* m_lastNode;
};

