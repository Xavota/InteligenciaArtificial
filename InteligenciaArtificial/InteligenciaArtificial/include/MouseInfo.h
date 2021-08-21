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

	/**
	  * @brief      Changes the node under the mouse (unused)
	  * @param      newNode: the new node under
	  * @bug	    No know Bugs
	*/
	static void ChageNode(Node* newNode);
	/**
	  * @brief      Updates the logic of the Mouse
	  * @bug	    No know Bugs
	*/
	static void Update();

	/**
	  * @brief      Changes the state type of the mouse, for the grid to know
	  * @param      state: the new state
	  * @bug	    No know Bugs
	*/
	static void ChangeState(eTYPE state);
	/**
	  * @brief      Changes the tile type of the mouse, for the grid to know
	  * @param      type: the new type
	  * @bug	    No know Bugs
	*/
	static void ChangeTileType(eTILE_TYPE type);
	/**
	  * @brief      Returns the state type of the mouse, for the grid to know
	  * @bug	    No know Bugs
	*/
	static eTYPE GetState();
	/**
	  * @brief      Returns the tile type of the mouse, for the grid to know
	  * @bug	    No know Bugs
	*/
	static eTILE_TYPE GetTileType();


	static eTYPE m_state;
	static eTILE_TYPE m_tileType;
	static Node* m_currentNode;
	static Node* m_lastNode;
};

