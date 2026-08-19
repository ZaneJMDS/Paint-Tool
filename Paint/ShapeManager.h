#pragma once
#include <SFML/Graphics.hpp>

enum CurrentTool
{
	tool_rectangle,
	tool_circle,
	tool_elipse,
	tool_line
};

class ShapeManager
{
public:
	CurrentTool m_current_tool;
	sf::CircleShape* m_circle_ref;
	sf::RectangleShape* m_rect_ref;
	sf::CircleShape* m_elipse_ref;
	sf::VertexArray m_line_tool_ref;
	sf::RenderWindow* m_window_ref;

	ShapeManager();
	~ShapeManager();

	CurrentTool GetTool() { return m_current_tool; }
	void SwapTool(CurrentTool _target_tool) { m_current_tool = _target_tool; }
	void SetTools(sf::CircleShape* _circle_ref, sf::RectangleShape* _rect_ref, sf::CircleShape* _elipse_ref);
	void Update(sf::RenderWindow* _window);
};

