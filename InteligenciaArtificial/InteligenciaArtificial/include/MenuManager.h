#pragma once
#include "UI.h"
#include "UIShape.h"

namespace gl {
class MenuManager : public UI
{
public:
	virtual void Init();
	virtual void Reposition(sf::Vector2f wordlPosition);
	virtual void Update();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();
protected:
	vector<Button> m_buttons;
	vector<UIShape> m_shapes;
};
}
