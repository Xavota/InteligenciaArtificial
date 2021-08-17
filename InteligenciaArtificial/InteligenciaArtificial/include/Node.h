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

	void Init(sf::Vector2f pos, sf::Vector2f size);
	void Init(sf::Vector2f pos, sf::Vector2f size, eNODE_PATH_TYPE initState, bool wall);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy();

	void ChangeState(eNODE_STATE state);
	void ChangeTileType(eNODE_PATH_TYPE type);
	void ChangeTempState(eNODE_STATE state);
	eNODE_STATE GetState();
	eNODE_STATE GetTempState();

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();

	void SetColor(sf::Color color);
	void SetParent(Node* parent);
	void Searched();

	void RestartSearch();
	void RestartAll();

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

