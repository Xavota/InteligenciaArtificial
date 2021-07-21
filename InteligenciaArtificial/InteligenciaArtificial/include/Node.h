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

class Node
{
public:
	Node(sf::Vector2f pos, sf::Vector2f size);
	~Node();

	void Init(sf::Vector2f pos, sf::Vector2f size);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy();

	void ChangeState(eNODE_STATE state);
	void ChangeTempState(eNODE_STATE state);
	eNODE_STATE GetState();
	eNODE_STATE GetTempState();

public:
	Node* m_up;
	Node* m_right;
	Node* m_down;
	Node* m_left;

	Node* m_parent;

private:
	sf::RectangleShape m_shape;

	eNODE_STATE m_state = eNODE_STATE::NONE;
	eNODE_STATE m_tempSate = eNODE_STATE::BLANK;

	bool m_in = false;


	static std::map<eNODE_STATE, sf::Color> m_colors;
};

