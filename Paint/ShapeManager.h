#pragma once
#include <SFML/Graphics.hpp>

enum CurrentTool
{
	tool_rectangle,
	tool_circle,
	tool_colour
};

class ShapeManager
{
public:
	CurrentTool m_current_tool;
	sf::CircleShape* m_circle_ref;
	sf::RectangleShape* m_rect_ref;
	sf::VertexArray m_line_tool_ref;
	sf::RenderWindow* m_window_ref;

	ShapeManager();
	~ShapeManager();

	void SwapTool(CurrentTool _target_tool) { m_current_tool = _target_tool; }
	void SetTools(sf::CircleShape* _circle_ref, sf::RectangleShape* _rect_ref);
	void Update(sf::RenderWindow* _window);
};

