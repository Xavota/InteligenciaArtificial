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

enum class eTILE_TYPE
{
	NONE = -1,
	GRASS,
	WATER,
	SAND,
	WALL,
	COUNT
};

class MouseInfo
{
public:
	MouseInfo() = default;
	~MouseInfo() = default;

	static void ChageNode(Node* newNode);
	static void Update();

	static void ChangeState(eTYPE state);
	static void ChangeTileType(eTILE_TYPE type);
	static eTYPE GetState();
	static eTILE_TYPE GetTileType();


	static eTYPE m_state;
	static eTILE_TYPE m_tileType;
	static Node* m_currentNode;
	static Node* m_lastNode;
};

