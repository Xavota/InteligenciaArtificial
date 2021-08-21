#pragma once
#include <SFML/Graphics.hpp>
#include <map>

enum class eNODE_STATE
{
	NONE = -1,
	BLANK,
	WALL,
	START,
	END,
	COUNT
};

enum class eNODE_PATH_TYPE
{
	NONE = -1,
	GRASS,
	WATER,
	SAND,
	COUNT
};

class Node
{
public:
	Node(sf::Vector2f pos, sf::Vector2f size);
	Node(sf::Vector2f pos, sf::Vector2f size, eNODE_PATH_TYPE initState, bool wall);
	~Node();

	/**
	  * @brief      Initialices the node with a position and size
	  * @param      pos: the position in the world
	  * @param      size: the size of the node
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2f pos, sf::Vector2f size);
	/**
	  * @brief      Initialices the node with a position, size, state and if it has a wall
	  * @param      pos: the position in the world
	  * @param      size: the size of the node
	  * @param      initState: the initial state of the node
	  * @param      wall: has a wall?
	  * @bug	    No know Bugs
	*/
	void Init(sf::Vector2f pos, sf::Vector2f size, eNODE_PATH_TYPE initState, bool wall);
	/**
	  * @brief      Updates the node every frame.
	  * @param      window: the window where it is placed. Neded for the mouse position
	  * @bug	    No know Bugs
	*/
	void Update(sf::RenderWindow* window);
	/**
	  * @brief      Renderss the node every frame.
	  * @param      window: the window where it is rendered to.
	  * @bug	    No know Bugs
	*/
	void Render(sf::RenderWindow* window);
	/**
	  * @brief      Frees the memory
	  * @bug	    No know Bugs
	*/
	void Destroy();

	/**
	  * @brief      Changes the state type of the node, and its color or texture
	  * @param      state: the new state
	  * @bug	    No know Bugs
	*/
	void ChangeState(eNODE_STATE state);
	/**
	  * @brief      Changes the tile type of the node, and its color or texture
	  * @param      type: the new type
	  * @bug	    No know Bugs
	*/
	void ChangeTileType(eNODE_PATH_TYPE type);
	/**
	  * @brief      Changes the temp state type of the node, and its color or texture
	  * @param      state: the new temp state
	  * @bug	    No know Bugs
	*/
	void ChangeTempState(eNODE_STATE state);
	/**
	  * @brief      Returns the state type of the node, and its color or texture
	  * @bug	    No know Bugs
	*/
	eNODE_STATE GetState();
	/**
	  * @brief      Returns the tile type of the node, and its color or texture
	  * @bug	    No know Bugs
	*/
	eNODE_PATH_TYPE GetTileType();
	/**
	  * @brief      Returns the temp state type of the node, and its color or texture
	  * @bug	    No know Bugs
	*/
	eNODE_STATE GetTempState();

	/**
	  * @brief      Returns the positions in the world of the node
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetPosition();
	/**
	  * @brief      Returns the size of the node
	  * @bug	    No know Bugs
	*/
	sf::Vector2f GetSize();

	/**
	  * @brief      Sets a new color for the node
	  * @param      color: the new color
	  * @bug	    No know Bugs
	*/
	void SetColor(sf::Color color);
	/**
	  * @brief      Sets a new parent for the node
	  * @param      parent: the new parent
	  * @bug	    No know Bugs
	*/
	void SetParent(Node* parent);
	/**
	  * @brief      Has the node been searched yet?
	  * @bug	    No know Bugs
	*/
	void Searched();

	/**
	  * @brief      Restart the search state of the node
	  * @bug	    No know Bugs
	*/
	void RestartSearch();
	/**
	  * @brief      Restart all the states, walls and search of the node.
	  * @bug	    No know Bugs
	*/
	void RestartAll();

	/**
	  * @brief      Has to show the lines of the node?
	  * @param      active: yes/no
	  * @bug	    No know Bugs
	*/
	void ShowLines(bool active);

public:
	Node* m_up = nullptr;
	float m_upWeight = 0;
	Node* m_right = nullptr;
	float m_rightWeight = 0;
	Node* m_down = nullptr;
	float m_downWeight = 0;
	Node* m_left = nullptr;
	float m_leftWeight = 0;

	Node* m_parent = nullptr;
	float m_parentWeight = 0;

	bool m_searched = false;

	int m_facesSeen = 0;

	float m_ucledianDistance = 0;

private:
	sf::RectangleShape m_shape;
	sf::RectangleShape m_wall;

	eNODE_STATE m_state = eNODE_STATE::NONE;
	eNODE_STATE m_tempSate = eNODE_STATE::BLANK;
	eNODE_PATH_TYPE m_pathType = eNODE_PATH_TYPE::NONE;

	static std::map<eNODE_STATE, sf::Color> m_colors;
};

